/*
 * Dragger.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: Ray
 */
#include "Constants.h"
#include "Dragger.h"
#include "WPILib.h"

/* Dragger constructor
 * Call the constructors of the motor and limit switches, using port numbers from the Constants.h file.
 */


Dragger::Dragger()
{}

/* Dragger operateDragger method:
 * Takes one Joystick parameter, to get a boolean for the button press.
 * Gets whether the limit switches have been triggered.
 * Activates the motor appropriately.
 *
 * To-do: get the button number from Constants.h
 */


void Dragger::operateDragger(Joystick * button, DigitalInput * limitSwitchDown, DigitalInput * limitSwitchUp, Talon * motor){

    bool buttonPressed = button->GetRawButton(1); //Gets button state, 1 is a placeholder value

    bool isUp = limitSwitchUp->Get(); //Is the up limit switch triggered?
    bool isDown = limitSwitchDown->Get(); //Is the down limit switch triggered?

    float motorSpeed = 0.25; //Sets the motor speed, 0.25 is a placeholder value
    float motorSpeedUp = motorSpeed;
    float motorSpeedDown = -motorSpeed;


    /* Sets the motor speed to up, down or stopped depending on the button press and limit switches:
     *    If the upper limit switch is tripped: stop the motor, or, if the button is pressed, move the motor down
     *    If the lower limit switch is tripped: stop the motor, or, if the button is pressed, move the motor up
     *    If both limits are somehow tripped (???): stop the motor, to prevent the robot from breaking anything.
     *    If neither limit is tripped: do nothing, the motor will continue to move in its old direction.
     */


    if (isUp || isDown)
        motor->Set(buttonPressed && (isUp != isDown) ? (isUp ? motorSpeedDown : motorSpeedUp) : 0);



}
Dragger::~Dragger(){

}
