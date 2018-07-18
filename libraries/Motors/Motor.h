/*
	Motor.h Library for driving motors on an H-bridge driver
	Created by Coleman S. Swenson, April 13, 2018.
	For use in Arliss AppleSeed Project
*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
Class Motor
{
	public:
		Motor(int pin1, int pin2, int enPin);
		drive(int speed);
	private:
		int _pin1;
		int _pin2;
		int _enPin;
};

#endif