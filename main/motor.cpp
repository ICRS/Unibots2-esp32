// DRV8833 test pins
#include "motor.hpp"
#include "constants.hpp"
#include "arduino.h"



static constexpr unsigned int LEFT_MOTOR_DRIVER_IN1 = 16;
static constexpr unsigned int LEFT_MOTOR_DRIVER_IN2 = 5;
static constexpr unsigned int LEFT_MOTOR_DRIVER_FAULT = 2;
static constexpr unsigned int LEFT_MOTOR_DRIVER_SLEEP = 2;
static constexpr unsigned int LEFT_MOTOR_DRIVER_IN3 = 2;
static constexpr unsigned int LEFT_MOTOR_DRIVER_IN4 = 4;

/*

*/

static constexpr unsigned int RIGHT_MOTOR_DRIVER_IN1 = 14;    
static constexpr unsigned int RIGHT_MOTOR_DRIVER_IN2 = 27;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_FAULT = 16;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_SLEEP = 4;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_IN3 = 25;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_IN4 = 33;

void init_left_motor_driver(){
  pinMode(LEFT_MOTOR_DRIVER_IN1,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN2,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN3,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN4,    OUTPUT);
  if constexpr (MOTOR_DRIVER_FAULT_USED)
    pinMode(LEFT_MOTOR_DRIVER_SLEEP,  OUTPUT);
  if constexpr (MOTOR_DRIVER_SLEEP_USED)
    pinMode(LEFT_MOTOR_DRIVER_FAULT,  INPUT_PULLUP);
}

void init_right_motor_driver(){
  pinMode(RIGHT_MOTOR_DRIVER_IN1,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN2,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN3,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN4,   OUTPUT);
  if constexpr (MOTOR_DRIVER_FAULT_USED)
    pinMode(RIGHT_MOTOR_DRIVER_SLEEP, OUTPUT);
  if constexpr (MOTOR_DRIVER_SLEEP_USED)
    pinMode(RIGHT_MOTOR_DRIVER_FAULT, INPUT_PULLUP);
}


void stop_left_motor_driver(){
  drive_left_motor_driver(0,0,0,0);
}

void stop_right_motor_driver(){
  drive_right_motor_driver(0,0,0,0);
}



void enable_disable_left_motor_driver(bool enable){
  if constexpr (MOTOR_DRIVER_SLEEP_USED)
    digitalWrite(LEFT_MOTOR_DRIVER_SLEEP, enable);
}

void enable_disable_right_motor_driver(bool enable){
  if constexpr (MOTOR_DRIVER_SLEEP_USED)
    digitalWrite(RIGHT_MOTOR_DRIVER_SLEEP, enable);
}




void enable_left_motor_driver(){
  if constexpr (MOTOR_DRIVER_SLEEP_USED)
    digitalWrite(LEFT_MOTOR_DRIVER_SLEEP, HIGH);
}

void enable_right_motor_driver(){
  if constexpr (MOTOR_DRIVER_SLEEP_USED)
    digitalWrite(RIGHT_MOTOR_DRIVER_SLEEP, HIGH);
}




void disable_left_motor_driver(){
  if constexpr (MOTOR_DRIVER_SLEEP_USED)
    digitalWrite(LEFT_MOTOR_DRIVER_SLEEP, LOW);
}

void disable_right_motor_driver(){
  if constexpr (MOTOR_DRIVER_SLEEP_USED)
    digitalWrite(RIGHT_MOTOR_DRIVER_SLEEP, LOW);
}


#if MOTOR_DRIVER_FAULT_USED

bool read_left_motor_driver_fault(){
  return digitalRead(LEFT_MOTOR_DRIVER_FAULT);
}

bool read_right_motor_driver_fault(){
  return digitalRead(RIGHT_MOTOR_DRIVER_FAULT);
}

#endif //MOTOR_DRIVER_FAULT_USED




void drive_left_motor_driver(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4){
  analogWrite(LEFT_MOTOR_DRIVER_IN1, in1);
  analogWrite(LEFT_MOTOR_DRIVER_IN2, in2);
  analogWrite(LEFT_MOTOR_DRIVER_IN3, in3);
  analogWrite(LEFT_MOTOR_DRIVER_IN4, in4);
  Serial.printf("left %d %d %d %d\n", in1, in2, in3, in4);
}

void drive_left_motor_driver(unsigned int in_low, unsigned int in_high){
  drive_left_motor_driver(in_low, in_high, in_low, in_high);
}

void drive_left_motor_driver(int in){
  in < 0 ? drive_left_motor_driver_reverse(-in) : drive_left_motor_driver_forward(in);
}

void drive_right_motor_driver(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4){
  analogWrite(RIGHT_MOTOR_DRIVER_IN1, in1);
  analogWrite(RIGHT_MOTOR_DRIVER_IN2, in2);
  analogWrite(RIGHT_MOTOR_DRIVER_IN3, in3);
  analogWrite(RIGHT_MOTOR_DRIVER_IN4, in4);
  Serial.printf("right %d %d %d %d\n", in1, in2, in3, in4);
}

void drive_right_motor_driver(unsigned int in_low, unsigned int in_high){
drive_right_motor_driver(in_low, in_high, in_low, in_high);
}

void drive_right_motor_driver(int in){
  in < 0 ? drive_right_motor_driver_reverse(-in) : drive_right_motor_driver_forward(in);
}

void drive_left_motor_driver_forward(unsigned int in) {
  drive_left_motor_driver(0, in);
}

void drive_left_motor_driver_reverse(unsigned int in){
  drive_left_motor_driver(in, 0);
}

void drive_right_motor_driver_forward(unsigned int in){
  drive_right_motor_driver(0, in);
}

void drive_right_motor_driver_reverse(unsigned int in){
  drive_right_motor_driver(in, 0);
}

void drive_forward(unsigned int in){
  drive_left_motor_driver_forward(in);
  drive_right_motor_driver_reverse(in);
}


void drive_forward(unsigned int in, unsigned int time){
  drive_forward(in);
  delay(time);
}

void drive_reverse(unsigned int in){
  drive_left_motor_driver_reverse(in);
  drive_right_motor_driver_forward(in);
}

void drive_reverse(unsigned int in, unsigned int time){
  drive_reverse(in);
  delay(time);
}

void stop(){
  stop_left_motor_driver();
  stop_right_motor_driver();
}


void point_turn_left(unsigned int in){
  drive_left_motor_driver_reverse(in);
  drive_right_motor_driver_reverse(in);

}

void point_turn_right(unsigned int in){
  drive_left_motor_driver_forward(in);
  drive_right_motor_driver_forward(in);
}

void point_turn_left(unsigned int in, unsigned int time){
  point_turn_left(in);
  delay(time);
}

void point_turn_right(unsigned int in, unsigned int time){
  point_turn_right(in);
  delay(time);
}

void motor_test_setup(){
  init_left_motor_driver();
  init_right_motor_driver();

  #if MOTOR_DRIVER_SLEEP_USED
    enable_right_motor_driver();
    enable_left_motor_driver();
  #endif

  stop_right_motor_driver();
  stop_left_motor_driver();  
  Serial.begin(BAUD_RATE);
}

void motor_test_loop(){
  #if MOTOR_DRIVER_FAULT_USED
    int fault;
  #endif
  
  // Test Motor A
  drive_left_motor_driver(MAX_DUTY_CYCLE);
  #if MOTOR_DRIVER_FAULT_USED
    fault = read_left_motor_driver_fault();
    Serial.print("left driver fault 1: ");
    Serial.println(fault);
  #else
    Serial.println("left 1:");
  #endif
  delay(1000);

  stop_left_motor_driver();
  #if MOTOR_DRIVER_FAULT_USED
    fault = read_left_motor_driver_fault();
    Serial.print("left driver fault 2: ");
    Serial.println(fault);
  #else
    Serial.println("left 2:");
  #endif
  delay(1000);

  drive_left_motor_driver(-MAX_DUTY_CYCLE);
  #if MOTOR_DRIVER_FAULT_USED
    fault = read_left_motor_driver_fault();
    Serial.print("left driver fault: 3: ");
    Serial.println(fault);
  #else
    Serial.println("left 3");
  #endif
  delay(1000);

  stop_left_motor_driver();
  #if MOTOR_DRIVER_FAULT_USED
    fault = read_left_motor_driver_fault();
    Serial.print("left driver fault 4: ");
    Serial.println(fault);
  #else
    Serial.println("left 4");
  #endif
  delay(1000);
  
  // Test Motor B
  drive_right_motor_driver(MAX_DUTY_CYCLE);
  #if MOTOR_DRIVER_FAULT_USED
    fault = read_right_motor_driver_fault();
    Serial.print("right motor driver fault 1: ");
    Serial.println(fault);
  #else
    Serial.println("right 1");
  #endif
  delay(1000);

  stop_right_motor_driver();
  #if MOTOR_DRIVER_FAULT_USED
    fault = read_right_motor_driver_fault();
    Serial.print("right motor driver fault 2: ");
    Serial.println(fault);
  #else
    Serial.println("right 2");
  #endif
  delay(1000);

  drive_right_motor_driver(-MAX_DUTY_CYCLE);
  #if MOTOR_DRIVER_FAULT_USED
    fault = read_right_motor_driver_fault();
    Serial.print("right motor driver fault  3: ");
    Serial.println(fault);
  #else
    Serial.println("right 3");
  #endif
  delay(1000);

  stop_right_motor_driver();
  #if MOTOR_DRIVER_FAULT_USED
    fault = read_right_motor_driver_fault();
    Serial.print("right motor driver fault 4: ");
    Serial.println(fault);
  #else
    Serial.println("right 4");
  #endif
  delay(1000);
}    