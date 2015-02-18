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
#include "EncoderTracker.h"


class DriveStabilize {
public:
    DriveStabilize(Gyro * gyro, EncoderTracker * tracker, Team2342Joystick * stick,
                   float goalAngle, float turnSpeed, float correction = 1.0, float xLock = 1.0, float yLock = 1.0);

    void UpdateGoalAngle();

    float GetCorrectionAngle();

    void SetGoalAngle(float GoalAngle);

    float LockX();

    float LockY();

    ~DriveStabilize();
private:
    Gyro * m_gyro;
    Team2342Joystick * m_stick;
    EncoderTracker * m_tracker;

    float m_goalAngle;
    float m_turnSpeed;
    float m_correction;

    float m_xLock;
    float m_yLock;
};



#endif /* SRC_DRIVESTABILIZE_H_ */

