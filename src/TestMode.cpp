/*
 * TestMode.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "Constants.h"
#include "TestMode.h"
#include "WPILib.h"
#include <sstream>

					//Change limitSwitch Port
TestMode::TestMode():limitSwitch1(1){
	c_mode = testTalon;
	currentEncoder = 0;
	oldButton1 = false;
	oldButton2 = false;
}

void TestMode::PerformTesting(Joystick * gamePad,Encoder * driveEncoder1,
		Encoder * driveEncoder2,Encoder * driveEncoder3,
		Encoder * driveEncoder4, Gyro * gyro,
		EncoderTracker * tracker, RobotDrive * driveTrain){

    driveTrain->MecanumDrive_Cartesian(gamePad->GetX(), gamePad->GetY(), 0);//No rotation for testing

    std::ostringstream messageBuilderX;
    std::ostringstream messageBuilderY;

	messageBuilderX << "TrackerX: ";
	messageBuilderY << "TrackerY: ";

	messageBuilderX << tracker->GetX();
	messageBuilderY << tracker->GetY();

	SmartDashboard::PutString("DB/String 0", messageBuilderX.str());
	SmartDashboard::PutString("DB/String 1", messageBuilderY.str());
}

TestMode::~TestMode(){

}


