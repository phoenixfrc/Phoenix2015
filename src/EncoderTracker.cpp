/*
 * EncoderTracker.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: Ray
 */

#include "EncoderTracker.h"
#include "WPILib.h"

EncoderTracker::EncoderTracker () {
    m_xPos = 0;
    m_yPos = 0;
}

void EncoderTracker::ResetPosition () {
    m_xPos = 0;
    m_yPos = 0;
}

void EncoderTracker::TrackPosition (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight) {
    m_xPos += this->GetDeltaX(frontLeft, frontRight, backLeft, backRight);
    m_yPos += this->GetDeltaY(frontLeft, frontRight, backLeft, backRight);
}

float EncoderTracker::GetX () {
    return m_xPos;
}

float EncoderTracker::GetY () {
    return m_yPos;
}

float EncoderTracker::GetDeltaX (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight) {
    //Algorithm for X movement (needs work):
    return (frontLeft->GetRate() - frontRight->GetRate() - backLeft->GetRate() + backRight->GetRate())/4;
}

float EncoderTracker::GetDeltaY (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight) {
    //Algorithm for Y movement (needs work):
    return (frontLeft->GetRate() + frontRight->GetRate() + backLeft->GetRate() + backRight->GetRate())/4;
}


EncoderTracker::~EncoderTracker(){

}
