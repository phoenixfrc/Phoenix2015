
#include "WPILib.h"
#include "Constants.h"
#include "TestMode.h"
#include "Team2342Joystick.h"
#include "Elevator.h"
#include "Dragger.h"
#include "EncoderTracker.h"
#include "PIDInterface.h"
#include "IRAdjust.h"
#include <sstream>
/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */

enum AutoMode {
    complex,
    simple,
    disabled
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
//    DigitalInput m_DIO18;
    DigitalInput m_DIO19;
    DigitalInput m_DIO20;
    DigitalInput m_DIO21;
    DigitalInput m_DIO22;
    DigitalInput m_DIO23;
    DigitalInput m_DIO24;
    DigitalInput m_DIO25;

    AnalogInput m_IRLeftInner; //only two sensors on robot right now
    AnalogInput m_IRLeftOuter;
    AnalogInput m_IRRightInner;
    AnalogInput m_IRRightOuter;

    Gyro m_gyro;


    Team2342Joystick m_stick;                 // only joystick
    Joystick m_gamepad;       // the gamepad

    IRAdjust m_IRAdjust;

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
        //m_DIO18(PortAssign::DIO18Channel),
        m_DIO19(PortAssign::DIO19Channel),
        m_DIO20(PortAssign::DIO20Channel),
        m_DIO21(PortAssign::DIO21Channel),
        m_DIO22(PortAssign::DIO22Channel),
        m_DIO23(PortAssign::DIO23Channel),
        m_DIO24(PortAssign::DIO24Channel),
        m_DIO25(PortAssign::DIO25Channel),

        m_IRLeftInner(PortAssign::IRLeftInnerChannel),
		m_IRLeftOuter(PortAssign::IRLeftOuterChannel),
        m_IRRightInner(PortAssign::IRRightInnerChannel),
		m_IRRightOuter(PortAssign::IRRightOuterChannel),

		m_gyro(PortAssign::GyroChannel),


        m_stick(PortAssign::JoystickChannel),
        m_gamepad(PortAssign::GamepadChannel),

        m_IRAdjust(&m_IRLeftInner, &m_IRLeftOuter, &m_IRRightInner, &m_IRRightOuter, &m_robotDrive),

        m_autoPID(&m_robotDrive, &m_tracker, &m_gyro, &m_driveStabilize),

        m_driveStabilize(&m_gyro, &m_tracker, &m_stick, 0.0, 0.0, 0.02)

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
        //Add empty auto enum state

        m_robotDrive.SetSafetyEnabled(false);
        m_gyro.Reset();

        ClearDisplay();
        m_elevator->ElevatorInit();
        SmartDashboard::PutString("DB/String 0", "Initial Homeing");
        while(!m_elevator->elevatorIsHomed())
        {
            m_elevator->operateElevator();
        }

        const float simpleAutoDelay = 0.0;

        //m_robotDrive.SetSafetyEnabled(false); this may be needed
        //This is the mode it's going to use
        AutoMode autoMode = complex;

        m_autoPID.Reset();

        //std::ostringstream strBuilder;

        double IRMove = 6.0;

        switch(autoMode)
        {
        //This case assumes that the robot begins in a position directly behind the rightmost tote.
        case complex:
            SnapshotEncoders("Start Values");
//            LiftAndMoveWithDelay(FieldDistances::shiftDiff, 0, 1, kElevatorHook3Lifted, kElevatorHook1Lifted,
//                    "Lift 1 Right");
//            Move(0, FieldDistances::moveBack, 1, "Move Back");
            //The LiftAndMoveWithDelay function is used because the motion of the elevator needs to begin
            //before sideways motion begins, in order to ensure that the robot will pick up the first
            //tote.
            LiftAndMoveWithDelay(0, FieldDistances::moveBack, 0.7, kElevatorHook3Lifted, kElevatorHook1Lifted,
                                "Lift 1 Back");
            SnapshotEncoders("Lift 1 Back");
            //The MoveAndLiftWithDelay function is used here so that downward motion of the tote does not
            //begin until it is past the bin.  This ensures that it will not hit the bin.
            MoveAndLiftWithDelay((-FieldDistances::autoCrateDiff + 4), 0, 1, kElevatorHook2Ready, -50,
                    "1 Left and Down");
            SnapshotEncoders("1 Left and Down");
            IRMove = 8+Tolerances::moveTolerance;//m_IRAdjust.GetMove(2.5);
            printf("IRMove: %10.6f, IRLeft: %d, IRRight: %d \n", IRMove,
                    m_IRLeftInner.GetAverageValue(), m_IRRightInner.GetAverageValue());
            MoveAndLiftWithDelay(0, IRMove, 0.4, kElevatorHook2Lifted, -(IRMove - 3),
                                "1 Left and Down");
            //Move(0, IRMove/*(-FieldDistances::moveBack + 6)*/, 0.2, //The +2 is to make sure that we still run into the tote.
              //      "Move forwards");
            //SnapshotEncoders("Move Forwards");
//            LiftAndMoveWithDelay(FieldDistances::shiftDiff, 0, 1, kElevatorHook4Lifted, kElevatorHook2Lifted,
//                    "Lift 2 Right");
//            Move(0, FieldDistances::moveBack, 1, "Move Back");
            //Lift(kElevatorHook2Lifted, "Lift 2nd tote");
            //The LiftAndMoveWithDelay function is used because the motion of the elevator needs to begin
            //before sideways motion begins, in order to ensure that the robot will pick up the first
            //tote.
            LiftAndMoveWithDelay(0, -IRMove/*(FieldDistances::moveBack - 6)*/, 0.7, kElevatorHook4Lifted, kElevatorHook2Lifted,
                                "Lift 2 Back"); //The -2 is to account for the previously increased forward movement.
            SnapshotEncoders("Lift 2 Back");
            //The MoveAndLiftWithDelay function is used here so that downward motion of the tote does not
            //begin until it is past the bin.  This ensures that it will not hit the bin.
            MoveAndLiftWithDelay((-FieldDistances::autoCrateDiff-6), 0, 1, kElevatorHook3Ready, -50,
                    "1,2 Left and Down");
            SnapshotEncoders("1,2 Left and Down");
            YMoveAndMoveWithDelay(0, (FieldDistances::intoAutoDiff -FieldDistances::moveBack), 0.7, 0.75, 0.4,
                    "To AutoZone");
            SnapshotEncoders("To AutoZone");
            Lift(kElevatorHook1Ready,
                    "Put down all");
            Move(0, FieldDistances::moveBack, 1, "Move Back");
            SnapshotEncoders("Move Back");
            //Backwards motion at the end avoids the possibility of the robot supporting
            //the stack at the end of the autonomous period.

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

            //MIGHT NOT WORK!!!!
            m_autoPID.SetGoal(0,-4.0);
            while(IsAutonomous() && IsEnabled() && !m_autoPID.BeforeGoal())
            {
                DisplayInfo();
                Wait(0.005);
            }

            SmartDashboard::PutString("DB/String 0", "Finished");


            m_autoPID.Reset();
            break;
        case disabled:
            break;
        }
        m_elevator->ElevatorEnd();

    }
    /**
     * Runs the motors with Mecanum drive.
     */
    void OperatorControl()
    {
        m_autoPID.Reset();

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

        m_gyro.Reset();
        //m_elevator->m_elevatorControl->Enable();

        while (IsTest() && IsEnabled())
        {
            m_tester.PerformTesting(&m_gamepad, &m_stick,
                    &m_elevatorMotor1, &m_elevatorMotor2, &m_robotDrive, &m_brake, &m_draggerMotor);
            //reserved for config
            //reserved for config
            //reserved for config
            m_IRAdjust.GetMove();
            DisplayInfo();

            Wait(0.005);
        }
        m_elevator->m_elevatorControl->Disable();
    }
    void DisplayInfo(){
        static int count = 0;
        if (count++ < 100) {
            return;
        }
        count = 0;

        std::ostringstream gyroBuilder, eb, eb2, elevatorBuilder, elevatorEncoderBuilder, elevatorBuilder3, IRSensors, IRSensors2;
        //Print IR Sensor Values


        /*IRSensors << "LI: " << m_IRLeftInner.GetAverageValue();
        IRSensors << "RI: " << m_IRRightInner.GetAverageValue();
        SmartDashboard::PutString("DB/String 0", IRSensors.str());

        IRSensors2 << "IR Inches: " << m_IRAdjust.GetMove();
        SmartDashboard::PutString("DB/String 1", IRSensors2.str());*/


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
				//m_DIO18.Get() <<
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

        SmartDashboard::PutString("DB/String 9", elevatorEncoderBuilder2.str());


    }

    void SnapshotEncoders (const char* message) {
        printf("%20s: LR: %6d, LF %6d, RR: %6d, RF %6d, Gyro: %f\n", message, m_leftRearDriveEncoder.Get(), m_leftFrontDriveEncoder.Get(),
                m_rightRearDriveEncoder.Get(), m_rightFrontDriveEncoder.Get(), m_gyro.GetAngle());
    }

    //This function enables movement in the x and y directions, although currently motion may
    //not occur in both of these directions simultaneously.
    void Move (float x, float y, float speedMultiplier, std::string debugMessage){
        if (!(IsAutonomous() && IsEnabled()))
            {return;}
    	SmartDashboard::PutString("DB/String 0", debugMessage);

        m_autoPID.SetGoal(x, y, speedMultiplier);
        while(IsAutonomous() && IsEnabled() && !m_autoPID.NearGoal())
        {
            DisplayInfo();
            Wait(0.005);
        }

    	//debugMessage->str(" ");
    }

    void YMoveAndMoveWithDelay (float x, float y, float speedMultiplier, float changePercent, float speedMultiplierTwo, std::string debugMessage){
        if (!(IsAutonomous() && IsEnabled()))
            {return;}
        SmartDashboard::PutString("DB/String 0", debugMessage);

        bool triggered = false;
        m_autoPID.SetGoal(x, y * (changePercent + .15), speedMultiplier);
        while(IsAutonomous() && IsEnabled() && !m_autoPID.NearGoal())
        {
            if(!triggered && (fabs(m_autoPID.PIDGet()) > fabs(y * changePercent )))
            {
                m_autoPID.SetGoal(x, y * (1 - changePercent - .15), speedMultiplierTwo);
                triggered = true;
            }
            DisplayInfo();
            Wait(0.005);
        }

        //debugMessage->str(" ");
    }

    //This function enables the motion of the elevator alone.
    void Lift (float height, std::string debugMessage){
        if (!(IsAutonomous() && IsEnabled())) {
            return;
        }
    	SmartDashboard::PutString("DB/String 0", debugMessage);
        m_elevator->setElevatorGoalPosition(height);
        while(IsAutonomous() && IsEnabled() && !m_elevator->elevatorIsAt(height))
        {
            m_elevator->updateProfile();
            DisplayInfo();
            Wait(0.005);
        }
    }

    //This function allows for simultaneous moving and lifting, although currently motion may not occur
    //simultaneously in the x and y directions.
    void MoveAndLift (float x, float y, float speedMultiplier, float height, std::string debugMessage){
        if (!(IsAutonomous() && IsEnabled()))
            {return;}
        SmartDashboard::PutString("DB/String 0", debugMessage);
        m_elevator->setElevatorGoalPosition(height);

        m_autoPID.SetGoal(x, y, speedMultiplier);

        while(IsAutonomous() && IsEnabled() && (!m_autoPID.NearGoal() || !m_elevator->elevatorIsAt(height)))
        {
            m_elevator->updateProfile();
            DisplayInfo();
            Wait(0.005);
        }
    }
    //This function will allow for movement to occur before lifting/lowering begins.
    void MoveAndLiftWithDelay (float x, float y, float speedMultiplier, float height, float ElevatorDropDelay, std::string debugMessage){
        if (!(IsAutonomous() && IsEnabled()))
                    {return;}
        SmartDashboard::PutString("DB/String 0", debugMessage);

        m_autoPID.SetGoal(x, y, speedMultiplier);

        bool triggered = false;

        while(IsAutonomous() && IsEnabled() && (!m_autoPID.NearGoal() || !m_elevator->elevatorIsAt(height)))
        {
            //This cannot be used generally; it only will work for leftward motion.
            if (!triggered){
                if (y == 0){
                    if (fabs(m_tracker.GetX()) >= fabs(ElevatorDropDelay)){
                        m_elevator->setElevatorGoalPosition(height);
                        triggered = true;
                    }
                } else {
                    if (fabs(m_tracker.GetY()) >= fabs(ElevatorDropDelay)){
                        m_elevator->setElevatorGoalPosition(height);
                        triggered = true;
                    }
                }
            }
            m_elevator->updateProfile();
            DisplayInfo();
            Wait(0.005);
        }
    }

    //This function will allow for the elevator motion to be started before movement along the
    //ground begins.  The initial lift of the elevator before horizontal motion occurs is necessary
    //in order to ensure that the bin will be picked up.  The bin will be lifted slightly, then lifted
    //much more as horizontal motion begins.
    void LiftAndMoveWithDelay (float x, float y, float speedMultiplier, float height, float StartMovePosition, std::string debugMessage){
        if (!(IsAutonomous() && IsEnabled()))
                    {return;}
        SmartDashboard::PutString("DB/String 0", debugMessage);

        m_elevator->setElevatorGoalPosition(height);
        bool moveTriggered = false;
        while(IsAutonomous() && IsEnabled() && (!m_autoPID.NearGoal() || !m_elevator->elevatorIsAt(height)))
        {
            //This cannot be used generally; it only will work for leftward motion.
            if (!moveTriggered && m_elevator->elevatorPosition() >= StartMovePosition){
                m_autoPID.SetGoal(x, y, speedMultiplier);
                moveTriggered = true;
            }
            m_elevator->updateProfile();
            DisplayInfo();
            Wait(0.005);
        }
    }

    void IRPickup (double extraMove, float speedMultiplier, std::string debugMessage) {
        Move(0.0, m_IRAdjust.GetMove(extraMove), speedMultiplier, debugMessage);
    }

};

START_ROBOT_CLASS(Robot);
