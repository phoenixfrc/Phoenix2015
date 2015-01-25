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
	//Elevator Ports
	static const uint32_t ElevatorMotor1 = 4;
	static const uint32_t ElevatorMotor2 = 5;
    //Dragger Ports:
	static const uint32_t draggerMotorPort = 1;
	static const uint32_t limitSwitchUpPort = 1;
	static const uint32_t limitSwitchDownPort = 2;
	//DIO ports
	static const uint32_t leftRearDriveEncoderChannelA = 0;
	static const uint32_t leftRearDriveEncoderChannelB = 1;
	static const uint32_t leftFrontDriveEncoderChannelA = 2;
	static const uint32_t leftFrontDriveEncoderChannelB = 3;
	static const uint32_t rightFrontDriveEncoderChannelA = 4;
	static const uint32_t rightFrontDriveEncoderChannelB = 5;
	static const uint32_t rightRearDriveEncoderChannelA = 6;
	static const uint32_t rightRearDriveEncoderChannelB = 7;
	static const int32_t gyroChannel = 0;

    //Drive Train Ports:
    static const uint32_t rearLeftChannel   = 0;
    static const uint32_t frontLeftChannel  = 1;
    static const uint32_t frontRightChannel = 2;
    static const uint32_t rearRightChannel  = 3;

    //Joystick Ports:
    static const uint32_t joystickChannel = 0;
    static const uint32_t gamepadChannel  = 1;

    //Elevator Ports:
    static const uint32_t ElevatorEncoderChannelA = 8;
    static const uint32_t ElevatorEncoderChannelB = 9;

};



#endif /* SRC_CONSTANTS_H_ */
