/*
 * EncoderTracker.h
 *
 *  Created on: Jan 20, 2015
 *      Author: Ray
 */

#ifndef ENCODERTRACKER_H_
#define ENCODERTRACKER_H_

#include "WPILib.h"

class EncoderTracker {
public:
    //Initializes with 4 encoders (assumes they are attached to mecanum wheels).
    EncoderTracker(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    //Call to restart the encoder tracking system:
    void ResetPosition();

    //Main function (should be called in Robot.cpp loop):
    void TrackPosition();

    //Functions that Kurtis should care about (the return value is currently in inches):
    float GetX();
    float GetY();

    //For testing:
    float GetTicks();

    //Base functions (contain the algorithms):
    float GetDeltaX();
    float GetDeltaY();

    ~EncoderTracker();

private:

    void UpdateEncoders();

    float m_xPos;
    float m_yPos;

    Encoder * m_frontLeft;
    Encoder * m_frontRight;
    Encoder * m_backLeft;
    Encoder * m_backRight;

    int32_t m_FLTicks;
    int32_t m_FRTicks;
    int32_t m_BLTicks;
    int32_t m_BRTicks;
    int32_t m_OldFLTicks;
    int32_t m_OldFRTicks;
    int32_t m_OldBLTicks;
    int32_t m_OldBRTicks;

    //Wheel results Forward:
    //Partially known. (old const was 20.5697)

    //(estimates):
    const float FConvFR = 0.04861519613800881879657943479973;
    const float FConvFL = 0.04861519613800881879657943479973;
    const float FConvBR = 0.04861519613800881879657943479973;
    const float FConvBL = 0.04861519613800881879657943479973;

    //Wheel results Backwards:
    //???

    //(estimates):
    const float BConvFR = 0.04861519613800881879657943479973;
    const float BConvFL = 0.04861519613800881879657943479973;
    const float BConvBR = 0.04861519613800881879657943479973;
    const float BConvBL = 0.04861519613800881879657943479973;


    //Wheel results Right: (4 feet driven, 48 inches)
    //Right Front: 931.2
    //Left Front: 942.6
    //Right Back: 1127.6
    //Left Back: 1437.2

    const float RConvFR = 0.05154639175257731958762886597938;//(48/931.2)
    const float RConvFL = 0.0509229789942711648631444939529;//(48/942.6)
    const float RConvBR = 0.04256828662646328485278467541681;//(48/1127.6)
    const float RConvBL = 0.03339827442248817144447536877261;//(48/1437.2)

    //Wheel results Left:
    //???

    //(estimates):
    const float LConvFR = 0.05154639175257731958762886597938;//(48/931.2)
    const float LConvFL = 0.0509229789942711648631444939529;//(48/942.6)
    const float LConvBR = 0.04256828662646328485278467541681;//(48/1127.6)
    const float LConvBL = 0.03339827442248817144447536877261;//(48/1437.2)


    //const float ticksToInchesX = 24.51875;
};


#endif /* ENCODERTRACKER_H_ */
