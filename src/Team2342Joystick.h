/*
 * DeadZoneJoystick.h'
 *
 *  Created on: Jan 17, 2015
 *      Author: Developer
 */

#include "WPILib.h"

#ifndef SRC_TEAM2342JOYSTICK_H_
#define SRC_TEAM2342JOYSTICK_H_

class Team2342Joystick: public Joystick { //This class is our customization of 'class Joystick'.
public:
	float GetZWithDeadZone(float deadZone);
};



#endif /* SRC_TEAM2342JOYSTICK_H_ */
