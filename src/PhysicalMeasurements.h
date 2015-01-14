#ifndef PHYS_MEASUREMENTS_H
#define PHYS_MEASUREMENTS_H

//This file is for storing any physical measurements such as relative distances on the field

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

#endif
