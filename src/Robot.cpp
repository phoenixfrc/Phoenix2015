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
	Talon elevator1;
	Talon elevator2;
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
			elevator1(PortAssign::ElevatorMotor1),
			elevator2(PortAssign::ElevatorMotor2),
			dragger()
// as they are declared above.
	{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);	// invert the right side motors
		robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);	// you may need to change or remove this to match your robot
		SmartDashboard::init();
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

			float thumbstick = -gamepad.GetY()/4;

			if(-0.0125 < thumbstick && thumbstick < 0.0125)
			{
				elevator1.Set(0);
				elevator2.Set(0);
			}
			else
			{
			elevator1.Set(thumbstick);
			elevator2.Set(thumbstick);
			}

			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
	void Test()
	{

		TestMode tester;

		while (IsTest() && IsEnabled())
		{
			tester.PerformTesting(&gamepad, &driveEncoder1, &driveEncoder2, &driveEncoder3, &driveEncoder4, &gyro, &elevator1, &elevator2);

			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot);
