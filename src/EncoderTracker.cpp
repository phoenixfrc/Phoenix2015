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

void EncoderTracker::TrackPosition (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight, float wheelRad) {
    //I have no hope for the following system, but at least it's a start...
    float wheelDiameter = wheelRad*2;


    float ticksToRotations = 0.002604167;
    float PI = 3.14159265;

    float multiplier = ticksToRotations*wheelDiameter*PI/4;

    m_yPos += (frontLeft->GetRate() + frontRight->GetRate() + backLeft->GetRate() + backRight->GetRate())*multiplier;
    m_xPos += (frontLeft->GetRate() - frontRight->GetRate() - backLeft->GetRate() + backRight->GetRate())*multiplier;
}

EncoderTracker::~EncoderTracker(){

}
