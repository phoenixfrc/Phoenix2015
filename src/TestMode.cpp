/*
 * TestMode.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "Constants.h"
#include "TestMode.h"
#include "WPILib.h"
#include "math.h"
#include "Team2342Joystick.h"
#include <sstream>

//Set limitSwitch port on init
TestMode::TestMode(): m_buttonWasPressed(false){}

void TestMode::PerformTesting(Joystick * gamePad, Team2342Joystick * stick,  Talon * motor1,
        Talon * motor2,  RobotDrive * driveTrain,
        Relay * ElevatorBrake){


    //Move robot:
    driveTrain->MecanumDrive_Cartesian(stick->GetX(), stick->GetY(), stick->GetZWithDeadZone(0.1));

    //Move elevator:
    float thumbstick = -gamePad->GetY()/4;
    thumbstick = fabs(thumbstick) < 0.0125 ? 0 : thumbstick;

    //inverted motor speeds because main robot has oposite wiring from test robot
    motor1->Set(-thumbstick);
    motor2->Set(-thumbstick);

    //Toggle Brake:
    bool buttonState = gamePad->GetRawButton(5);
    bool buttonHit = buttonState && (! m_buttonWasPressed);
    m_buttonWasPressed = buttonState;

    if (buttonHit){
        if (ElevatorBrake->Get() == ElevatorBrake->kOff){
            ElevatorBrake->Set(ElevatorBrake->kForward);
        } else{
            ElevatorBrake->Set(ElevatorBrake->kOff);
        }
    }



}

TestMode::~TestMode(){

}


