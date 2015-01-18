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
	Team2342Joystick(uint32_t port);
	float GetZWithDeadZone(float deadZone);
};



#endif /* SRC_TEAM2342JOYSTICK_H_ */
