/*
 * driveStabilize.h
 *
 *  Created on: Feb 3, 2015
 *      Author: Ray
 */

#include "WPILib.h"

#ifndef SRC_DRIVESTABILIZE_H_
#define SRC_DRIVESTABILIZE_H_


class DriveStabilize {
public:
    DriveStabilize(Gyro * gyro, Joystick * stick, float goalAngle, float turnSpeed, float correction);

    void UpdateGoalAngle();

    float GetCorrectionAngle();

    ~DriveStabilize();
private:
    Gyro * m_gyro;
    Joystick * m_stick;
    float m_goalAngle;
    const float m_turnSpeed;
    const float m_correction;
};


#endif /* SRC_DRIVESTABILIZE_H_ */
