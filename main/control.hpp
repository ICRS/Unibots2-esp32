#ifndef CONTROL_HPP
#define CONTROL_HPP

void drive_forward();
void drive_forward_blocking();
void drive_forward_blocking(unsigned int time);
void half_drive_forward();

void drive_reverse();
void drive_reverse_blocking();
void drive_reverse_blocking(unsigned int time);

void turn90_left();
void turn90_right();
void turn180();

void control_setup();
void control_loop();
void complex_control_loop();
#endif