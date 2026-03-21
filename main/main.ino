#include "motor.hpp"
#include "constants.hpp"

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

static constexpr int TURN90_LEFT_TIME  = 1000;
static constexpr int TURN90_RIGHT_TIME = 1000;
static constexpr int TURN180_TIME = 2000;

static_assert(TURN90_LEFT_TIME == TURN90_RIGHT_TIME);

static constexpr unsigned int TIME_TO_LIVE_S = 180;
static constexpr unsigned int FORWARD_TIME = 3000;
static constexpr unsigned int PARK_TIME = 1000;
static constexpr unsigned int RETURN_TIME = 20000;
static constexpr unsigned int NUM_CORNERS = 4;
static constexpr unsigned int SETUP_TIME = TURN90_LEFT_TIME + FORWARD_TIME / 2;
static constexpr unsigned int FORWARD_SPEED = MAX_DUTY_CYCLE;
static constexpr unsigned int TOTAL_LOOP_TIME = TIME_TO_LIVE_S - SETUP_TIME - RETURN_TIME;
static constexpr unsigned int NUM_REPETITIONS = TOTAL_LOOP_TIME * 1000ul / (TURN90_LEFT_TIME + FORWARD_TIME);
static constexpr unsigned int END_CORNER = NUM_REPETITIONS % 4;

void setup() {
  init_left_motor_driver();
  init_right_motor_driver();  
}

static void drive_forward(){
  drive_forward(FORWARD_SPEED, FORWARD_TIME);
}

static void half_drive_forward(){
  drive_forward(FORWARD_SPEED, FORWARD_TIME / 2);
}

static void park_reverse(){
    drive_reverse(FORWARD_SPEED, PARK_TIME);
}

static void turn90_left(){
  static constexpr int in = 255;
  point_turn_left(in, TURN90_LEFT_TIME);
}

static void turn90_right(){
  static constexpr int in = 255;
  point_turn_right(in, TURN90_RIGHT_TIME);
}

static void turn180(){
  static constexpr int in = 255;
  point_turn_right(in, TURN180_TIME);
}

void loop() {
  
  turn90_right();
  half_drive_forward();

  for (int i = 0; i < NUM_REPETITIONS; ++i){
    turn90_left();
    drive_forward();
  }

  if constexpr (END_CORNER == 0){
    turn180();
    half_drive_forward();
    turn90_right();
    park_reverse();
  } else if constexpr (END_CORNER == 1){
    turn180();
    drive_forward();
    turn90_right();
    half_drive_forward();
    turn90_right();
    park_reverse();
  } else if constexpr (END_CORNER == 2) {
    turn90_left();
    drive_forward();
    turn90_left();
    half_drive_forward();
    turn90_left();
    park_reverse();
  } else if constexpr (END_CORNER == 3) {
    turn90_left();
    half_drive_forward();
    turn90_left();
    park_reverse();
  }
}