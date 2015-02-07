/*
 * DriveStabilize.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: Ray
 */

#include "WPILib.h"
#include "DriveStabilize.h"


DriveStabilize::DriveStabilize(Gyro * gyro, float referenceAngle, float scale){
    m_gyro = gyro;
    m_referenceAngle = referenceAngle;
    m_scale = scale;
}

void DriveStabilize::SetReferenceAngle(float newAngle){
    m_referenceAngle = newAngle;
}


float DriveStabilize::GetCorrectionAngle(){
    return (m_referenceAngle - m_gyro->GetAngle())*m_scale;
}

DriveStabilize::~DriveStabilize(){

}
