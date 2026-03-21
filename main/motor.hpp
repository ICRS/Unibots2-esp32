#ifndef MOTOR_HPP
#define MOTOR_HPP

#define MOTOR_DRIVER_FAULT_USED 0
#define MOTOR_DRIVER_SLEEP_USED 0

/*
FOR ANYONE READING THIS CODE
I could massively reduce the code duplication using templates and structure types
but I am implementing it this way for "simplicity..."
*/

void init_left_motor_driver();
void init_right_motor_driver();

void stop_left_motor_driver();
void stop_right_motor_driver();

void enable_disable_left_motor_driver(bool enable);
void enable_disable_right_motor_driver(bool enable);

void enable_left_motor_driver();
void enable_right_motor_driver();

void disable_left_motor_driver();
void disable_right_motor_driver();


//false means there is a fault, true means there is not a 
#if MOTOR_DRIVER_FAULT_USED
  bool read_left_motor_driver_fault();
  bool read_right_motor_driver_fault();
#endif

void drive_left_motor_driver(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4);
void drive_left_motor_driver(unsigned int in_low, unsigned int in_high);
void drive_left_motor_driver(int in);
void drive_right_motor_driver(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4);
void drive_right_motor_driver(unsigned int in_low, unsigned int in_high);
void drive_right_motor_driver(int in);

void drive_left_motor_driver_forward(unsigned int in);
void drive_left_motor_driver_reverse(unsigned int in);
void drive_right_motor_driver_forward(unsigned int in);
void drive_right_motor_driver_reverse(unsigned int in);


void drive_forward(unsigned int in);
void drive_forward(unsigned int in, unsigned int time);
void drive_reverse(unsigned int in);
void drive_reverse(unsigned int in, unsigned int time);

void point_turn_left(unsigned int in);
void point_turn_left(unsigned int in, unsigned int time);
void point_turn_right(unsigned int in);
void point_turn_right(unsigned int in, unsigned int time);



void motor_test_setup();
void motor_test_loop();
#endif