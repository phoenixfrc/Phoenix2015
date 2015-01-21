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

void TestMode::PerformTesting(Joystick * gamePad, Encoder * driveEncoder1,
		Encoder * driveEncoder2,Encoder * driveEncoder3,
		Encoder * driveEncoder4, Gyro * gyro, Talon * motor1, Talon * motor2){

    std::ostringstream mainMessageBuilder;
	std::ostringstream encoderBuilder;
	std::ostringstream limitBuilder;
	std::ostringstream gyroBuilder;

	mainMessageBuilder << "Testing: ";

	bool button1 = gamePad->GetRawButton(1);
	bool button2 = gamePad->GetRawButton(2);
	bool button3 = gamePad->GetRawButton(3);
	float thumbstick = gamePad->GetY();

	if (button3){
		currentEncoder++;
		currentEncoder %= 4;
	}

	bool button1Pressed = (button1&&(!oldButton1));
	bool button2Pressed = (button2&&(!oldButton2));

	switch (c_mode){
		case testElevator:

		    mainMessageBuilder << "Elevator";
		    if(-0.05 < thumbstick && thumbstick < 0.05)
		    {
			    motor1->Set(0);
			    motor2->Set(0);
		    }
		    else
		    {
		    motor1->Set(thumbstick);
		    motor2->Set(thumbstick);
		    }

			if(button1Pressed)
			{
				c_mode = testJoystick;
			}
			if(button2Pressed)
			{
				c_mode = testTalon;
			}
			break;
		case testJoystick:

		    mainMessageBuilder << "Joystick";

			if(button1Pressed)
			{
				c_mode = testTalon;				
			}
			if(button2Pressed)
			{
				c_mode = testElevator;
			}
			break;
		case testTalon:

		    mainMessageBuilder << "Talon";
			if(button1Pressed)
			{
				c_mode = testEncoder;
			}
			if(button2Pressed)
			{
				c_mode = testJoystick;
			}
			break;
		case testEncoder:

		    mainMessageBuilder << "Encoders";

		    encoderBuilder << "Encoder: ";
		    encoderBuilder << currentEncoder;
		    encoderBuilder << ", Value: ";
			switch (currentEncoder){
			    case 0:
			        encoderBuilder << driveEncoder1->Get();
			        break;
			    case 1:
			        encoderBuilder << driveEncoder2->Get();
			    	break;
			    case 2:
			        encoderBuilder << driveEncoder3->Get();
			    	break;
			    case 3:
			        encoderBuilder << driveEncoder4->Get();
			    	break;
			}

			SmartDashboard::PutString("DB/String 1", mainMessageBuilder.str());

			if(button1Pressed)
			{
				c_mode = testGyro;
			}
			if(button2Pressed)
			{
				c_mode = testTalon;
			}
			break;
		case testGyro:

		    mainMessageBuilder << "Gyro";

			//Prints out the values for gyro.
			gyroBuilder << "The Gyro angle is: ";
			gyroBuilder << gyro->GetAngle();
			SmartDashboard::PutString("DB/String 2", gyroBuilder.str());

			if(button1Pressed)
			{
				c_mode = testLimitSwitch;
			}
			if(button2Pressed)
			{
				c_mode = testEncoder;
			}
			break;
		case testLimitSwitch:

		    mainMessageBuilder << "Limit Switch";

			limitBuilder << "The Limit Switch value is: ";
			limitBuilder << limitSwitch1.Get();
			//Prints out the values for the limit switch
			SmartDashboard::PutString("DB/String 3", limitBuilder.str());

			if(button1Pressed)
			{
				c_mode = testElevator;
			}
			if(button2Pressed)
			{
				c_mode = testGyro;
			}
	}

	SmartDashboard::PutString("DB/String 0", mainMessageBuilder.str());

	oldButton1 = button1;
	oldButton2 = button2;
}

TestMode::~TestMode(){

}


