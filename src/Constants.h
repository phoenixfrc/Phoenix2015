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
    //Dragger Ports:
    static const uint32_t DraggerMotorPort = 6;


    // relay ports
    // relay port 0 is unused
    //Elevator Ports:
    static const uint32_t ElevatorBrakeChannel = 1;

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
    static const uint32_t DIO11Channel = 11; //Does not exist
    static const uint32_t ElevatorUpperLimitChannel = 12;
    static const uint32_t DraggerActivatedLimitChannel = 13;
    static const uint32_t DraggerUpperLimitChannel = 18;

    //MXP Breakout board doesn't expose ports: 14-17
    static const uint32_t DIO14Channel = 14;
    static const uint32_t DIO15Channel = 15;
    static const uint32_t DIO16Channel = 16;
    static const uint32_t DIO17Channel = 17;
   // static const uint32_t DIO18Channel = 18;
    static const uint32_t DIO19Channel = 19;
    static const uint32_t DIO20Channel = 20;
    static const uint32_t DIO21Channel = 21;
    static const uint32_t DIO22Channel = 22;
    static const uint32_t DIO23Channel = 23;
    static const uint32_t DIO24Channel = 24;
    static const uint32_t DIO25Channel = 25;

    // analog
    static const int32_t GyroChannel = 0;
    static const uint32_t IRLeftInnerChannel = 3;//tba //current port numbers for test board
    static const uint32_t IRLeftOuterChannel = 4;//tba
    static const uint32_t IRRightInnerChannel = 2;//tba
    static const uint32_t IRRightOuterChannel = 1;//tba


    //Joystick Ports:
    static const uint32_t JoystickChannel = 0;
    static const uint32_t GamepadChannel  = 1;
};

struct FieldDistances
{

	static const int shortAutoDiff = 100;
    //Distance between the crates we have to pick up during auto
    static const int autoCrateDiff = 81+16; // This number comes from the manual but may be a little off
    //Added 8 in order to correct for decreased distance during testing (thus far unexplained)
    //Distance from start to the auto zone
    static const int simpleIntoAutoDiff = 128;//from the manual
    static const int complexIntoAutoDiff = 140 + 40;//This number comes from the manual but may be a little off
    static const int shortIntoAutoDiff = 64;
    //Distance to move before lifting over container
    static const int shiftDiff = 3;
    //Distance to back away from totes after dropping them.
    static const int backOffDiff = -5;
    //Distance to Push totes forward before pickup
    static const int pushDiff = 9;
    //Distance to move left, after lifting upwards and right, before beginning elevator motion
    static const int rightElevatorDistance = 49;
    //Distance to move back initially, to avoid hitting totes
    static const int moveBack = -4;
};

struct Tolerances
{
	static const int moveTolerance = 2;
};


struct ObjectSizes
{
    //Height of an individual tote
    static const int toteHeight = 2; //This is a filler number
    //Height of an individual barrel
    static const int barrelHeight = 4; //This is a filler number
};

#endif /* SRC_CONSTANTS_H_ */
