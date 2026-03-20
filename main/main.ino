#include "motor.hpp"
#include "constants.hpp"
#include "Wire.h"

/*
https://lastminuteengineers.com/drv8833-arduino-tutorial/

https://thelinuxcode.com/power-esp32-battery/
https://lastminuteengineers.com/esp32-pinout-reference/

Wire.begin(I2C_SDA, I2C_SCL, freq) e.g. freq can be 100000
Wire.begin() - uses SDA=21 and SCL=22 by default
also a Wire1 object

https://randomnerdtutorials.com/esp32-i2c-master-slave-arduino/

-- need to connect esp SCL SDA GND to rpi SDA SCL GND

https://randomnerdtutorials.com/esp32-i2c-master-slave-arduino/
https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2c.html
*/

static constexpr unsigned int I2C_SDA = 18;
static constexpr unsigned int I2C_SCL = 19;
static constexpr unsigned long I2C_FREQUENCY = 100'000;
static constexpr unsigned int I2C_SLAVE_ADDRESS = 0x08;
static constexpr unsigned int DIRECTION_REVERSE = 0;
static constexpr unsigned int DIRECTION_FORWARD = 1;

#if MOTOR_DRIVER_SLEEP_USED
void on_single_byte_cmd(){
  const unsigned char byte = Wire.read()
  if (byte > 3) //this includes (unsigned char)-1 i.e. no data available
    return;
  const bool left_enable = byte & 0b10;
  const bool right_enable = byte & 0b01;
  enable_disable_left_motor_driver(left_enable);
  enable_disable_right_motor_driver(right_enable);
}
#endif

void on_triple_byte_cmd(){
  const unsigned char direction = Wire.read();
  const unsigned char left_speed = Wire.read();
  const unsigned char right_speed = Wire.read();
  if (direction > 3) //this includes (unsigned char)-1 i.e. no data available
    return;
  const bool left_direction = direction & 0b10;
  const bool right_direction = direction & 0b01;
  if (left_direction == DIRECTION_FORWARD)
    drive_left_motor_driver(0, left_speed);
  else
    drive_left_motor_driver(left_speed, 0);
  if (right_direction == DIRECTION_FORWARD)
    drive_right_motor_driver(right_speed, 0);
  else
    drive_right_motor_driver(0, right_speed);
}

void i2c_on_recieve(int len){
  switch (len){
    #if MOTOR_DRIVER_SLEEP_USED
    case 1: on_single_byte_cmd(); break;
    #endif
    case 3: on_triple_byte_cmd(); break;
  }
}

#if MOTOR_DRIVER_FAULT_USED
void i2c_on_request(){
  const unsigned char byte = read_left_motor_driver_fault() << 1 | read_right_motor_driver_fault();
  Wire.write(byte);
}
#endif

void slave_init(){
  Wire.begin(I2C_SLAVE_ADDRESS, I2C_SDA, I2C_SCL, I2C_FREQUENCY);
  Wire.onReceive(i2c_on_recieve);
#if MOTOR_DRIVER_FAULT_USED
  Wire.onRequest(i2c_on_request);
#endif
}

void setup() {
  motor_test_setup();
}


void loop() {
  motor_test_loop();
}