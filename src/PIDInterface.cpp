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
    xPID.Disable();
    yPID.Disable();
}

void PIDInterface::SetGoal(double xGoalDistance, double yGoalDistance)
{
    Reset();
    //Go as far in the left-right axis as required
    if(xGoalDistance != 0)
    {
        m_currentAxis = right;
        xPID.Enable();
    }
    xPID.SetSetpoint(xGoalDistance);

    //Now to do the same for forward-backward
    if(yGoalDistance != 0)
    {
        m_currentAxis = forward;
        yPID.Enable();
    }
    yPID.SetSetpoint(yGoalDistance);
}

//This will return true if either of the PID loops are enabled and have reached their target
bool PIDInterface::ReachedGoal()
{
    if(xPID.IsEnabled())
    {
        return xPID.OnTarget();
    }
    else if(yPID.IsEnabled())
    {
        return yPID.OnTarget();
    }
    else
    {
        return false;
    }
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
    default:
    	return 0;
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
