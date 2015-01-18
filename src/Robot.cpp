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
	Joystick stick;			// only joystick
	Joystick gamepad;       // the gamepad
	Encoder testEncoder;
	Dragger dragger;


public:
	Robot() :
			robotDrive(PortAssign::frontLeftChannel, PortAssign::rearLeftChannel,
			        PortAssign::frontRightChannel, PortAssign::rearRightChannel),	// these must be initialized in the same order
			stick(PortAssign::joystickChannel),
			gamepad(PortAssign::gamepadChannel),
			testEncoder(PortAssign::testEncoderChannelA, PortAssign::testEncoderChannelB),
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
			robotDrive.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), stick.GetZ());
			dragger.operateDragger(&gamepad);
			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
	void Test()
	{

		TestMode tester;

		while (IsTest() && IsEnabled())
		{
			tester.PerformTesting(&stick, &testEncoder);

			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot);
