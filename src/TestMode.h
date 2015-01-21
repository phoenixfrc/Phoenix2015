#ifndef TESTMODE_H
#define TESTMODE_H

#include "WPILib.h"


enum testModes{testElevator, testJoystick, testTalon, testEncoder, testGyro, testLimitSwitch};

class TestMode
{
	
	public:

		TestMode();
		void PerformTesting(Joystick * gamePad,
				Encoder * driveEncoder1, Encoder * driveEncoder2,
				Encoder * driveEncoder3, Encoder * driveEncoder4, Gyro * gyro, Talon * motor1, Talon * motor2);
		~TestMode();
	private:
		testModes c_mode; //current mode
		DigitalInput limitSwitch1;
		int currentEncoder;

		bool oldButton2;
		bool oldButton1;

};

#endif
