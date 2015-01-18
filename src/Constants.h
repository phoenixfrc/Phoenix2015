/*
 * Constants.h
 *
 *  Created on: Jan 11, 2015
 *      Author: Ray
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_


struct PortAssign
{
    //Joystick Ports
    static const int gamePadChannel = 3;
    const static int joystickChannel	= 0;
    //Drive Train Talon Ports
    const static int frontLeftChannel	= 3;
    const static int rearLeftChannel	= 0;
    const static int frontRightChannel	= 1;
    const static int rearRightChannel	= 2;

    //Dragger Ports:
	 const static int draggerMotorPort = 1;
	 const static int limitSwitchUpPort = 1;
	 const static int limitSwitchDownPort = 2;
	 //DIO ports
	 const static int driveEncoder1ChannelA = 0;
	 const static int driveEncoder1ChannelB = 1;
	 const static int driveEncoder2ChannelA = 2;
	 const static int driveEncoder2ChannelB = 3;
	 const static int driveEncoder3ChannelA = 4;
	 const static int driveEncoder3ChannelB = 5;
	 const static int driveEncoder4ChannelA = 6;
	 const static int driveEncoder4ChannelB = 7;
	 const static int gyroChannel = 0;
	 const static int gamepadChannel = 1;
};



#endif /* SRC_CONSTANTS_H_ */
