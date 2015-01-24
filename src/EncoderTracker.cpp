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
    m_FLTicks = 0;
    m_FRTicks = 0;
    m_BLTicks = 0;
    m_BRTicks = 0;
    m_OldFLTicks = 0;
    m_OldFRTicks = 0;
    m_OldBLTicks = 0;
    m_OldBRTicks = 0;
}

void EncoderTracker::ResetPosition (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight) {
    //Reset the position:
    m_xPos = 0;
    m_yPos = 0;

    //Reset all the ticks variables:
    m_FLTicks = 0;
    m_FRTicks = 0;
    m_BLTicks = 0;
    m_BRTicks = 0;
    m_OldFLTicks = 0;
    m_OldFRTicks = 0;
    m_OldBLTicks = 0;
    m_OldBRTicks = 0;

    frontLeft->Reset();
    frontRight->Reset();
    backLeft->Reset();
    backRight->Reset();
}

void EncoderTracker::TrackPosition (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight) {
    //Get the up-to-date encoder values:
    this->UpdateEncoders(frontLeft, frontRight, backLeft, backRight);

    //Change the positions accordingly:
    m_xPos += this->GetDeltaX(frontLeft, frontRight, backLeft, backRight);
    m_yPos += this->GetDeltaY(frontLeft, frontRight, backLeft, backRight);
}

float EncoderTracker::GetX () {
    //return the x position (in ticks):
    return m_xPos;
}

float EncoderTracker::GetY () {
    //return the y position (in ticks):
    return m_yPos;
}


float EncoderTracker::GetDeltaX (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight) {
    //Get the difference (in ticks):
    float FLChange = m_FLTicks - m_OldFLTicks;
    float FRChange = m_FRTicks - m_OldFRTicks;
    float BLChange = m_BLTicks - m_OldBLTicks;
    float BRChange = m_BRTicks - m_OldBRTicks;


    //Algorithm for X movement (needs work):
    return (FLChange - FRChange - BLChange + BRChange)/4;
}

float EncoderTracker::GetDeltaY (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight) {
    //Get difference:
    float FLChange = m_FLTicks - m_OldFLTicks;
    float FRChange = m_FRTicks - m_OldFRTicks;
    float BLChange = m_BLTicks - m_OldBLTicks;
    float BRChange = m_BRTicks - m_OldBRTicks;

    //Algorithm for Y movement (needs work):
    return (FLChange + FRChange + BLChange + BRChange)/4;
}


void EncoderTracker::UpdateEncoders(Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight){
    //Update all the tick variables:
    m_OldFLTicks = m_FLTicks;
    m_FLTicks = frontLeft->Get();

    m_OldFRTicks = m_FRTicks;
    m_FRTicks = frontRight->Get();

    m_OldBLTicks = m_BLTicks;
    m_BLTicks = backLeft->Get();

    m_OldBRTicks = m_BRTicks;
    m_BRTicks = backRight->Get();
}


EncoderTracker::~EncoderTracker(){

}
