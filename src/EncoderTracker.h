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
    EncoderTracker::EncoderTracker();

    void ResetPosition();
    void TrackPosition(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight, float wheelRadius);

    EncoderTracker::~EncoderTracker();

private:
    float m_xPos;
    float m_yPos;
};


#endif /* ENCODERTRACKER_H_ */
