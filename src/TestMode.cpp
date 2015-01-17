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
}

void TestMode::PerformTesting(Joystick * gamePad, Encoder * encoder,
		Encoder * driveEncoder1, Encoder * driveEncoder2,
		Encoder * driveEncoder3, Encoder * driveEncoder4, Gyro * gyro){
	std::ostringstream builder;
	std::ostringstream limitBuilder;
	std::ostringstream gyroBuilder;

	bool button1 = gamePad->GetRawButton(1);
	bool button2 = gamePad->GetRawButton(2);

	switch (c_mode){
		case testElevator:

			if(button1)
			{
				c_mode = testJoystick;
			}
			if(button2)
			{
				c_mode = testTalon;
			}
			break;
		case testJoystick:

			if(button1)
			{
				c_mode = testTalon;				
			}
			if(button2)
			{
				c_mode = testElevator;
			}
			break;
		case testTalon:

			if(button1)
			{
				c_mode = testEncoder;
			}
			if(button2)
			{
				c_mode = testJoystick;
			}
			break;
		case testEncoder:

			builder << "The encoder value is: ";
			builder << encoder->Get();
			SmartDashboard::PutString("DB/String 0", builder.str());

			if(button1)
			{
				c_mode = testGyro;
			}
			if(button2)
			{
				c_mode = testTalon;
			}
			break;
		case testGyro:

			//Prints out the values for gyro.
			gyroBuilder << "The Gyro angle is: ";
			gyroBuilder << gyro->GetAngle();
			SmartDashboard::PutString("DB/String 2", gyroBuilder.str());

			if(button1)
			{
				c_mode = testLimitSwitch;
			}
			if(button2)
			{
				c_mode = testEncoder;
			}
			break;
		case testLimitSwitch:

			limitBuilder << "The Limit Switch value is: ";
			limitBuilder << limitSwitch1.Get();
			//Prints out the values for the limit switch
			SmartDashboard::PutString("DB/String 1", limitBuilder.str());

			if(button1)
			{
				c_mode = testElevator;
			}
			if(button2)
			{
				c_mode = testGyro;
			}
	}
}
TestMode::~TestMode(){

}


