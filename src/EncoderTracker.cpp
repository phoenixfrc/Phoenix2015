/*
 * EncoderTracker.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: Ray
 */

#include "EncoderTracker.h"
#include "WPILib.h"

EncoderTracker::EncoderTracker (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight) {
    m_xPos = 0;
    m_yPos = 0;
    m_frontLeft = frontLeft;
    m_frontRight = frontRight;
    m_backLeft = backLeft;
    m_backRight = backRight;
}

void EncoderTracker::ResetPosition () {
    m_xPos = 0;
    m_yPos = 0;
}

void EncoderTracker::TrackPosition () {
    m_xPos += this->GetDeltaX();
    m_yPos += this->GetDeltaY();
}

float EncoderTracker::GetX () {
    return m_xPos;
}

float EncoderTracker::GetY () {
    return m_yPos;
}

float EncoderTracker::GetDeltaX () {
    //Algorithm for X movement (needs work):
    return (m_frontLeft->GetRate() - m_frontRight->GetRate() - m_backLeft->GetRate() + m_backRight->GetRate())/4;
}

float EncoderTracker::GetDeltaY () {
    //Algorithm for Y movement (needs work):
    return (m_frontLeft->GetRate() + m_frontRight->GetRate() + m_backLeft->GetRate() + m_backRight->GetRate())/4;
}


EncoderTracker::~EncoderTracker(){

}
