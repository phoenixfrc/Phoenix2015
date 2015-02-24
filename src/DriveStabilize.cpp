/*
 * DriveStabilize.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: ben
 */

#include "DriveStabilize.h"


DriveStabilize::DriveStabilize(Gyro * gyro, EncoderTracker * tracker, Team2342Joystick * stick,
                               float goalAngle, float turnSpeed, float correction, float xLock, float yLock){
    m_gyro = gyro;
    m_stick = stick;
    m_tracker = tracker;

    m_goalAngle = goalAngle;
    m_turnSpeed = turnSpeed;
    m_correction = correction;

    m_xLock = xLock;
    m_yLock = yLock;
}

void DriveStabilize::UpdateGoalAngle(){
    m_goalAngle += m_stick->GetZWithDeadZone(0.1)*m_turnSpeed;
}


float DriveStabilize::GetCorrectionAngle(){
    //UpdateGoalAngle();
    return (m_goalAngle - m_gyro->GetAngle())*m_correction;
}


void DriveStabilize::SetGoalAngle(float GoalAngle)
{
	m_goalAngle = GoalAngle;
}

float DriveStabilize::LockX(){
    return - m_tracker->GetX()*m_xLock;
}

float DriveStabilize::LockY(){
    return m_tracker->GetY()*m_yLock;//Probably should be negative, but maybe not? (test)
}


DriveStabilize::~DriveStabilize(){

}




