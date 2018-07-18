/*
	Motor.cpp - Library for driving motors on an H-bridge driver
	Created by Coleman S. Swenson, April 13, 2018.
	For use in ARLISS AppleSeed Project, OSU 2018
*/

#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pin1, int pin2, int enPin)
{
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	_pin1 = pin1;
	_pin2 = pin2;
	_enPin = enPin;
	
}

void Motor::drive(int speed)
{
	if(speed < 0){
		digitalWrite(_pin1,HIGH);
		digitalWrite(_pin2, LOW);
		analogWrite(enPin, abs(speed));
	}else if(speed > 0){
		digitalWrite(_pin1,LOW);
		digitalWrite(_pin2, HIGH);
		analogWrite(enPin, abs(speed));
	}else if(speed == 0){
		digitalWrite(_pin1,LOW);
		digitalWrite(_pin2,LOW);
		analogWrite(_enPin, 0);
	}
}