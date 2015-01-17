#include "WPILib.h"
#include "TestMode.h"

/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{

    // Channels for the wheels
    const static int frontLeftChannel	= 3;
    const static int rearLeftChannel	= 0;
    const static int frontRightChannel	= 1;
    const static int rearRightChannel	= 2;

    const static int joystickChannel	= 0;
    const static int testEncoderChannelA = 0;
    const static int testEncoderChannelB = 1;
    const static int driveEncoder1ChannelA = 2;
    const static int driveEncoder1ChannelB = 3;
    const static int driveEncoder2ChannelA = 4;
    const static int driveEncoder2ChannelB = 5;
    const static int driveEncoder3ChannelA = 6;
    const static int driveEncoder3ChannelB = 7;
    const static int driveEncoder4ChannelA = 8;
    const static int driveEncoder4ChannelB = 9;
    const static int gyroChannel = 0;


	RobotDrive robotDrive;	// robot drive system
	Joystick stick;			// only joystick
	Encoder testEncoder;
	Encoder driveEncoder1;
	Encoder driveEncoder2;
	Encoder driveEncoder3;
	Encoder driveEncoder4;
	Gyro gyro;

public:
	Robot() :
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick(joystickChannel),
			testEncoder(testEncoderChannelA,testEncoderChannelB),
			driveEncoder1(driveEncoder1ChannelA, driveEncoder1ChannelB),
			driveEncoder2(driveEncoder2ChannelA, driveEncoder2ChannelB),
			driveEncoder3(driveEncoder3ChannelA, driveEncoder3ChannelB),
			driveEncoder4(driveEncoder4ChannelA, driveEncoder4ChannelB),
			gyro(gyroChannel)
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

			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
	void Test()
	{

		TestMode tester;

		while (IsTest() && IsEnabled())
		{
			tester.PerformTesting(&stick, &testEncoder, &driveEncoder1, &driveEncoder2, &driveEncoder3, &driveEncoder4, &gyro);

			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot);
