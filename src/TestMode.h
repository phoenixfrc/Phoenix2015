#ifndef TESTMODE_H
#define TESTMODE_H

#include "WPILib.h"
class TestMode
{
	public:
		enum testModes{testElevator, testJoystick, testTalon, testEncoder};

		TestMode();
		static void PerformTesting(Joystick * gamePad, Encoder * encoder);

	private:
		testModes c_mode; //current mode

};

#endif
