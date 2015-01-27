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
    EncoderTracker::EncoderTracker(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    void ResetPosition();
    void TrackPosition();
    float GetX();
    float GetY();
    float GetDeltaX();
    float GetDeltaY();

    EncoderTracker::~EncoderTracker();

private:
    float m_xPos;
    float m_yPos;
    Encoder * m_frontLeft;
    Encoder * m_frontRight;
    Encoder * m_backLeft;
    Encoder * m_backRight;
};


#endif /* ENCODERTRACKER_H_ */
