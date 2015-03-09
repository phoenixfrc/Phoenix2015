/*
 * DriveStabilize.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: ben
 */

#include "DriveStabilize.h"


DriveStabilize::DriveStabilize(Gyro * gyro, EncoderTracker * tracker, Team2342Joystick * stick,
                               float goalAngle, float turnSpeed, float correction):
                               m_xLockPID(0.25, 0.0, 0.0, this, this),//0.25 is from the P control loop in Robot.cpp
                               m_yLockPID(0.6, 0.0, 0.0, this, this)//0.6 is from the P control loop in Robot.cpp
{
    m_gyro = gyro;
    m_stick = stick;
    m_tracker = tracker;

    m_goalAngle = goalAngle;
    m_turnSpeed = turnSpeed;
    m_correction = correction;

    m_xLock = 0;
    m_yLock = 0;

    m_lockedAxis = xAxis;
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
    return m_xLock;
}

float DriveStabilize::LockY(){
    return m_yLock;
}

void DriveStabilize::StopPID(){
    if (m_xLockPID.IsEnabled()){
       m_xLockPID.Disable();
   }
   if (m_yLockPID.IsEnabled()){
       m_yLockPID.Disable();
   }
}

void DriveStabilize::StartPID(){
   StopPID();
   switch (m_lockedAxis){
       case xAxis:
           if (!m_xLockPID.IsEnabled()){
               m_xLockPID.Enable();
           }
           break;
       case yAxis:
           if (!m_xLockPID.IsEnabled()){
               m_xLockPID.Enable();
           }
           break;
       case none:
           break;
   }
}

void DriveStabilize::SetLockAxis(LockAxis axis){
    m_lockedAxis = axis;
}

void DriveStabilize::PIDWrite(float output){
    switch (m_lockedAxis){
        case xAxis:
            m_xLock += output;
            break;
        case yAxis:
            m_yLock += output;
            break;
        case none:
            break;
    }
}

double DriveStabilize::PIDGet(){
    switch (m_lockedAxis){
        case xAxis:
            return m_tracker->GetX();
            break;
        case yAxis:
            return m_tracker->GetY();
            break;
        default:
        case none:
            return 0.0;//This is a little dangerous, but it should be okay.
    }

}


DriveStabilize::~DriveStabilize(){

}




