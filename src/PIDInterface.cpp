#include "PIDInterface.h"
#include "WPILib.h"

PIDInterface::PIDInterface(RobotDrive * robotDrive, Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight):
    m_tracker(frontLeft, frontRight, backLeft, backRight),
    xPID(0.05, 0.05, 0.05, this, this), //PID values will need to be tuned for both of these
    yPID(0.05, 0.05, 0.05, this, this)
{
    xPID.Disable();
    yPID.Disable();
    m_robotDrive = robotDrive;
    m_currentAxis = x;
}

void PIDInterface::Reset()
{
    m_tracker.ResetPosition();
}

void PIDInterface::SetGoal(double xGoalDistance, double yGoalDistance)
{
    Reset();
    //Go as far in the x axis as required
    m_currentAxis = x;
    xPID.Enable();
    xPID.SetSetpoint(xGoalDistance);
    while(!xPID.OnTarget())
    {
        Wait(0.005); //Wait until the x distance is reached, but only check every 5ms
    }
    xPID.Disable();

    //Now to do the same for y
    m_currentAxis = y;
    yPID.Enable();
    yPID.SetSetpoint(yGoalDistance);
    while(!yPID.OnTarget())
    {
        Wait(0.005); //Wait until the y distance is reached, but only check every 5ms
    }
    yPID.Disable();
}

double PIDInterface::PIDGet()
{
    //Update the tracker's internal numbers and then return either x or y depending on which axis we're currently trying to move along
    m_tracker.TrackPosition();
    switch(m_currentAxis)
    {
    case x:
        return m_tracker.GetX();
        break;
    case y:
        return m_tracker.GetY();
        break;
    }
}

void PIDInterface::PIDWrite(float output)
{
    //Output to the motors so they drive and move along the current axis
    switch(m_currentAxis)
    {
    case x:
        m_robotDrive->MecanumDrive_Cartesian(output,0,0);
        break;
    case y:
        m_robotDrive->MecanumDrive_Cartesian(0,output,0);
        break;
    }
}

PIDInterface::~PIDInterface(){

}
