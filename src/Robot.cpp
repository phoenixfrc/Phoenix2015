#include "WPILib.h"
#include "TestMode.h"
#include "PhysicalMeasurements.h"

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
    const static int testEncoderChannelA = 1;
    const static int testEncoderChannelB = 2;


	RobotDrive robotDrive;	// robot drive system
	Joystick stick;			// only joystick
	Encoder testEncoder;

public:
	Robot() :
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick(joystickChannel),
			testEncoder(testEncoderChannelA,testEncoderChannelB)
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
	        wait(xDistance/RobotSpecs::driveSpeed);
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
	        wait(yDistance/RobotSpecs::driveSpeed);
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
			robotDrive.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), stick.GetZ());

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
