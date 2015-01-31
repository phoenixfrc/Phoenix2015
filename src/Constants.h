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

    // PWM ports
    //Drive Train Ports:
    static const uint32_t RearLeftChannel   = 0;
    static const uint32_t FrontLeftChannel  = 1;
    static const uint32_t FrontRightChannel = 2;
    static const uint32_t RearRightChannel  = 3;
    //Elevator Motor Ports
    static const uint32_t ElevatorMotor1 = 4;
    static const uint32_t ElevatorMotor2 = 5;

    // relay ports
    //Dragger Ports:
    static const uint32_t DraggerMotorPort = 6;

    //Elevator Ports:
     static const uint32_t ElevatorBrakeChannel = 1;//placeholder value.

    //DIO ports
    static const uint32_t LeftRearDriveEncoderChannelA = 0;
    static const uint32_t LeftRearDriveEncoderChannelB = 1;
    static const uint32_t LeftFrontDriveEncoderChannelA = 2;
    static const uint32_t LeftFrontDriveEncoderChannelB = 3;
    static const uint32_t RightFrontDriveEncoderChannelA = 4;
    static const uint32_t RightFrontDriveEncoderChannelB = 5;
    static const uint32_t RightRearDriveEncoderChannelA = 6;
    static const uint32_t RightRearDriveEncoderChannelB = 7;
    static const uint32_t ElevatorEncoderChannelA = 8;
    static const uint32_t ElevatorEncoderChannelB = 9;
    static const uint32_t ElevatorLowerLimitChannel = 10;
    static const uint32_t ElevatorUpperLimitChannel = 11;
    static const uint32_t ElevatorHomeSwitchChannel = 12;
    static const uint32_t OpticalSensorChannel = 13;
    static const uint32_t DraggerLowerLimitChannel = 14;
    static const uint32_t DraggerUpperLimitChannel = 15;
    static const uint32_t DIO16Channel = 16;
    static const uint32_t DIO17Channel = 17;
    static const uint32_t DIO18Channel = 18;
    static const uint32_t DIO19Channel = 19;
    static const uint32_t DIO20Channel = 20;
    static const uint32_t DIO21Channel = 21;
    static const uint32_t DIO22Channel = 22;
    static const uint32_t DIO23Channel = 23;
    static const uint32_t DIO24Channel = 24;
    static const uint32_t DIO25Channel = 25;

    // analog
    static const int32_t GyroChannel = 0;

    //Joystick Ports:
    static const uint32_t JoystickChannel = 0;
    static const uint32_t GamepadChannel  = 1;
};

struct FieldDistances
{
    //Distance between the crates we have to pick up during auto
    static const int autoCrateDiff = 5; //This is a filler number
    //Distance from start to the auto zone
    static const int intoAutoDiff = 10; //This is a filler number
};

struct ObjectSizes
{
    //Height of an individual tote
    static const int toteHeight = 2; //This is a filler number
    //Height of an individual barrel
    static const int barrelHeight = 4; //This is a filler number
};

#endif /* SRC_CONSTANTS_H_ */
