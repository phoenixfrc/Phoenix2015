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
TestMode::TestMode():limitSwitch1(1){}


void TestMode::PerformTesting(Joystick * gamePad, Team2342Joystick * stick, Encoder * leftRearDriveEncoder,
		Encoder * leftFrontDriveEncoder,Encoder * rightFrontDriveEncoder,
		Encoder * rightRearDriveEncoder, Gyro * gyro, Talon * motor1, Talon * motor2,  RobotDrive * driveTrain){

    //init string builders:
    std::ostringstream gyroBuilder, limitBuilder, eblr, eblf, ebrf, ebrr, elevatorBuilder;

    //Move robot:
	driveTrain->MecanumDrive_Cartesian(stick->GetX(), stick->GetY(), stick->GetZWithDeadZone(0.1));

	//Move elevator:
	float thumbstick = -gamePad->GetY()/4;
	thumbstick = fabs(thumbstick) < 0.0125 ? 0 : thumbstick;
	motor1->Set(thumbstick);
	motor2->Set(thumbstick);

    //Prints out the values for gyro:
    gyroBuilder << "The Gyro angle is: ";
    gyroBuilder << gyro->GetAngle();
    SmartDashboard::PutString("DB/String 0", gyroBuilder.str());

    //Prints out the values for the limit switch:
    limitBuilder << "The Limit Switch value is: ";
    limitBuilder << limitSwitch1.Get();
    SmartDashboard::PutString("DB/String 1", limitBuilder.str());

    //Print the Elevator value:
    elevatorBuilder << "Elvtr 1:" << motor1->Get() << ", 2:" << motor2->Get();
    SmartDashboard::PutString("DB/String 2", elevatorBuilder.str());

    //Print Encoder values:
	eblr << "Encoder: LR, Value: "<< leftRearDriveEncoder->Get();
	SmartDashboard::PutString("DB/String 5", eblr.str());
	eblf << "Encoder: LF, Value: "<< leftFrontDriveEncoder->Get();
    SmartDashboard::PutString("DB/String 6", eblf.str());
    ebrf << "Encoder: RF, Value: "<< rightFrontDriveEncoder->Get();
    SmartDashboard::PutString("DB/String 7", ebrf.str());
    ebrr << "Encoder: RR, Value: "<< rightRearDriveEncoder->Get();
    SmartDashboard::PutString("DB/String 8", ebrr.str());
}

TestMode::~TestMode(){

}


