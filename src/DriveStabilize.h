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
    DriveStabilize(Gyro * gyro, Joystick * stick, float referenceAngle, float scale = 1.0);

    void UpdateGoalAngle(float newAngle);

    float GetCorrectionAngle();

    ~DriveStabilize();
private:
    Gyro * m_gyro;
    Joystick * m_stick;
    float m_goalAngle;
    float m_scale;
};


#endif /* SRC_DRIVESTABILIZE_H_ */
