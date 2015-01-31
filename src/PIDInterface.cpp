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
    m_currentAxis = right;
}

void PIDInterface::Reset()
{
    m_tracker.ResetPosition();
}

void PIDInterface::SetGoal(double xGoalDistance, double yGoalDistance, bool (*IsAutoFunc))
{
    Reset();
    //Go as far in the left-right axis as required
    m_currentAxis = right;
    xPID.Enable();
    xPID.SetSetpoint(xGoalDistance);
    //This will break if autonomous mode ends during either of these loops
    while(!xPID.OnTarget())
    {
        if(!IsAutoFunc())
        {
            break;
        }
        Wait(0.005); //Wait until the left-right distance is reached, but only check every 5ms
    }
    xPID.Disable();

    //Now to do the same for forward-backward
    m_currentAxis = forward;
    yPID.Enable();
    yPID.SetSetpoint(yGoalDistance);
    while(!yPID.OnTarget())
    {
        if(!IsAutoFunc())
        {
            break;
        }
        Wait(0.005); //Wait until the forward-backward distance is reached, but only check every 5ms
    }
    yPID.Disable();
}

double PIDInterface::PIDGet()
{
    //Update the tracker's internal numbers and then return either x or y depending on which axis we're currently trying to move along
    m_tracker.TrackPosition();
    switch(m_currentAxis)
    {
    case right:
        return m_tracker.GetX();
        break;
    case forward:
        return m_tracker.GetY();
        break;
    }
}

void PIDInterface::PIDWrite(float output)
{
    //Output to the motors so they drive and move along the current axis
    switch(m_currentAxis)
    {
    case right:
        m_robotDrive->MecanumDrive_Cartesian(output,0,0);
        break;
    case forward:
        m_robotDrive->MecanumDrive_Cartesian(0,output,0);
        break;
    }
}
