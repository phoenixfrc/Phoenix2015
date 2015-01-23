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
    //Joystick Ports:
    static const int leftJoystickID  = 1;
    static const int rightJoystickID = 2;
    static const int gamePadID = 3;
    //DIO Ports:
    static const int ElevatorEncoderChannelA = 8;
    static const int ElevatorEncoderChannelB = 9;

    static const int ElevatorLowerLimitChannel = 10;
    static const int ElevatorUpperLimitChannel = 11;
    static const int ElevatorHomeSwitchChannel = 12;

    //Elevator Motor Ports (PWN):
    static const int ElevatorMotorPort1 = 4;
    static const int ElevatorMotorPort2 = 5;

};

#endif /* SRC_CONSTANTS_H_ */
