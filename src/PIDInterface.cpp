#include "PIDInterface.h"
#include "WPILib.h"
#include <sstream>

PIDInterface::PIDInterface(RobotDrive * robotDrive, Encoder * frontLeft, Encoder * frontRight, Encoder * backLeft, Encoder * backRight, Gyro * gyro):
m_tracker(frontLeft, frontRight, backLeft, backRight),
xPID(0.025, 0.02, 0.001, this, this), //PID values will need to be tuned for both of these
yPID(0.01, 0.001, 0.0, this, this)
{
	if(xPID.IsEnabled())
	{
		xPID.Disable();
	}
	if(yPID.IsEnabled())
	{
		yPID.Disable();
	}
	m_robotDrive = robotDrive;
	m_currentAxis = stop;
	m_gyro = gyro;
}

void PIDInterface::Reset()
{
	m_tracker.ResetPosition();
	if(xPID.IsEnabled())
	{
		xPID.Disable();
	}
	if(yPID.IsEnabled())
	{
		yPID.Disable();
	}
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

bool PIDInterface::PastGoal(double xGoalDistance, double yGoalDistance) {
	switch(m_currentAxis)
	{
	case forward:
		/*
	    if(yGoalDistance < 0)
		{
			return m_tracker.GetY() < yGoalDistance;
		}
		else
		{
			return m_tracker.GetY() > yGoalDistance;
		}
		*/
	    float y = m_tracker.GetY();
        float py = y - m_tracker.GetDeltaY();

        return (y > yGoalDistance) != (py > yGoalDistance);
		break;
	case right:
	    /*
		if(xGoalDistance < 0)
		{
			return m_tracker.GetX() < xGoalDistance;
		}
		else
		{
			return m_tracker.GetX() > xGoalDistance;
		}
		*/
	    float x = m_tracker.GetX();
        float px = x - m_tracker.GetDeltaX();

        return (x > xGoalDistance) != (px > xGoalDistance);
		break;
	case stop:
		return false;
		break;
	}
}

bool PIDInterface::BeforeGoal(double xGoalDistance, double yGoalDistance) {
	switch(m_currentAxis)
	{
	case forward:
		return m_tracker.GetY() < yGoalDistance;
		break;
	case right:
		return m_tracker.GetX() < xGoalDistance;
		break;
	case stop:
		return false;
		break;
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

	switch(m_currentAxis)
	{
	case right:
		m_robotDrive->MecanumDrive_Cartesian(output, 0.0, 0.0, m_gyro->GetAngle());
		break;
	case forward:
		output /= 2;
		m_robotDrive->MecanumDrive_Cartesian(0.0, output, 0.0, m_gyro->GetAngle());
		break;
	case stop:
		Reset();
	}
}
