#ifndef PID_INTERFACE_H
#define PID_INTERFACE_H
#include "WPILib.h"
#include "EncoderTracker.h"
#include "DriveStabilize.h"

enum AxisOfMotion {
    right,
    forward,
	stop
};

//Only supports L-shaped motion along the x and y axis (one axis at a time)
class PIDInterface : public PIDOutput, public PIDSource {
public:
    PIDInterface(RobotDrive * robotDrive, Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight, Gyro * gyro, DriveStabilize * driveStabilize);

    //Required by PIDOutput; This function sends the output to the robotDrive
    virtual void PIDWrite(float output);
    //Required by PIDSource; This function takes the values from the tracker and gives it to the PID loop
    virtual double PIDGet();

    //My functions
    void Reset(); //Sets current location to 0
    //Never set both x and y to some number at the same time. One must always be 0 or else bad things occur
    void SetGoal(double xGoalDistance, double yGoalDistance);

    bool ReachedGoal();

    bool PastGoal(double xGoalDistance, double yGoalDistance);
    bool BeforeGoal(double xGoalDistance, double yGoalDistance);

    void TestEnable();

    virtual ~PIDInterface(){};

private:
    EncoderTracker m_tracker;
    RobotDrive * m_robotDrive;
    PIDController xPID;
    PIDController yPID;
    Gyro  * m_gyro;
    AxisOfMotion m_currentAxis;
    DriveStabilize * m_driveStabilize;
};

#endif
