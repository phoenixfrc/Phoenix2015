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
		void PerformTesting(Joystick * gamePad, Team2342Joystick * stick, Encoder * driveEncoder1,
				Encoder * driveEncoder2,Encoder * driveEncoder3,
				Encoder * driveEncoder4, Gyro * gyro, Talon * motor1, Talon * motor2,  RobotDrive * driveTrain, Encoder * elevatorEncoder,
				Relay * elevatorBrake, DigitalInput * lowerElevatorLimitSwitch, DigitalInput * upperElevatorLimitSwitch, DigitalInput * homeElevatorLimitSwitch,
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
				DigitalInput *dio25,
				EncoderTracker * tracker
				);
		~TestMode();
	private:
		bool m_buttonWasPressed;
		float m_prevGyroAng;
};

#endif
