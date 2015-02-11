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
    EncoderTracker(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    //Call to restart the encoder tracking system:
    void ResetPosition();

    //Main function (should be called in Robot.cpp loop):
    void TrackPosition();

    //Functions that Kurtis should care about (the return value is currently in inches):
    float GetX();
    float GetY();

    //Base functions (contain the algorithms):
    float GetDeltaX();
    float GetDeltaY();

    virtual ~EncoderTracker(){};

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

    const float ticksToInchesY = 20.5697;
    const float ticksToInchesX = 24.51875;
};


#endif /* ENCODERTRACKER_H_ */
