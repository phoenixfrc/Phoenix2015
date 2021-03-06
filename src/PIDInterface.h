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
    PIDInterface(RobotDrive * robotDrive, EncoderTracker * tracker, Gyro * gyro, DriveStabilize * driveStabilize);

    //Required by PIDOutput; This function sends the output to the robotDrive
    virtual void PIDWrite(float output);
    //Required by PIDSource; This function takes the values from the tracker and gives it to the PID loop
    virtual double PIDGet();

    //My functions
    void Reset(); //Sets current location to 0
    //Never set both x and y to some number at the same time. One must always be 0 or else bad things occur
    void SetGoal(double xGoalDistance, double yGoalDistance);
    void SetGoal(double xGoalDistance, double yGoalDistance, float speedMultiplier);

    bool ReachedGoal();

    bool BeforeGoal();
    bool PastGoal();
    bool NearGoal();

    void TestEnable();

    virtual ~PIDInterface(){};

    bool isPastGoal;

private:
    RobotDrive * m_robotDrive;
    PIDController xPID;
    PIDController yPID;
    Gyro  * m_gyro;
    AxisOfMotion m_currentAxis;
    DriveStabilize * m_driveStabilize;
    EncoderTracker * m_tracker;
    double m_xGoalDistance;
    double m_yGoalDistance;
    float m_speedMultiplier;
};

#endif
