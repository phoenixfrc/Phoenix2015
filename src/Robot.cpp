
#include "WPILib.h"
#include "Constants.h"
#include "TestMode.h"
#include "Team2342Joystick.h"
#include "Elevator.h"
#include "Dragger.h"
#include "EncoderTracker.h"
#include "PIDInterface.h"
#include <sstream>
/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */

enum AutoMode {
    complex,
    simple
};

class Robot: public SampleRobot
{
	RobotDrive m_robotDrive;	// robot drive system

        Talon m_elevatorMotor1;
        Talon m_elevatorMotor2;
        Talon m_draggerMotor;

        Elevator* m_elevator;
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

        EncoderTracker m_dummyTracker;
        PIDInterface m_autoPID;

public:
	Robot() :
	    m_robotDrive(PortAssign::FrontLeftChannel, PortAssign::RearLeftChannel,
					  PortAssign::FrontRightChannel, PortAssign::RearRightChannel),	// these must be initialized in the same order

            m_elevatorMotor1(PortAssign::ElevatorMotor1),
            m_elevatorMotor2(PortAssign::ElevatorMotor2),
			m_draggerMotor(PortAssign::DraggerMotorPort),

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

			m_dummyTracker(&m_leftFrontDriveEncoder, &m_rightFrontDriveEncoder, &m_leftRearDriveEncoder, &m_rightRearDriveEncoder),
			m_autoPID(&m_robotDrive, &m_leftFrontDriveEncoder, &m_rightFrontDriveEncoder, &m_leftRearDriveEncoder, &m_rightRearDriveEncoder)

// as they are declared above.
	{
	    printf("In robot constructor..\n");
            m_elevator = new Elevator(&m_elevatorMotor1,
                    &m_elevatorMotor2,
                    &m_elevatorLowerLimit,
                    &m_elevatorUpperLimit,
                    &m_elevatorHomeSwitch,
                    &m_elevatorEncoder,
                    &m_gamepad,
                    &m_brake);

	    m_robotDrive.SetExpiration(0.1);
		m_robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);	// invert the right side motors
		m_robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);	// you may need to change or remove this to match your robot
		m_rightRearDriveEncoder.SetReverseDirection(true);
		m_rightFrontDriveEncoder.SetReverseDirection(true);
		SmartDashboard::init();
	}
	void ClearDisplay()
	{
        SmartDashboard::PutString("DB/String 0", " ");
        SmartDashboard::PutString("DB/String 1", " ");
        SmartDashboard::PutString("DB/String 2", " ");
        SmartDashboard::PutString("DB/String 3", " ");
        SmartDashboard::PutString("DB/String 4", " ");
        SmartDashboard::PutString("DB/String 5", " ");
        SmartDashboard::PutString("DB/String 6", " ");
        SmartDashboard::PutString("DB/String 7", " ");
        SmartDashboard::PutString("DB/String 8", " ");
        SmartDashboard::PutString("DB/String 9", " ");
	}
	void Autonomous()
	{
	    ClearDisplay();

	    m_robotDrive.SetSafetyEnabled(false);

		//m_robotDrive.SetSafetyEnabled(false); this may be needed
	    //This is the mode it's going to use
	    AutoMode autoMode = simple;

	    switch(autoMode)
	    {
	    case complex:
            //Pick up tote here
	        m_autoPID.SetGoal(-FieldDistances::autoCrateDiff,0);
	        while(IsAutonomous() && !m_autoPID.ReachedGoal())
	        {
	            Wait(0.005);
	        }
            //Pick up another tote here
	        m_autoPID.SetGoal(-FieldDistances::autoCrateDiff,0);
            while(IsAutonomous() && !m_autoPID.ReachedGoal())
            {
                Wait(0.005);
            }
            //Pick up yet another tote here
	        m_autoPID.SetGoal(0,FieldDistances::intoAutoDiff);
            while(IsAutonomous() && !m_autoPID.ReachedGoal())
            {
                Wait(0.005);
            }
            //drop totes here
            m_autoPID.Reset();
            break;
	    case simple:
	        SmartDashboard::PutString("DB/String 0", "Starting Autonomous");

	    	//This expects robot to be placed between tote and drive station facing into the field
	        //Pick up tote here
	        m_autoPID.SetGoal(0,FieldDistances::intoAutoDiff);

	        int counter = 0;

            while(IsAutonomous() && IsEnabled() && !m_autoPID.ReachedGoal())
            {
                counter++;
            	DisplayInfo();
                Wait(0.005);
                std::ostringstream builder;
                builder << "We looped " << counter << " times";
                SmartDashboard::PutString("DB/String 3", builder.str());
            }

            //Drop tote here

            m_autoPID.Reset();
	    }
	}
	/**
	 * Runs the motors with Mecanum drive.
	 */
	void OperatorControl()
	{
	    ClearDisplay();

	    m_robotDrive.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{
        	// Use the joystick X axis for lateral movement, Y axis for forward movement, and Z axis for rotation.
        	// This sample does not use field-oriented drive, so the gyro input is set to zero.
		    m_robotDrive.MecanumDrive_Cartesian(m_stick.GetX(), m_stick.GetY(), m_stick.GetZWithDeadZone(0.1)/*gyro.GetAngle()*/);

		    m_elevator->operateElevator();

		    m_dragger.operateDragger(&m_gamepad, &m_draggerLowerLimit, &m_draggerUpperLimit, &m_draggerMotor);

		    DisplayInfo();

			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
	void Test()
	{
	    ClearDisplay();

		TestMode tester;
		m_leftRearDriveEncoder.Reset();
		m_leftFrontDriveEncoder.Reset();
		m_rightRearDriveEncoder.Reset();
		m_rightFrontDriveEncoder.Reset();
		m_elevatorEncoder.Reset();
		while (IsTest() && IsEnabled())
		{
			tester.PerformTesting(&m_gamepad, &m_stick,
			       &m_elevatorMotor1, &m_elevatorMotor2, &m_robotDrive, &m_brake, &m_dummyTracker);
			//DisplayInfo();
			Wait(0.005);
		}
	}
	void DisplayInfo(){

		static int count = 0;
		if (count++ < 100) {
			return;
		}
		count = 0;
		std::ostringstream gyroBuilder, eb, eb2, elevatorBuilder, elevatorEncoderBuilder, elevatorBuilder3;

		//Prints out the values for gyro:
		gyroBuilder << "The Gyro angle is: ";
		gyroBuilder << m_gyro.GetAngle();
	    SmartDashboard::PutString("DB/String 2", gyroBuilder.str());

	    //Print Encoder values:
	    eb << "LR: "<< m_leftRearDriveEncoder.Get();
	    eb << " RR: "<< m_rightRearDriveEncoder.Get();
	    SmartDashboard::PutString("DB/String 3", eb.str());



	    eb2 << " LF: "<< m_leftFrontDriveEncoder.Get();
	    eb2 << " RF: "<< m_rightFrontDriveEncoder.Get();
	    SmartDashboard::PutString("DB/String 4", eb2.str());

	    elevatorEncoderBuilder << "Elevator Encoder: " << m_elevatorEncoder.Get();
	    SmartDashboard::PutString("DB/String 6", elevatorEncoderBuilder.str());


	    //Prints out the elevator limit switches
	     elevatorBuilder3 << //"ElL,U,H;O;DL,U*: "<<
	     		m_elevatorLowerLimit.Get() <<
				m_elevatorUpperLimit.Get() <<
				m_elevatorHomeSwitch.Get() <<
	 			m_opticalSensor.Get() <<
	 			m_draggerLowerLimit.Get() <<
	 			m_draggerUpperLimit.Get() <<
	 			m_DIO16.Get() <<
	 			m_DIO17.Get() <<
	 			m_DIO18.Get() <<
	 			m_DIO19.Get() <<
	 			m_DIO20.Get() <<
	 			m_DIO21.Get() <<
	 			m_DIO22.Get() <<
	 			m_DIO23.Get() <<
	 			m_DIO24.Get() <<
	 			m_DIO25.Get();
	     SmartDashboard::PutString("DB/String 5", elevatorBuilder3.str());

	}

};

START_ROBOT_CLASS(Robot);
