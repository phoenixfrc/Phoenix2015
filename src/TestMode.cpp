/*
 * TestMode.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "Constants.h"
#include "TestMode.h"
#include "WPILib.h"
#include "math.h"
#include "Team2342Joystick.h"
#include <sstream>

//Set limitSwitch port on init
TestMode::TestMode(): m_buttonWasPressed(false){}


void TestMode::PerformTesting(Joystick * gamePad, Team2342Joystick * stick, Encoder * leftRearDriveEncoder,
		Encoder * leftFrontDriveEncoder,Encoder * rightFrontDriveEncoder,
		Encoder * rightRearDriveEncoder, Gyro * gyro, Talon * motor1,
		Talon * motor2,  RobotDrive * driveTrain, Encoder * ElevatorEncoder,
		Relay * ElevatorBrake, DigitalInput * lowerElevatorLimitSwitch,
		DigitalInput * upperElevatorLimitSwitch, DigitalInput * homeElevatorLimitSwitch,
		DigitalInput *opticalSensor,
		DigitalInput *draggerLowerLimit,
		DigitalInput *draggerUpperLimit,
		DigitalInput *dio16,
		DigitalInput *dio17,
		DigitalInput *dio18,
		DigitalInput *dio19,
		DigitalInput *dio20,
		DigitalInput *dio21,
		DigitalInput *dio22,
		DigitalInput *dio23,
		DigitalInput *dio24,
		DigitalInput *dio25){

    //init string builders:
    std::ostringstream gyroBuilder, eblr, eblf, ebrf, ebrr,
		elevatorBuilder1, elevatorBuilder2, elevatorEncoderBuilder, elevatorBuilder3;

    //Move robot:
	driveTrain->MecanumDrive_Cartesian(stick->GetX(), stick->GetY(), stick->GetZWithDeadZone(0.1));

	//Move elevator:
	float thumbstick = -gamePad->GetY()/4;
	thumbstick = fabs(thumbstick) < 0.0125 ? 0 : thumbstick;
	motor1->Set(thumbstick);
	motor2->Set(thumbstick);

	//Toggle Brake:
	bool buttonState = gamePad->GetRawButton(5);
	bool buttonHit = buttonState && (! m_buttonWasPressed);
	m_buttonWasPressed = buttonState;

	if (buttonHit){
	    if (ElevatorBrake->Get() == ElevatorBrake->kOff){
	        ElevatorBrake->Set(ElevatorBrake->kForward);
	    } else{
	        ElevatorBrake->Set(ElevatorBrake->kOff);
            }
	}

    //Prints out the values for gyro:
    gyroBuilder << "The Gyro angle is: ";
    gyroBuilder << gyro->GetAngle();
    SmartDashboard::PutString("DB/String 0", gyroBuilder.str());


    //Print the Elevator value:
    elevatorBuilder1 << "ElevatorTal#1: " << motor1->Get();
    SmartDashboard::PutString("DB/String 2", elevatorBuilder1.str());

    elevatorBuilder2 << "ElevatorTal#2: " << motor2->Get();
    SmartDashboard::PutString("DB/String 3", elevatorBuilder2.str());

    elevatorEncoderBuilder << "ElevatorEnc: " << ElevatorEncoder->Get();
    SmartDashboard::PutString("DB/String 4", elevatorEncoderBuilder.str());


    //Print Encoder values:
	eblr << "Encoder: LR, Value: "<< leftRearDriveEncoder->Get();
	SmartDashboard::PutString("DB/String 5", eblr.str());
	eblf << "Encoder: LF, Value: "<< leftFrontDriveEncoder->Get();
    SmartDashboard::PutString("DB/String 6", eblf.str());
    ebrf << "Encoder: RF, Value: "<< rightFrontDriveEncoder->Get();
    SmartDashboard::PutString("DB/String 7", ebrf.str());
    ebrr << "Encoder: RR, Value: "<< rightRearDriveEncoder->Get();
    SmartDashboard::PutString("DB/String 8", ebrr.str());

    //Prints out the elevator limit switches
    elevatorBuilder3 << //"ElL,U,H;O;DL,U*: "<<
    		lowerElevatorLimitSwitch->Get() <<
			upperElevatorLimitSwitch->Get() <<
			homeElevatorLimitSwitch->Get() <<
			opticalSensor->Get() <<
			draggerLowerLimit->Get() <<
			draggerUpperLimit->Get() <<
			dio16->Get() <<
			dio17->Get() <<
			dio18->Get() <<
			dio19->Get() <<
			dio20->Get() <<
			dio21->Get() <<
			dio22->Get() <<
			dio23->Get() <<
			dio24->Get() <<
			dio25->Get();
    SmartDashboard::PutString("DB/String 9", elevatorBuilder3.str());

}

TestMode::~TestMode(){

}


