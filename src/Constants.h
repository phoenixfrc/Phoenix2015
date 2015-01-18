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
    static const int leftJoystickID  = 1;
    static const int rightJoystickID = 2;
    static const int gamePadID       = 3;

    //Dragger Ports:
    static const int draggerMotorPort    = 1;
    static const int limitSwitchUpPort   = 1;
    static const int limitSwitchDownPort = 2;

    //Drive Train Ports:
    const static int rearLeftChannel   = 0;
    const static int frontLeftChannel  = 1;
    const static int frontRightChannel = 2;
    const static int rearRightChannel  = 3;

    //Joystick Ports:
    const static int joystickChannel = 0;
    const static int gamepadChannel  = 1;

    //DIO Ports:
    const static int testEncoderChannelA = 1;
    const static int testEncoderChannelB = 2;
};



#endif /* SRC_CONSTANTS_H_ */
