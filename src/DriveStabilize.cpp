/*
 * DriveStabilize.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: Ray
 */

#include "WPILib.h"
#include "DriveStabilize.h"


DriveStabilize::DriveStabilize(Gyro * gyro, Joystick * stick, float goalAngle, float turnSpeed, float correction = 1.0){
    m_gyro = gyro;
    m_stick = stick;
    m_goalAngle = goalAngle;
    m_turnSpeed = turnSpeed;
    m_correction = correction;
}

void DriveStabilize::UpdateGoalAngle(){
    m_goalAngle += m_stick->GetZ()*m_turnSpeed;
}


float DriveStabilize::GetCorrectionAngle(){
    return (m_goalAngle - m_gyro->GetAngle())*m_correction;
}

DriveStabilize::~DriveStabilize(){

}
