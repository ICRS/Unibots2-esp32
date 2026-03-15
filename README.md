# Unibots2-esp32
Contains the source files for the program that will be executed on the ESP32

ESP32 I2C Communication Protocal
- Drive Control
	- First Byte (direction) - one of either:
		- 0x00 - both speeds are in the reverse direction
		- 0x01 - left is backward, right is forward
		- 0x10 - left speed is forward, right is backward	
		- 0x11 - both speeds are in the foward direction
	- Second Byte (Left Speed) - The unsigned 8 bit left motor speed
	- Third Byte (Right Speed) - The unsigned 8 bit right motor speed
- Motor Enable/Disable
	- First Byte (enable or disable)
		- 0x00 - left motor disable, right motor disable
		- 0x01 - left motor disable, right motor enable
		- 0x10 - left motor enable , right motor disable
		- 0x11 - left motor enable , right motor enable
- Read Fault
	- 0x00 - right, left fault
	- 0x01 - right fault, left no fault
	- 0x10 - right no fault, left fault
	- 0x11 - right, left no fault
	- Send back either 0x0 for a fault, 0x1 for no fault

