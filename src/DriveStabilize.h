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


enum LockAxis {
    xAxis,
    yAxis,
    none
};


class DriveStabilize : public PIDOutput, public PIDSource {
public:
    DriveStabilize(Gyro * gyro, EncoderTracker * tracker, Team2342Joystick * stick,
                   float goalAngle, float turnSpeed, float correction = 1.0);

    void UpdateGoalAngle();

    float GetCorrectionAngle();

    void SetGoalAngle(float GoalAngle);

    float LockX();

    float LockY();

    void StopPID();

    void StartPID();

    void SetLockAxis(LockAxis axis);

    virtual void PIDWrite(float output);

    virtual double PIDGet();

    ~DriveStabilize();
private:
    Gyro * m_gyro;
    Team2342Joystick * m_stick;
    EncoderTracker * m_tracker;

    PIDController m_xLockPID;
    PIDController m_yLockPID;

    LockAxis m_lockedAxis;

    float m_goalAngle;
    float m_turnSpeed;
    float m_correction;

    double m_xLock;
    double m_yLock;
};



#endif /* SRC_DRIVESTABILIZE_H_ */

