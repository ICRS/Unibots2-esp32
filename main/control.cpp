#include "motor.hpp"
#include "constants.hpp"
#include "servo.hpp"
#include "control.hpp"
#include <arduino.h>

static constexpr int TURN90_LEFT_TIME  = 600;
static constexpr int TURN90_RIGHT_TIME = 600;
static constexpr int TURN180_TIME = 1000;
static constexpr unsigned int FORWARD_TIME = 3000;
static constexpr unsigned int REVERSE_TIME = 3000;

static constexpr unsigned int FORWARD_SPEED = MAX_DUTY_CYCLE;
static constexpr unsigned int REVERSE_SPEED = MAX_DUTY_CYCLE;


static_assert(TURN90_LEFT_TIME == TURN90_RIGHT_TIME);

static constexpr unsigned int TIME_TO_LIVE_S = 180;

static constexpr unsigned int PARK_TIME = 1000;
static constexpr unsigned int RETURN_TIME = 20000;
static constexpr unsigned int NUM_CORNERS = 4;
static constexpr unsigned int SETUP_TIME = TURN90_LEFT_TIME + FORWARD_TIME / 2;
static constexpr unsigned int TOTAL_LOOP_TIME = TIME_TO_LIVE_S - SETUP_TIME - RETURN_TIME;
static constexpr unsigned int NUM_REPETITIONS = TOTAL_LOOP_TIME * 1000ul / (TURN90_LEFT_TIME + FORWARD_TIME);
static constexpr unsigned int END_CORNER = NUM_REPETITIONS % 4;

void drive_forward(){drive_forward(FORWARD_SPEED);}
void drive_forward_blocking(){drive_forward_blocking(FORWARD_TIME);}
void drive_forward_blocking(unsigned int time){drive_forward(FORWARD_SPEED, time);}
void half_drive_forward_blocking(){drive_forward(FORWARD_SPEED, FORWARD_TIME / 2);}

void drive_reverse(){drive_reverse(REVERSE_SPEED);}
void drive_reverse_blocking(){drive_reverse(REVERSE_SPEED, REVERSE_TIME);}
void drive_reverse_blocking(unsigned int time){drive_reverse(REVERSE_SPEED, time);}

void turn_right(){
  static constexpr unsigned int in = 255;
  drive_left_motor_driver(0,in,0,0);
  drive_right_motor_driver(0,in,0,0);
}

void turn90_right(){
  static constexpr unsigned int in = 255;
  turn_right();
  delay(TURN90_RIGHT_TIME);
}

void turn_left(){
  static constexpr unsigned int in = 255;
  drive_left_motor_driver(in,0,0,0);
  drive_right_motor_driver(in,0,0,0);
}

void turn90_left(){
  static constexpr unsigned int in = 255;
  turn_left();
  delay(TURN90_LEFT_TIME);
}

void turn180(){
  static constexpr unsigned int in = 255;
  point_turn_right(in, TURN180_TIME);
}

void control_setup() {
  init_left_motor_driver();
  init_right_motor_driver();  
  init_servo();
}

void complex_control_loop(){
  static unsigned int start_time = millis() / 1000;
  static constexpr unsigned int STRAIGHT_TIME = 5000;
  static constexpr unsigned int HALF_STRAIGHT_TIME = STRAIGHT_TIME / 2;
  static constexpr unsigned int STRAIF_TIME = 1000;
  
  drive_forward_blocking(500);
  turn90_left();
  drive_forward_blocking(HALF_STRAIGHT_TIME);
  turn90_right();
  drive_forward_blocking(STRAIF_TIME);
  turn90_right();

  drive_forward_blocking(STRAIGHT_TIME);
  turn90_left();
  drive_forward_blocking(STRAIF_TIME);
  turn90_left();

  drive_forward_blocking(STRAIGHT_TIME);
  turn90_right();
  drive_forward_blocking(STRAIF_TIME);
  turn90_right();

  //going backward now

  drive_forward_blocking(STRAIGHT_TIME);
  turn90_right();
  drive_forward_blocking(STRAIF_TIME);
  turn90_right();

  drive_forward_blocking(STRAIGHT_TIME);
  turn90_left();
  drive_forward_blocking(STRAIF_TIME);
  turn90_left();

  drive_forward_blocking(STRAIGHT_TIME);
  turn90_right(); 
  drive_forward_blocking(HALF_STRAIGHT_TIME);
  turn90_right();

  if (millis() / 1000 - start_time <= 150)
    return;

  turn90_right();
  drive_reverse_blocking(500);
  stop();
  while (true);
}

void control_loop() {
  
  turn90_right();
  half_drive_forward_blocking();

  for (int i = 0; i < NUM_REPETITIONS; ++i){
    turn90_left();
    drive_forward_blocking();
  }

  if constexpr (END_CORNER == 0){
    turn180();
    half_drive_forward_blocking();
    turn90_right();
    drive_reverse_blocking();
  } else if constexpr (END_CORNER == 1){
    turn180();
    drive_forward_blocking();
    turn90_right();
    half_drive_forward_blocking();
    turn90_right();
    drive_reverse_blocking();
  } else if constexpr (END_CORNER == 2) {
    turn90_left();
    drive_forward_blocking();
    turn90_left();
    half_drive_forward_blocking();
    turn90_left();
    drive_reverse_blocking();
  } else if constexpr (END_CORNER == 3) {
    turn90_left();
    half_drive_forward_blocking();
    turn90_left();
    drive_reverse_blocking();
  }
  drive_servo_up();
  stop();
  while(true);
}