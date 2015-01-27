#ifndef PID_INTERFACE_H
#define PID_INTERFACE_H
#include "WPILib.h"
#include "EncoderTracker.h"

enum AxisOfMotion {
    right,
    forward
};

//Only supports L-shaped motion along the x and y axis (one axis at a time)
//TODO: set PID output scaling (needs to be between -1 and 1)
class PIDInterface : public PIDOutput, public PIDSource {
public:
    PIDInterface(RobotDrive * robotDrive, Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight);

    //Required by PIDOutput; This function sends the output to the robotDrive
    virtual void PIDWrite(float output);
    //Required by PIDSource; This function takes the values from the tracker and gives it to the PID loop
    virtual double PIDGet();

    //My functions
    void Reset(); //Sets current location to 0
    void SetGoal(double xGoalDistance, double yGoalDistance);

    virtual ~PIDInterface();

private:
    EncoderTracker m_tracker;
    RobotDrive * m_robotDrive;
    PIDController xPID;
    PIDController yPID;
    AxisOfMotion m_currentAxis;
};

#endif
