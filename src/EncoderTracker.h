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

    void ResetPosition();
    void TrackPosition();

    float GetX();
    float GetY();

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

    float ticksToInchY;
    float ticksToInchX;
};


#endif /* ENCODERTRACKER_H_ */
