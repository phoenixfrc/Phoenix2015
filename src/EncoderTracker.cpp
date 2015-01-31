/*
 * EncoderTracker.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: Ray
 */

#include "EncoderTracker.h"
#include "WPILib.h"

EncoderTracker::EncoderTracker (Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight){
    m_xPos = 0;
    m_yPos = 0;

    m_frontLeft = frontLeft;
    m_frontRight = frontRight;
    m_backLeft = backLeft;
    m_backRight = backRight;

    m_FLTicks = 0;
    m_FRTicks = 0;
    m_BLTicks = 0;
    m_BRTicks = 0;

    m_OldFLTicks = 0;
    m_OldFRTicks = 0;
    m_OldBLTicks = 0;
    m_OldBRTicks = 0;
}

void EncoderTracker::ResetPosition () {
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
    m_frontLeft->Reset();
    m_frontRight->Reset();
    m_backLeft->Reset();
    m_backRight->Reset();
}

void EncoderTracker::TrackPosition () {
    //Get the up-to-date encoder values:
    this->UpdateEncoders();

    //Change the positions accordingly:
    m_xPos += this->GetDeltaX();
    m_yPos += this->GetDeltaY();
}

float EncoderTracker::GetX () {
    //return the x position (in inches):
    return m_xPos;
}

float EncoderTracker::GetY () {
    //return the y position (in inches):
    return m_yPos;
}

float EncoderTracker::GetTicks(){
    return m_FRTicks;
}

float EncoderTracker::GetDeltaX () {
    //Get the difference (in ticks):
    float FLChange = m_FLTicks - m_OldFLTicks;
    float FRChange = m_FRTicks - m_OldFRTicks;
    float BLChange = m_BLTicks - m_OldBLTicks;
    float BRChange = m_BRTicks - m_OldBRTicks;

    //Algorithm for X movement (needs work):
    if (FRChange - FLChange - BRChange + BLChange > 0){
        return (float)(FRChange*LConvFR - FLChange*LConvFL - BRChange*LConvBR + BLChange*LConvBL) / 4;
    } else {
        return - (float)(FRChange*RConvFR - FLChange*RConvFL - BRChange*RConvBR + BLChange*RConvBL) / 4;
    }
}

float EncoderTracker::GetDeltaY () {
    //Get difference (in ticks):
    float FLChange = m_FLTicks - m_OldFLTicks;
    float FRChange = m_FRTicks - m_OldFRTicks;
    float BLChange = m_BLTicks - m_OldBLTicks;
    float BRChange = m_BRTicks - m_OldBRTicks;


    //Algorithm for Y movement (needs work):
    if (FRChange + FLChange + BRChange + BLChange > 0){
        return (float)(FRChange*FConvFR + FLChange*FConvFL + BRChange*FConvBR + BLChange*FConvBL) / 4;
    } else {
        return - (float)(FRChange*BConvFR + FLChange*BConvFL + BRChange*BConvBR + BLChange*BConvBL) / 4;
    }
}


void EncoderTracker::UpdateEncoders(){
    //Update all the tick variables:
    m_OldFLTicks = m_FLTicks;
    m_FLTicks = m_frontLeft->Get();

    m_OldFRTicks = m_FRTicks;
    m_FRTicks = m_frontRight->Get();

    m_OldBLTicks = m_BLTicks;
    m_BLTicks = m_backLeft->Get();

    m_OldBRTicks = m_BRTicks;
    m_BRTicks = m_backRight->Get();
}


EncoderTracker::~EncoderTracker(){

}
