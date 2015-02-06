#ifndef TESTMODE_H
#define TESTMODE_H

#include "WPILib.h"
#include "EncoderTracker.h"
#include "Team2342Joystick.h"


enum testModes{testElevator, testJoystick, testTalon, testEncoder, testGyro, testLimitSwitch};

class TestMode
{
	public:

		TestMode();
		void PerformTesting(Joystick * gamePad, Team2342Joystick * stick,  Talon * motor1,
				Talon * motor2,  RobotDrive * driveTrain, Relay * ElevatorBrake);
		~TestMode();
	private:
		bool m_buttonWasPressed;
};

#endif
