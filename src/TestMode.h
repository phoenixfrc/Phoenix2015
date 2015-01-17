#ifndef TESTMODE_H
#define TESTMODE_H

#include "WPILib.h"


enum testModes{testElevator, testJoystick, testTalon, testEncoder, testGyro, testLimitSwitch};

class TestMode
{
	
	public:

		TestMode();
		void PerformTesting(Joystick * gamePad, Encoder * encoder, Gyro * gyro);

	private:
		testModes c_mode; //current mode
		DigitalInput limitSwitch1;

};

#endif
