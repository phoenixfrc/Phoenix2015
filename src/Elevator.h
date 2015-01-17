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
	Encoder encoder;

	enum elevatorStates{joystickMode, buttonMode};
	enum offSets{none, scoring, step};
	float motorSpeed = .5;
	int ticks = 200;
        elevatorStates currentMode;

        offSets offSetState;
        int offset = 0;
	double distance = 0; // distance form home (in)
	int goalStep = 0;   /*
	                         0 = floor
	                         1 = 13 in
                                 2 = 26 in
                                 3 = 39 in
                                 4 = 52 in
                             */
	bool upperWasPressed = false;
	bool lowerWasPressed = false;
	bool switchWasPressed = false;


public:
	Elevator();
	void find_home();
	void operateElevator(Joystick * gamePad);
	void moveElevator();
	~Elevator();

};





#endif /* SRC_ELEVATOR_H_ */
