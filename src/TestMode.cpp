/*
 * TestMode.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "TestMode.h"
#include "WPILib.h"
#include <sstream>


TestMode::TestMode(){

}

void TestMode::PerformTesting(Encoder * encoder){
	std::ostringstream builder;
	builder << "The encoder value is: ";
	builder << encoder->Get();
	SmartDashboard::PutString("DB/String 0", builder.str());
}



