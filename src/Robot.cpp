
#include "WPILib.h"
#include "Constants.h"
#include "TestMode.h"
#include "Team2342Joystick.h"
#include "Elevator.h"
#include "Dragger.h"
#include "EncoderTracker.h"
#include "PIDInterface.h"
#include "DashboardPreferences.h"
#include <sstream>
/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */

enum AutoMode {
    complex,
    simple,
	simpleShort
};

class Robot: public SampleRobot
{
    RobotDrive m_robotDrive;	// robot drive system

    Talon m_elevatorMotor1;
    Talon m_elevatorMotor2;

    Talon m_draggerMotor;
    Elevator* m_elevator;
    Dragger m_dragger;
    TestMode m_tester;
    // tba Brake
    Relay m_brake;

    DashboardPreferences m_dashboard;

    Encoder m_leftRearDriveEncoder;
    Encoder m_leftFrontDriveEncoder;
    Encoder m_rightFrontDriveEncoder;
    Encoder m_rightRearDriveEncoder;
    Encoder m_elevatorEncoder;

    EncoderTracker m_tracker;
    DigitalInput m_elevatorLowerLimit;
    DigitalInput m_DIO11;
    DigitalInput m_elevatorUpperLimit;
    DigitalInput m_draggerLowerLimit;
    //MXP Breakout board doesn't expose ports: 14-17
//    DigitalInput m_DIO14;
//    DigitalInput m_DIO15;
//    DigitalInput m_DIO16;
//    DigitalInput m_DIO17;
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

    PIDInterface m_autoPID;
    DriveStabilize m_driveStabilize;

public:
    Robot():
        m_robotDrive(PortAssign::FrontLeftChannel, PortAssign::RearLeftChannel,
        PortAssign::FrontRightChannel, PortAssign::RearRightChannel),	// these must be initialized in the same order

        m_elevatorMotor1(PortAssign::ElevatorMotor1),
        m_elevatorMotor2(PortAssign::ElevatorMotor2),

        m_draggerMotor(PortAssign::DraggerMotorPort),


        m_dragger(),

		m_tester(),

        m_brake(PortAssign::ElevatorBrakeChannel),

		m_dashboard(),

        m_leftRearDriveEncoder(PortAssign::LeftRearDriveEncoderChannelA, PortAssign::LeftRearDriveEncoderChannelB),
        m_leftFrontDriveEncoder(PortAssign::LeftFrontDriveEncoderChannelA, PortAssign::LeftFrontDriveEncoderChannelB),
        m_rightFrontDriveEncoder(PortAssign::RightFrontDriveEncoderChannelA, PortAssign::RightFrontDriveEncoderChannelB),
        m_rightRearDriveEncoder(PortAssign::RightRearDriveEncoderChannelA, PortAssign::RightRearDriveEncoderChannelB),
        m_elevatorEncoder(PortAssign::ElevatorEncoderChannelA, PortAssign::ElevatorEncoderChannelB),

        m_tracker(&m_leftFrontDriveEncoder, &m_rightFrontDriveEncoder, &m_leftRearDriveEncoder, &m_rightRearDriveEncoder),

        m_elevatorLowerLimit(PortAssign::ElevatorLowerLimitChannel),
        m_DIO11(PortAssign::DIO11Channel),
        m_elevatorUpperLimit(PortAssign::ElevatorUpperLimitChannel),
        m_draggerLowerLimit(PortAssign::DraggerActivatedLimitChannel),

        //m_DIO14(PortAssign::DIO14Channel),
        //m_DIO15(PortAssign::DIO15Channel),
        //m_DIO16(PortAssign::DIO16Channel),
        //m_DIO17(PortAssign::DIO17Channel),
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
        m_autoPID(&m_robotDrive, &m_tracker, &m_gyro, &m_driveStabilize),

        m_driveStabilize(&m_gyro, &m_tracker, &m_stick, 0.0, 0.0, 0.008, 0.25, 0.5)

// as they are declared above.

{
        printf("In robot constructor..\n");
        m_elevator = new Elevator(&m_elevatorMotor1,
                &m_elevatorMotor2,
                &m_elevatorLowerLimit,
                &m_elevatorUpperLimit,
                &m_elevatorEncoder,
                &m_gamepad,
                &m_stick,
                &m_brake);



        m_robotDrive.SetExpiration(0.1);
        m_robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);	// invert the right side motors
        m_robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);	// you may need to change or remove this to match your robot
        m_rightRearDriveEncoder.SetReverseDirection(true);
        m_rightFrontDriveEncoder.SetReverseDirection(true);
        m_elevatorEncoder.SetReverseDirection(true);
        SmartDashboard::init();
        //reserved for config
        //reserved for config
        //reserved for config
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
        m_robotDrive.SetSafetyEnabled(false);
        m_gyro.Reset();

        //This is the mode it's going to use

       /* if(m_dashboard.m_button1){
        	AutoMode autoMode = complex;
        }
        if(m_dashboard.m_button2){
        	AutoMode autoMode = simple;
        }
        if(m_dashboard.m_button3){
        	AutoMode autoMode = simpleShort;
        } */

        ClearDisplay();
        m_elevator->ElevatorInit();
        SmartDashboard::PutString("DB/String 0", "Initial Homeing");
        while(!m_elevator->elevatorIsHomed())
        {
            m_elevator->operateElevator();
        }

        int MovePickup2Height = 60;

        const float simpleAutoDelay = 0;

        //m_robotDrive.SetSafetyEnabled(false); this may be needed

        AutoMode autoMode = simple;

        m_autoPID.Reset();

        Wait(simpleAutoDelay);//debug only

        switch(autoMode)
        {
        case complex:
            SmartDashboard::PutString("DB/String 0", "Starting Autonomous");

            //Pick up tote  6 inch
                SmartDashboard::PutString("DB/String 0", "Initial Pick up");

            m_elevator->setElevatorGoalPosition(kElevatorHook1Lifted);

            while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook1Lifted))
            {
            	SmartDashboard::PutString("DB/String 0", "Still in this loop");
                DisplayInfo();
                Wait(0.005);
            }

            Wait(1.0);

            // move right + move up over container
            SmartDashboard::PutString("DB/String 0", "Pick Up and Move 1");

            m_autoPID.SetGoal(FieldDistances::autoCrateDiff,0);
            m_elevator->setElevatorGoalPosition(kElevatorHook3Lifted);
            while(IsAutonomous() && IsEnabled() &&
                        (!m_autoPID.isPastGoal || !m_elevator->elevatorIsAt(kElevatorHook3Lifted)))
            {
                DisplayInfo();
                Wait(0.005);
            }




            Wait(1.0);

            //move down
            SmartDashboard::PutString("DB/String 0", "Lower Crate 1 ");

            m_elevator->setElevatorGoalPosition(kElevatorHook2Ready);
            while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook2Ready))
            {
                DisplayInfo();
                Wait(0.005);
            }

            Wait(1.0);

            SmartDashboard::PutString("DB/String 0", "Pick up 2");

             m_elevator->setElevatorGoalPosition(kElevatorHook2Lifted);
            while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook2Lifted))
            {
                DisplayInfo();
                Wait(0.005);
            }

            Wait(1.0);


            //up right
            SmartDashboard::PutString("DB/String 0", "Move Pickup 2");
            m_autoPID.SetGoal(FieldDistances::autoCrateDiff,0);
            m_elevator->setElevatorGoalPosition(MovePickup2Height);
            while(IsAutonomous() && IsEnabled() &&
                    (!m_autoPID.isPastGoal || !m_elevator->elevatorIsAt(MovePickup2Height)))
            {
                DisplayInfo();
                Wait(0.005);
            }

            Wait(1.0);

            //move right

            SmartDashboard::PutString("DB/String 0", "Move Right 2");

            m_autoPID.SetGoal(FieldDistances::autoCrateDiff,0);
            while(IsAutonomous()  && IsEnabled() && !m_autoPID.isPastGoal)
            {
                Wait(0.005);
            }

            Wait(1.0);

            //move down
            SmartDashboard::PutString("DB/String 0", "Put down 2");

             m_elevator->setElevatorGoalPosition(kElevatorHook3Ready);
             while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook3Ready))
             {
                DisplayInfo();
                Wait(0.005);
             }

             Wait(1.0);

             //pick up
             SmartDashboard::PutString("DB/String 0", "Pick up 3");

             m_elevator->setElevatorGoalPosition(kElevatorHook3Lifted);
             while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook3Lifted))
             {
                DisplayInfo();
                Wait(0.005);
             }

             Wait(1.0);

            SmartDashboard::PutString("DB/String 0", "Backoff totes");

            //move forward
            m_autoPID.SetGoal(0,-FieldDistances::intoAutoDiff);
            while(IsAutonomous() && IsEnabled() && !m_autoPID.isPastGoal)
            {
                Wait(0.005);
            }

            Wait(1.0);

            //drop totes here
            SmartDashboard::PutString("DB/String 0", "Put down all");

            m_elevator->setElevatorGoalPosition(kElevatorHook1Ready);
            while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook1Ready))
             {
                DisplayInfo();
                Wait(0.005);
             }


            m_autoPID.Reset();
            break;
        case simple:
            SmartDashboard::PutString("DB/String 0", "Starting Autonomous");

            //This expects robot to be placed between tote and drive station facing into the field
            //Pick up tote here
            SmartDashboard::PutString("DB/String 0", "Initial Pick-up");

            m_elevator->setElevatorGoalPosition(kElevatorHook1Lifted);
            while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook1Lifted))
            {
            	m_elevator->updateProfile();
                DisplayInfo();
                Wait(0.005);
            }

            Wait(simpleAutoDelay);//debug only

            SmartDashboard::PutString("DB/String 0", "Moving Forward");

            m_autoPID.SetGoal(0,FieldDistances::intoAutoDiff);
            while(IsAutonomous() && IsEnabled() && !m_autoPID.isPastGoal)
            {
                DisplayInfo();
                Wait(0.005);
            }

            Wait(simpleAutoDelay);//debug only

            SmartDashboard::PutString("DB/String 0", "Dropping");

            m_elevator->setElevatorGoalPosition(kElevatorHook1Ready - 2);
            while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook1Ready - 2))
            {
            	m_elevator->updateProfile();
                DisplayInfo();
                Wait(0.005);
            }

            Wait(simpleAutoDelay);//debug only

            SmartDashboard::PutString("DB/String 0", "Moving Back");


            m_autoPID.SetGoal(0,-4.0);
            while(IsAutonomous() && IsEnabled() && !m_autoPID.BeforeGoal(0,-4))
            {
                DisplayInfo();
                Wait(0.005);
            }

            SmartDashboard::PutString("DB/String 0", "Finished");


            m_autoPID.Reset();
            break;
        case simpleShort:
        	SmartDashboard::PutString("DB/String 0", "Starting Autonomous");
			//This expects robot to be placed between tote and drive station facing into the field
			//Pick up tote here
			SmartDashboard::PutString("DB/String 0", "Initial Pick-up");

			m_elevator->setElevatorGoalPosition(kElevatorHook1Lifted);
			while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook1Lifted))
			{
				m_elevator->updateProfile();
				DisplayInfo();
				Wait(0.005);
			}

			Wait(simpleAutoDelay);//debug only

			SmartDashboard::PutString("DB/String 0", "Moving Forward");

			m_autoPID.SetGoal(0,FieldDistances::intoAutoDiff);
			while(IsAutonomous() && IsEnabled() && !m_autoPID.isPastGoal)
			{
				DisplayInfo();
				Wait(0.005);
			}

			Wait(simpleAutoDelay);//debug only

			SmartDashboard::PutString("DB/String 0", "Dropping");

			m_elevator->setElevatorGoalPosition(kElevatorHook1Ready - 2);
			while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(kElevatorHook1Ready - 2))
			{
				m_elevator->updateProfile();
				DisplayInfo();
				Wait(0.005);
			}

			Wait(simpleAutoDelay);//debug only

			SmartDashboard::PutString("DB/String 0", "Moving Back");


			m_autoPID.SetGoal(0,-4.0);
			while(IsAutonomous() && IsEnabled() && !m_autoPID.BeforeGoal(0,-4))
			{
				DisplayInfo();
				Wait(0.005);
			}

			SmartDashboard::PutString("DB/String 0", "Finished");


			m_autoPID.Reset();
			break;
        }
        m_elevator->ElevatorEnd();

    }
    /**
     * Runs the motors with Mecanum drive.
     */
    void OperatorControl()
    {
        ClearDisplay();

        m_robotDrive.SetSafetyEnabled(false);
        m_elevator->ElevatorInit();
        while (IsOperatorControl() && IsEnabled())
        {
            // Use the joystick X axis for lateral movement, Y axis for forward movement, and Z axis for rotation.
            // This sample does not use field-oriented drive, so the gyro input is set to zero.
            m_robotDrive.MecanumDrive_Cartesian(m_stick.GetX(), m_stick.GetY(), m_stick.GetZWithDeadZone(0.1)/*gyro.GetAngle()*/);


            m_elevator->operateElevator();

            m_elevator->updateProfile();

            m_dragger.operateDragger(&m_gamepad, &m_draggerLowerLimit, &m_draggerMotor);

            DisplayInfo();

            Wait(0.005); // wait 5ms to avoid hogging CPU cycles
        }
        m_elevator->ElevatorEnd();
    }
    void Test()
    {
        ClearDisplay();

        m_leftRearDriveEncoder.Reset();
        m_leftFrontDriveEncoder.Reset();
        m_rightRearDriveEncoder.Reset();
        m_rightFrontDriveEncoder.Reset();

        m_elevatorEncoder.Reset();
        int32_t count = 0;
        //m_elevator->m_elevatorControl->Enable();

        while (IsTest() && IsEnabled())
        {
        	 m_dashboard.updateButtons();
        	 if(m_dashboard.m_button1){
        	              SmartDashboard::PutString("DB/String 9", "Dashboard Button Works!");
        	        }
        	printf("-------------->%6d button value %c\n", count++,  m_dashboard.m_button1? '1': '0');

            m_tester.PerformTesting(&m_gamepad, &m_stick,
                    &m_elevatorMotor1, &m_elevatorMotor2, &m_robotDrive, &m_brake, &m_draggerMotor);
            //reserved for config
            //reserved for config
            //reserved for config
            DisplayInfo();

            Wait(/*0.005*/0.1);
        }
        m_elevator->m_elevatorControl->Disable();
    }
    void DisplayInfo(){
        static int count = 0;
        if (count++ < 100) {
            return;
        }
        count = 0;

        std::ostringstream gyroBuilder, eb, eb2, elevatorBuilder, elevatorEncoderBuilder, elevatorBuilder3;

        //Prints out the values for gyro:
        gyroBuilder << "Gyro angle: ";
        gyroBuilder << m_gyro.GetAngle();
        SmartDashboard::PutString("DB/String 2", gyroBuilder.str());

        //Print Encoder values:
        eb << "LR: "<< m_leftRearDriveEncoder.Get();
        eb << " RR: "<< m_rightRearDriveEncoder.Get();
        SmartDashboard::PutString("DB/String 3", eb.str());



        eb2 << " LF: "<< m_leftFrontDriveEncoder.Get();
        eb2 << " RF: "<< m_rightFrontDriveEncoder.Get();
        SmartDashboard::PutString("DB/String 4", eb2.str());


        std::ostringstream limitSwitches;

        //Prints out the elevator limit switches
        limitSwitches << //"ElL,U,H;O;DL,U*: "<<
                m_elevatorLowerLimit.Get() <<  // 10
                m_elevatorUpperLimit.Get() <<  // 12
				m_draggerLowerLimit.Get() <<   // 13
                "-" <<
                //m_DIO14.Get() <<
                //m_DIO15.Get() <<
                //m_DIO16.Get() <<
                //m_DIO17.Get() <<
                m_DIO11.Get() <<
				m_DIO18.Get() <<
				m_DIO19.Get() <<
				m_DIO20.Get() <<
                m_DIO21.Get() <<
                m_DIO22.Get() <<
                m_DIO23.Get() <<
                m_DIO24.Get() <<
                m_DIO25.Get();
        SmartDashboard::PutString("DB/String 5", limitSwitches.str());

        elevatorEncoderBuilder << "Ele. Encoder: " << m_elevatorEncoder.Get()/TicksPerInch; // in inches
        SmartDashboard::PutString("DB/String 6", elevatorEncoderBuilder.str());

        std::ostringstream elevatorEncoderBuilder2;

        elevatorEncoderBuilder2 << "Ele. Target: " << m_elevator->getElevatorGoalPosition();

        SmartDashboard::PutString("DB/String 7", elevatorEncoderBuilder2.str());


    }

};

START_ROBOT_CLASS(Robot);
