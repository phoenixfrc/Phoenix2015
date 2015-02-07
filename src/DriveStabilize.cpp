/*
 * DriveStabilize.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: Ray
 */

#include "WPILib.h"
#include "DriveStabilize.h"


DriveStabilize::DriveStabilize(Gyro * gyro, Joystick * stick, float referenceAngle, float scale){
    m_gyro = gyro;
    m_stick = stick;
    m_goalAngle = referenceAngle;
    m_scale = scale;
}

void DriveStabilize::UpdateGoalAngle(float newAngle){
    m_goalAngle += m_stick->GetZ();
}


float DriveStabilize::GetCorrectionAngle(){
    return (m_goalAngle - m_gyro->GetAngle())*m_scale;
}

DriveStabilize::~DriveStabilize(){

}
