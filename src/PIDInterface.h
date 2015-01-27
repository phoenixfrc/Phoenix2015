#ifndef PID_INTERFACE_H
#define PID_INTERFACE_H
#include "WPILib.h"

enum Axis {
    x,
    y
};

class PIDInterface : public PIDOutput, public PIDSource {
public:
    PIDInterface(RobotDrive * robotDrive, Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    virtual void PIDWrite(float output);
    virtual double PIDGet();
    void Reset();
    void SetGoal(double xGoalDistance, double yGoalDistance);

    virtual ~PIDInterface();

private:
    EncoderTracker m_tracker;
    RobotDrive * m_robotDrive;
    PIDController xPID;
    PIDController yPID;
    Axis m_currentAxis;
};

#endif
