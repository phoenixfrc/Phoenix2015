#include "PIDInterface.h"
#include "WPILib.h"
#include <sstream>

PIDInterface::PIDInterface(RobotDrive * robotDrive, Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight):
    m_tracker(frontLeft, frontRight, backLeft, backRight),
    xPID(0.1, 0.001, 0.0, this, this), //PID values will need to be tuned for both of these
    yPID(0.1, 0.001, 0.0, this, this) // Old values were 100.0, 0.0, 2.0
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
    std::ostringstream Goal;
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
    Goal << "Goal: (" << xGoalDistance << "," << yGoalDistance << ")";
    SmartDashboard::PutString("DB/String 1", Goal.str());
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

void PIDInterface::TestEnable()
{
    xPID.Enable();
    yPID.Enable();
}

double PIDInterface::PIDGet()
{
	std::ostringstream LR, FB, State;
    //Update the tracker's internal numbers and then return either x or y depending on which axis we're currently trying to move along
    m_tracker.TrackPosition();
    LR << "Position LR: " << m_tracker.GetX();
    SmartDashboard::PutString("DB/String 7", LR.str());
    FB << "Position FB: " << m_tracker.GetY();
    SmartDashboard::PutString("DB/String 8", FB.str());
    switch(m_currentAxis)
    {
    case right:
        State << "Pos_X: " << m_tracker.GetX();
        SmartDashboard::PutString("DB/String 0", State.str());
        return m_tracker.GetX();
        break;
    case forward:
        State << "Pos_Y: " << m_tracker.GetY();
        SmartDashboard::PutString("DB/String 0", State.str());
        return m_tracker.GetY();
        break;
    default:
    	return 0;
    }
}

void PIDInterface::PIDWrite(float output)
{
    //Output to the motors so they drive and move along the current axis
    std::ostringstream Output;
    Output << "Desired out: " << output;
    SmartDashboard::PutString("DB/String 2", Output.str());
    output /= 4;
    switch(m_currentAxis)
    {
    case right:
        m_robotDrive->MecanumDrive_Cartesian(output,0,0);
        break;
    case forward:
        m_robotDrive->MecanumDrive_Cartesian(0,-output,0);
        break;
    }
}
