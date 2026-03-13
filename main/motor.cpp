// DRV8833 test pins
#include "motor.hpp"
#include "constants.hpp"
#include "arduino.h"

static constexpr int UNDEFINED_PIN = 2;



static constexpr unsigned int LEFT_MOTOR_DRIVER_IN1 = 25;
static constexpr unsigned int LEFT_MOTOR_DRIVER_IN2 = 26;
static constexpr unsigned int LEFT_MOTOR_DRIVER_FAULT = 27;
static constexpr unsigned int LEFT_MOTOR_DRIVER_SLEEP = 14;
static constexpr unsigned int LEFT_MOTOR_DRIVER_IN3 = 12;
static constexpr unsigned int LEFT_MOTOR_DRIVER_IN4 = 13;


static constexpr unsigned int RIGHT_MOTOR_DRIVER_IN1 = 5;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_IN2 = 17;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_FAULT = 16;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_SLEEP = 4;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_IN3 = 2;
static constexpr unsigned int RIGHT_MOTOR_DRIVER_IN4 = 15;

void init_left_motor_driver(){
  pinMode(LEFT_MOTOR_DRIVER_IN1,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN2,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN3,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN4,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_SLEEP,  OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_FAULT,  INPUT_PULLUP);
}

void init_right_motor_driver(){
  pinMode(RIGHT_MOTOR_DRIVER_IN1,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN2,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN3,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN4,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_SLEEP, OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_FAULT, INPUT_PULLUP);
}


void stop_left_motor_driver(){
  drive_left_motor_driver(0,0,0,0);
}

void stop_right_motor_driver(){
  drive_right_motor_driver(0,0,0,0);
}




void enable_left_motor_driver(){
  digitalWrite(LEFT_MOTOR_DRIVER_SLEEP, HIGH);
}

void enable_right_motor_driver(){
  digitalWrite(RIGHT_MOTOR_DRIVER_SLEEP, HIGH);
}




void disable_left_motor_driver(){
  digitalWrite(LEFT_MOTOR_DRIVER_SLEEP, LOW);
}

void disable_right_motor_driver(){
  digitalWrite(RIGHT_MOTOR_DRIVER_SLEEP, LOW);
}



bool read_left_motor_driver_fault(){
  return digitalRead(LEFT_MOTOR_DRIVER_FAULT);
}

bool read_right_motor_driver_fault(){
  return digitalRead(RIGHT_MOTOR_DRIVER_FAULT);
}




void drive_left_motor_driver(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4){
  analogWrite(LEFT_MOTOR_DRIVER_IN1, in1);
  analogWrite(LEFT_MOTOR_DRIVER_IN2, in2);
  analogWrite(LEFT_MOTOR_DRIVER_IN3, in3);
  analogWrite(LEFT_MOTOR_DRIVER_IN4, in4);
}

void drive_left_motor_driver(unsigned int in_low, unsigned int in_high){
  drive_left_motor_driver(in_low, in_high, in_low, in_high);
}

void drive_left_motor_driver(int in){
  in < 0 ? drive_left_motor_driver(-in, 0) : drive_left_motor_driver(0, in);
}

void drive_right_motor_driver(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4){
  analogWrite(RIGHT_MOTOR_DRIVER_IN1, in1);
  analogWrite(RIGHT_MOTOR_DRIVER_IN2, in2);
  analogWrite(RIGHT_MOTOR_DRIVER_IN3, in3);
  analogWrite(RIGHT_MOTOR_DRIVER_IN4, in4);
}

void drive_right_motor_driver(unsigned int in_low, unsigned int in_high){
  drive_right_motor_driver(in_low, in_high, in_low, in_high);
}

void drive_right_motor_driver(int in){
  in < 0 ? drive_right_motor_driver(-in, 0) : drive_right_motor_driver(0, in);
}

void motor_test_setup(){
    init_left_motor_driver();
  init_right_motor_driver();

  enable_right_motor_driver();
  enable_left_motor_driver();

  stop_right_motor_driver();
  stop_left_motor_driver();  
  Serial.begin(BAUD_RATE);
}

void motor_test_loop(){
    int fault;
  // Test Motor A
  drive_left_motor_driver(MAX_DUTY_CYCLE);
  fault = read_left_motor_driver_fault();
  Serial.print("left driver fault 1: ");
  Serial.println(fault);
  delay(1000);

  stop_left_motor_driver();
  fault = read_left_motor_driver_fault();
  Serial.print("left driver fault 2: ");
  Serial.println(fault);
  delay(1000);

  drive_left_motor_driver(-MAX_DUTY_CYCLE);
  fault = read_left_motor_driver_fault();
  Serial.print("left driver fault: 3: ");
  Serial.println(fault);
  delay(1000);

  stop_left_motor_driver();
  fault = read_left_motor_driver_fault();
  Serial.print("left driver fault 4: ");
  Serial.println(fault);
  delay(1000);
  
  // Test Motor B
  drive_right_motor_driver(MAX_DUTY_CYCLE);
  fault = read_right_motor_driver_fault();
  Serial.print("right motor driver fault 1: ");
  Serial.println(fault);
  delay(1000);

  stop_right_motor_driver();
  fault = read_right_motor_driver_fault();
  Serial.print("right motor driver fault 2: ");
  Serial.println(fault);
  delay(1000);

  drive_right_motor_driver(-MAX_DUTY_CYCLE);
  fault = read_right_motor_driver_fault();
  Serial.print("right motor driver fault  3: ");
  Serial.println(fault);
  delay(1000);

  stop_right_motor_driver();
  fault = read_right_motor_driver_fault();
  Serial.print("right motor driver fault 4: ");
  Serial.println(fault);
  delay(1000);
}