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
    static const int gamePadID = 3;
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

struct RobotSpecs
{
    //Speed of the robot in inches per second
    static const int driveSpeed = 2; //This is a filler number
};

#endif /* SRC_CONSTANTS_H_ */
