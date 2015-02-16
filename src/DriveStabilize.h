/*
 * DriveStabilize.h
 *
 *  Created on: Feb 16, 2015
 *      Author: ben
 */

#ifndef SRC_DRIVESTABILIZE_H_
#define SRC_DRIVESTABILIZE_H_
#include "WPILib.h"
#include "Team2342Joystick.h"


class DriveStabilize {
public:
    DriveStabilize(Gyro * gyro, Team2342Joystick * stick, float goalAngle, float turnSpeed, float correction);

    void UpdateGoalAngle();

    float GetCorrectionAngle();

    void SetGoalAngle(float GoalAngle);

    ~DriveStabilize();
private:
    Gyro * m_gyro;
    Team2342Joystick * m_stick;
    float m_goalAngle;
    float m_turnSpeed;
    float m_correction;
};



#endif /* SRC_DRIVESTABILIZE_H_ */

