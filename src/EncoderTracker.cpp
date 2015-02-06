/*
 * EncoderTracker.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: Ray
 */

#include "EncoderTracker.h"
#include "WPILib.h"


//Ticks to Inches conversion rates:
static const float FrontConv = 0.048615;////Forwards
static const float BackConv = 0.048615;//Backwards, (using the same value as Forwards for now)
static const float RightConv = 0.0446045;//Right
static const float LeftConv = 0.0446045;//Left, (using the same value as Right for now)
//old X const (was 24.51875) didn't work well.


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

    //Resets the Encoders:
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

    float d = (float)(FRChange - FLChange - BRChange + BLChange) / 4;

    //Algorithm for X movement (needs work):
    if (d > 0){
        //if moving to the left:
        return d * LeftConv;
    } else {
        //if moving to the right:
        return d * RightConv;
    }
}

float EncoderTracker::GetDeltaY () {
    //Get difference (in ticks):
    float FLChange = m_FLTicks - m_OldFLTicks;
    float FRChange = m_FRTicks - m_OldFRTicks;
    float BLChange = m_BLTicks - m_OldBLTicks;
    float BRChange = m_BRTicks - m_OldBRTicks;

    float d = (float)(FRChange + FLChange + BRChange + BLChange) / 4;

    //Algorithm for Y movement (needs work):
    if (d > 0){
        //if moving forward:
        return d * RightConv;
    } else {
        //if moving backward:
        return d * LeftConv;
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
