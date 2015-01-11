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


TestMode::TestMode(){
	c_mode = testTalon;
}

void TestMode::PerformTesting(Joystick * gamePad, Encoder * encoder){
	std::ostringstream builder;
	builder << "The encoder value is: ";
	builder << encoder->Get();
	SmartDashboard::PutString("DB/String 0", builder.str());

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

			if(button1)
			{
				c_mode = testElevator;
			}
			if(button2)
			{
				c_mode = testEncoder;
			}
			break;

	}
}



