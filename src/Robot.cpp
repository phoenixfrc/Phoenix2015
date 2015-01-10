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

    const static int joystickChannel1	= 0;
    const static int joystickChannel2	= 1;
    const static int testEncoderChannelA = 1;
    const static int testEncoderChannelB = 2;


	RobotDrive robotDrive;	// robot drive system
	Joystick stick1;			// only joystick
	Joystick stick2;
	Encoder testEncoder;

public:
	Robot() :
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick1(joystickChannel1),
			stick2(joystickChannel2),
			testEncoder(testEncoderChannelA,testEncoderChannelB)
// as they are declared above.
	{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);	// invert the left side motors
		robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);	// you may need to change or remove this to match your robot
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
			robotDrive.MecanumDrive_Cartesian(stick1.GetX(), stick1.GetY(), stick2.GetX());

			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
	void Test()
	{
		while (IsTest() && IsEnabled())
		{
			TestMode::PerformTesting(&testEncoder);

			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot);
