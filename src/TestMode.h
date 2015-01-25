#ifndef TESTMODE_H
#define TESTMODE_H

#include "WPILib.h"
#include "Team2342Joystick.h"


enum testModes{testElevator, testJoystick, testTalon, testEncoder, testGyro, testLimitSwitch};

class TestMode
{
	
	public:

		TestMode();
		void PerformTesting(Joystick * gamePad, Team2342Joystick * stick, Encoder * driveEncoder1,
				Encoder * driveEncoder2,Encoder * driveEncoder3,
				Encoder * driveEncoder4, Gyro * gyro, Talon * motor1, Talon * motor2,  RobotDrive * driveTrain);
		~TestMode();
	private:
		DigitalInput limitSwitch1;

};

#endif
