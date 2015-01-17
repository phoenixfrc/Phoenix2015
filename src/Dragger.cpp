/*
 * Dragger.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: Ray
 */
#include "Constants.h"
#include "Dragger.h"
#include "WPILib.h"

Dragger::Dragger():
motor(PortAssign::draggerMotorPort),
limitSwitchUp(PortAssign::limitSwitchUpPort),
limitSwitchDown(PortAssign::limitSwitchDownPort)
{

}

Dragger::operateDragger(Joystick * button){
    bool buttonPressed = button->GetRawButton(1); //Gets button state, 1 is placeholder value

    bool isUp = limitSwitchUp.Get(); //Is the up limit switch triggered?
    bool isDown = limitSwitchDown.Get(); //Is the down limit switch triggered?

    float motorSpeed = 0.25;
    float motorSpeedUp = motorSpeed;
    float motorSpeedDown = -motorSpeed;



    //Long version (commented out, in case it's preferred):

    /*if (buttonPressed){ // If the button is pressed:
        if (isUp){
            motor.Set(motorSpeedDown); // Set the downward speed.
        } else if (isDown){
            motor.Set(motorSpeedUp); // Set the upward speed.
        }
    } else {
        if (isUp||isDown){ // If either limit switch is triggered:
            motor.Set(0); // Stop the motor.
        }
    }*/


    //Short version:

    if (isUp || isDown)
    	motor.Set(buttonPressed ? (isUp ? motorSpeedDown : motorSpeedUp) : 0);


}

