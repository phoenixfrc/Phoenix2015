/*
 * DeadZoneJoystick.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: Developer
 */

#include "Team2342Joystick.h"

/*
 * 0.1 to -0.1 should be treated as '0'
 * */


float Team2342Joystick::GetZWithDeadZone(float deadZone = 0.1){
	float twistValue = this->GetZ();

	if (abs(twistValue) <= deadZone){
		return 0.0;
	}

	return (twistValue - deadZone) * (1 / ( 1 - deadZone ) );
}


