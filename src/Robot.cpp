#include "WPILib.h"
#include "Constants.h"
#include "TestMode.h"
#include "Team2342Joystick.h"
#include "Dragger.h"

/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{
	RobotDrive robotDrive;	// robot drive system
	Team2342Joystick stick;			// only joystick
	Joystick gamepad;       // the gamepad
	Encoder driveEncoder1;
	Encoder driveEncoder2;
	Encoder driveEncoder3;
	Encoder driveEncoder4;
	Gyro gyro;
	Dragger dragger;    // the gamepad

public:
	Robot() :
			robotDrive(PortAssign::frontLeftChannel, PortAssign::rearLeftChannel,
					  PortAssign::frontRightChannel, PortAssign::rearRightChannel),	// these must be initialized in the same order
			stick(PortAssign::joystickChannel),
			gamepad(PortAssign::gamepadChannel),
			driveEncoder1(PortAssign::driveEncoder1ChannelA, PortAssign::driveEncoder1ChannelB),
			driveEncoder2(PortAssign::driveEncoder2ChannelA, PortAssign::driveEncoder2ChannelB),
			driveEncoder3(PortAssign::driveEncoder3ChannelA, PortAssign::driveEncoder3ChannelB),
			driveEncoder4(PortAssign::driveEncoder4ChannelA, PortAssign::driveEncoder4ChannelB),
			gyro(PortAssign::gyroChannel),
			dragger()
// as they are declared above.
	{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);	// invert the right side motors
		robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);	// you may need to change or remove this to match your robot
		SmartDashboard::init();
	}
	//Move a given distance (in inches). This is a very early concept of it and will probably change when we implement encoders
	void MoveDistance(float xDistance, float yDistance)
	{
	    //Assuming that 1 is the max input for a joystick because if I assume it's 255 and it turns out to be 1 the robot might have issues while testing
	    //This will move the robot in an L shape for now (x first)
	    if (xDistance != 0)
	    {
	        if (xDistance > 0)
	        {
	            robotDrive.MecanumDrive_Cartesian(1,0,0);
	        }
	        else
	        {
	            robotDrive.MecanumDrive_Cartesian(-1,0,0);
	        }
	        Wait(xDistance/4);
	    }
	    if (yDistance != 0)
	    {
            if (yDistance > 0)
            {
                robotDrive.MecanumDrive_Cartesian(0,1,0);
            }
            else
            {
                robotDrive.MecanumDrive_Cartesian(0,-1,0);
            }
	        Wait(yDistance/4);
	    }
	}
	void Autonomous()
	{
        //Pick up tote here
	    MoveDistance(-FieldDistances::autoCrateDiff,0);
        //Pick up another tote here
        MoveDistance(-FieldDistances::autoCrateDiff,0);
        //Pick up yet another tote here
        MoveDistance(0,FieldDistances::intoAutoDiff);
	}
	/**
	 * Runs the motors with Mecanum drive.
	 */
	void OperatorControl()
	{
		robotDrive.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{
        	// Use the joystick X axis for lateral movement, Y axis for forward movement, and Z axis for rotation.
        	// This sample does not use field-oriented drive, so the gyro input is set to zero.
			robotDrive.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), stick.GetZWithDeadZone(0.1)/*gyro.GetAngle()*/);
			dragger.operateDragger(&gamepad);
			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
	void Test()
	{

		TestMode tester;

		while (IsTest() && IsEnabled())
		{
			tester.PerformTesting(&stick, &driveEncoder1, &driveEncoder2, &driveEncoder3, &driveEncoder4, &gyro);

			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot);
