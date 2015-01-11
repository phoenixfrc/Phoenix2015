#ifndef TESTMODE_H
#define TESTMODE_H

#include "WPILib.h"


enum testModes{testElevator, testJoystick, testTalon, testEncoder, testGyro};

class TestMode
{
	public:

		TestMode();
		void PerformTesting(Joystick * gamePad, Encoder * encoder);

	private:
		testModes c_mode; //current mode

};

#endif
