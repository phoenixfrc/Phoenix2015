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
	DigitalInput homeSwitch;
	Talon motor1;
	Talon motor2;
	Encoder encoder;


	float MotorSpeed = 0.5;
	float HomeSpeed = 0.1;
	int Ticks = 200;
	double m_distance = 0; // distance form home (in)
	int Heights[4] = {0, 13, 26, 39};
	double m_goalDistance = 0;
	double Range = 0.25; // range on either side of goalDistance
	enum homingStates
	{
	    lookingForLowerLimit,
	    goingUpToHome,
	    homingComplete
	} homeState;


public:
	Elevator();
	void operateElevator
	void find_home();
	void controlElevator(Joystick * gamePad);
	void moveElevator();
	void moveMotors(double speed);
	~Elevator();

};





#endif /* SRC_ELEVATOR_H_ */
