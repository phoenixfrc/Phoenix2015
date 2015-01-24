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
    EncoderTracker();

    //Call to restart the encoder tracking system:
    void ResetPosition(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    //Main function (should be called in Robot.cpp loop):
    void TrackPosition(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    //Functions that Kurtis should care about (the return value is currently in ticks):
    float GetX();
    float GetY();

    //Base functions (contains the algorithms):
    float GetDeltaX(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);
    float GetDeltaY(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    ~EncoderTracker();

private:

    void UpdateEncoders(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    float m_xPos;
    float m_yPos;
    int32_t m_FLTicks;
    int32_t m_FRTicks;
    int32_t m_BLTicks;
    int32_t m_BRTicks;
    int32_t m_OldFLTicks;
    int32_t m_OldFRTicks;
    int32_t m_OldBLTicks;
    int32_t m_OldBRTicks;
};


#endif /* ENCODERTRACKER_H_ */