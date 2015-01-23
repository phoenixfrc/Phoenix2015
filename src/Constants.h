/*
 * Constants.h
 *
 *  Created on: Jan 11, 2015
 *      Author: Ray
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "WPILib.h"

struct PortAssign
{

    //Dragger Ports:
	static const uint32_t draggerMotorPort = 1;
	static const uint32_t limitSwitchUpPort = 1;
	static const uint32_t limitSwitchDownPort = 2;
	//DIO ports
	static const uint32_t driveEncoder1ChannelA = 0;
	static const uint32_t driveEncoder1ChannelB = 1;
	static const uint32_t driveEncoder2ChannelA = 2;
	static const uint32_t driveEncoder2ChannelB = 3;
	static const uint32_t driveEncoder3ChannelA = 4;
	static const uint32_t driveEncoder3ChannelB = 5;
	static const uint32_t driveEncoder4ChannelA = 6;
	static const uint32_t driveEncoder4ChannelB = 7;
	static const int32_t gyroChannel = 0;

    //Drive Train Ports:
    static const uint32_t rearLeftChannel   = 0;
    static const uint32_t frontLeftChannel  = 1;
    static const uint32_t frontRightChannel = 2;
    static const uint32_t rearRightChannel  = 3;

    //Joystick Ports:
    static const uint32_t joystickChannel = 0;
    static const uint32_t gamepadChannel  = 1;

};



#endif /* SRC_CONSTANTS_H_ */
