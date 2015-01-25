#include "WPILib.h"
#include "Constants.h"
#include "TestMode.h"
#include "Team2342Joystick.h"
#include "Dragger.h"
#include "Configuration.h"

/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{
	RobotDrive robotDrive;	// robot drive system
	Team2342Joystick stick;			// only joystick
	Joystick gamepad;       // the gamepad
	Encoder leftRearDriveEncoder;
	Encoder leftFrontDriveEncoder;
	Encoder rightFrontDriveEncoder;
	Encoder rightRearDriveEncoder;
	Gyro gyro;
	Talon elevator1;
	Talon elevator2;
	Dragger dragger; // the gamepad
	Configuration * m_myConfig = Configuration::getInstance();

public:
	Robot() :
			robotDrive(PortAssign::frontLeftChannel, PortAssign::rearLeftChannel,
					  PortAssign::frontRightChannel, PortAssign::rearRightChannel),	// these must be initialized in the same order
			stick(PortAssign::joystickChannel),
			gamepad(PortAssign::gamepadChannel),
			leftRearDriveEncoder(PortAssign::leftRearDriveEncoderChannelA, PortAssign::leftRearDriveEncoderChannelB),
			leftFrontDriveEncoder(PortAssign::leftFrontDriveEncoderChannelA, PortAssign::leftFrontDriveEncoderChannelB),
			rightFrontDriveEncoder(PortAssign::rightFrontDriveEncoderChannelA, PortAssign::rightFrontDriveEncoderChannelB),
			rightRearDriveEncoder(PortAssign::rightRearDriveEncoderChannelA, PortAssign::rightRearDriveEncoderChannelB),
			gyro(PortAssign::gyroChannel),
			elevator1(PortAssign::ElevatorMotor1),
			elevator2(PortAssign::ElevatorMotor2),
			dragger()

// as they are declared above.
	{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);	// invert the right side motors
		robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);	// you may need to change or remove this to match your robot
		rightRearDriveEncoder.SetReverseDirection(true);
		rightFrontDriveEncoder.SetReverseDirection(true);
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

			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
	void Test()
	{

		TestMode tester;
		leftRearDriveEncoder.Reset();
		leftFrontDriveEncoder.Reset();
		rightRearDriveEncoder.Reset();
		rightFrontDriveEncoder.Reset();

		while (IsTest() && IsEnabled())
		{
			tester.PerformTesting(&gamepad, &stick, &leftRearDriveEncoder, &leftFrontDriveEncoder, &rightFrontDriveEncoder, &rightRearDriveEncoder, &gyro, &elevator1, &elevator2, &robotDrive);
			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot);
