/*
 * Elevator.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "Elevator.h"

Elevator::Elevator():
	lowerLimit(1),
	upperLimit(2),
	home(3),
	motor1(4),
	motor2(5)
{

	currentMode = buttonMode;


}

void Elevator::find_home(){

	while (!isHome){

		if (!lowerLimitTriped)
			{

			motor1.Set(-motorSpeed);		//go down
			motor2.Set(-motorSpeed);

			}
		else if (lowerLimitTriped)
			{

			motor1.Set(motorSpeed);			//go up
			motor2.Set(motorSpeed);

			}
	}
	int encoder_value = 0;
}





void Elevator::operateElevator(){

	if (upperLimitTriped){

		motor1.Set(0);
		motor2.Set(0);
		}
	else if (lowerLimitTriped){
		motor1.Set(0);
		motor2.Set(0);
		}

	switch (currentMode){

	case buttonMode:
		break;

	case joystickMode:
		break;


	}




}








Elevator::~Elevator(){}
