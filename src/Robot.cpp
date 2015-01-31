#include "WPILib.h"
#include "Constants.h"
#include "TestMode.h"
#include "Team2342Joystick.h"
#include "Dragger.h"
#include "EncoderTracker.h"

/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */

class Robot: public SampleRobot
{
	RobotDrive m_robotDrive;	// robot drive system

        Talon m_elevatorMotor1;
        Talon m_elevatorMotor2;

        Dragger m_dragger;
        // tba Brake

        Relay m_brake;

	Encoder m_leftRearDriveEncoder;
        Encoder m_leftFrontDriveEncoder;
        Encoder m_rightFrontDriveEncoder;
        Encoder m_rightRearDriveEncoder;
        Encoder m_elevatorEncoder;

        DigitalInput m_elevatorLowerLimit;
        DigitalInput m_elevatorUpperLimit;
        DigitalInput m_elevatorHomeSwitch;
        DigitalInput m_opticalSensor;
        DigitalInput m_draggerLowerLimit;
        DigitalInput m_draggerUpperLimit;
        DigitalInput m_DIO16;
        DigitalInput m_DIO17;
        DigitalInput m_DIO18;
        DigitalInput m_DIO19;
        DigitalInput m_DIO20;
        DigitalInput m_DIO21;
        DigitalInput m_DIO22;
        DigitalInput m_DIO23;
        DigitalInput m_DIO24;
        DigitalInput m_DIO25;

        Gyro m_gyro;

        Team2342Joystick m_stick;                 // only joystick
        Joystick m_gamepad;       // the gamepad

        EncoderTracker m_tracker;

public:
	Robot() :
	    m_robotDrive(PortAssign::FrontLeftChannel, PortAssign::RearLeftChannel,
					  PortAssign::FrontRightChannel, PortAssign::RearRightChannel),	// these must be initialized in the same order

            m_elevatorMotor1(PortAssign::ElevatorMotor1),
            m_elevatorMotor2(PortAssign::ElevatorMotor2),

            m_dragger(),

            m_brake(PortAssign::ElevatorBrakeChannel),

            m_leftRearDriveEncoder(PortAssign::LeftRearDriveEncoderChannelA, PortAssign::LeftRearDriveEncoderChannelB),
            m_leftFrontDriveEncoder(PortAssign::LeftFrontDriveEncoderChannelA, PortAssign::LeftFrontDriveEncoderChannelB),
            m_rightFrontDriveEncoder(PortAssign::RightFrontDriveEncoderChannelA, PortAssign::RightFrontDriveEncoderChannelB),
            m_rightRearDriveEncoder(PortAssign::RightRearDriveEncoderChannelA, PortAssign::RightRearDriveEncoderChannelB),
            m_elevatorEncoder(PortAssign::ElevatorEncoderChannelA, PortAssign::ElevatorEncoderChannelB),

            m_elevatorLowerLimit(PortAssign::ElevatorLowerLimitChannel),
            m_elevatorUpperLimit(PortAssign::ElevatorUpperLimitChannel),
            m_elevatorHomeSwitch(PortAssign::ElevatorHomeSwitchChannel),

	        m_opticalSensor(PortAssign::OpticalSensorChannel),
			m_draggerLowerLimit(PortAssign::DraggerLowerLimitChannel),
			m_draggerUpperLimit(PortAssign::DraggerUpperLimitChannel),
	        m_DIO16(PortAssign::DIO16Channel),
	        m_DIO17(PortAssign::DIO17Channel),
	        m_DIO18(PortAssign::DIO18Channel),
	        m_DIO19(PortAssign::DIO19Channel),
	        m_DIO20(PortAssign::DIO20Channel),
	        m_DIO21(PortAssign::DIO21Channel),
	        m_DIO22(PortAssign::DIO22Channel),
	        m_DIO23(PortAssign::DIO23Channel),
	        m_DIO24(PortAssign::DIO24Channel),
	        m_DIO25(PortAssign::DIO25Channel),

			m_gyro(PortAssign::GyroChannel),

            m_stick(PortAssign::JoystickChannel),
            m_gamepad(PortAssign::GamepadChannel),

       m_tracker(m_leftFrontDriveEncoder, m_rightFrontDriveEncoder, m_leftRearDriveEncoder, m_rightRearDriveEncoder)

// as they are declared above.
	{
		m_robotDrive.SetExpiration(0.1);
		m_robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);	// invert the right side motors
		m_robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);	// you may need to change or remove this to match your robot
		m_rightRearDriveEncoder.SetReverseDirection(true);
		m_rightFrontDriveEncoder.SetReverseDirection(true);
		SmartDashboard::init();
	}

	/**
	 * Runs the motors with Mecanum drive.
	 */
	void OperatorControl()
	{
	    m_robotDrive.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{
        	// Use the joystick X axis for lateral movement, Y axis for forward movement, and Z axis for rotation.
        	// This sample does not use field-oriented drive, so the gyro input is set to zero.
		    m_robotDrive.MecanumDrive_Cartesian(m_stick.GetX(), m_stick.GetY(), m_stick.GetZWithDeadZone(0.1)/*gyro.GetAngle()*/);
		    m_dragger.operateDragger(&m_gamepad, &m_draggerLowerLimit, &m_draggerUpperLimit);

			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
	void Test()
	{

		TestMode tester;
		m_leftRearDriveEncoder.Reset();
		m_leftFrontDriveEncoder.Reset();
		m_rightRearDriveEncoder.Reset();
		m_rightFrontDriveEncoder.Reset();

		m_elevatorEncoder.Reset();

		while (IsTest() && IsEnabled())
		{
			tester.PerformTesting(&m_gamepad, &m_stick,
			        &m_leftRearDriveEncoder, &m_leftFrontDriveEncoder,
			        &m_rightFrontDriveEncoder, &m_rightRearDriveEncoder,
			        &m_gyro, &m_elevatorMotor1, &m_elevatorMotor2, &m_robotDrive,
			        &m_elevatorEncoder, &m_brake,
					&m_elevatorLowerLimit, &m_elevatorUpperLimit, &m_elevatorHomeSwitch,
					&m_opticalSensor,
					&m_draggerLowerLimit,
					&m_draggerUpperLimit,
					&m_DIO16,
					&m_DIO17,
					&m_DIO18,
					&m_DIO19,
					&m_DIO20,
					&m_DIO21,
					&m_DIO22,
					&m_DIO23,
					&m_DIO24,
					&m_DIO25,
					&m_tracker
					);
			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot);
