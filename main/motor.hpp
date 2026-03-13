void init_left_motor_driver();
void init_right_motor_driver();

void stop_left_motor_driver();
void stop_right_motor_driver();

void enable_left_motor_driver();
void enable_right_motor_driver();

void disable_left_motor_driver();
void disable_right_motor_driver();

bool read_left_motor_driver_fault();
bool read_right_motor_driver_fault();

void drive_left_motor_driver(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4);
void drive_left_motor_driver(unsigned int in_low, unsigned int in_high);
void drive_left_motor_driver(int in);
void drive_right_motor_driver(unsigned int in1, unsigned int in2, unsigned int in3, unsigned int in4);
void drive_right_motor_driver(unsigned int in_low, unsigned int in_high);
void drive_right_motor_driver(int in);

void motor_test_setup();
void motor_test_loop();
