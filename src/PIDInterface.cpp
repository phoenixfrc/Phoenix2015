#include "PIDInterface.h"
#include "WPILib.h"
#include <sstream>

PIDInterface::PIDInterface(RobotDrive * robotDrive, EncoderTracker * tracker, Gyro * gyro, DriveStabilize * driveStabilize):
xPID(0.08, 0.0, 0.0, this, this), //PID values will need to be tuned for both of these
yPID(0.16, 0.0, 0.0, this, this)
{
    xPID.SetOutputRange(-0.5, 0.5);
    yPID.SetOutputRange(-0.5, 0.5);

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
	m_tracker = tracker;

	m_driveStabilize = driveStabilize;
	isPastGoal = false;
	m_xGoalDistance = 0;
	m_yGoalDistance = 0;
}

void PIDInterface::Reset()
{
	m_tracker->ResetPosition();
	isPastGoal = false;

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
	m_xGoalDistance = xGoalDistance;
	//Now to do the same for forward-backward
	if(yGoalDistance != 0)
	{
		m_currentAxis = forward;
		yPID.Enable();
	}
	yPID.SetSetpoint(yGoalDistance);
	m_yGoalDistance = yGoalDistance;
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

bool PIDInterface::PastGoal() {
    float y = m_tracker->GetY();
    float py = y - m_tracker->GetDeltaY();
    float x = m_tracker->GetX();
    float px = x - m_tracker->GetDeltaX();
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


            return (y > m_yGoalDistance) != (py > m_yGoalDistance);
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


            return (x > m_xGoalDistance) != (px > m_xGoalDistance);
            break;
        case stop:
            return false;
            break;
        }
    return false;
}

bool PIDInterface::BeforeGoal(double xGoalDistance, double yGoalDistance) {
	switch(m_currentAxis)
	{
	case forward:
		return m_tracker->GetY() < yGoalDistance;
		break;
	case right:
		return m_tracker->GetX() < xGoalDistance;
		break;
	case stop:
		return false;
		break;
	}
	return false;
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
	m_tracker->TrackPosition();
	LR << "Position LR: " << m_tracker->GetX();
	SmartDashboard::PutString("DB/String 7", LR.str());
	FB << "Position FB: " << m_tracker->GetY();
	SmartDashboard::PutString("DB/String 8", FB.str());
	switch(m_currentAxis)
	{
	case right:
		return m_tracker->GetX();
		break;
	case forward:
		return m_tracker->GetY();
		break;
	default:
		return 0;
	}
}

void PIDInterface::PIDWrite(float output)
{
	//Output to the motors so they drive and move along the current axis
    if(PastGoal())
    {
        isPastGoal = true;
    }

    std::ostringstream bobTheStringBuilder;

	switch(m_currentAxis)
	{
	case right:
		m_robotDrive->MecanumDrive_Cartesian(output, m_driveStabilize->LockY(), m_driveStabilize->GetCorrectionAngle(), m_gyro->GetAngle());

		bobTheStringBuilder << "LockY: " << m_driveStabilize->LockY();
		SmartDashboard::PutString("DB/String 9", bobTheStringBuilder.str());


		break;
	case forward:
		output /= -2;
		m_robotDrive->MecanumDrive_Cartesian(0.0, output, m_driveStabilize->GetCorrectionAngle(), m_gyro->GetAngle());
		break;
	case stop:
		Reset();
	}
}
