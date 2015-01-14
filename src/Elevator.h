/*
 * Elevator.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "WPILib.h"
#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_
class Elevator {

	DigitalInput lowerLimit;
	DigitalInput upperLimit;
	DigitalInput home;
	Talon motor1;
	Talon motor2;

	enum elevatorStates{joystickMode, buttonMode};

	bool isHome = home.Get();
	bool upperLimitTriped = upperLimit.Get();
	bool lowerLimitTriped = lowerLimit.Get();
	float encoder_value=0;
	float motorSpeed = .5;
	elevatorStates currentMode;


public:
	Elevator();
	void find_home();
	void operateElevator();
	~Elevator();

};





#endif /* SRC_ELEVATOR_H_ */
