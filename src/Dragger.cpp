/*
 * Dragger.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: Ray
 */
#include "Constants.h"
#include "Dragger.h"
#include "WPILib.h"
#include <sstream>

/* Dragger constructor
 * Call the constructors of the motor and limit switches, using port numbers from the Constants.h file.
 */


Dragger::Dragger():
m_timer(kDraggerReverseTime * 200),//max value for ints
m_liftDuration(kDraggerReverseTime),
m_downSpeed(kDraggerMotorDownSpeed),
m_upSpeed(kDraggerMotorUpSpeed)
{}

/* Dragger operateDragger method:
 * Takes one Joystick parameter, to get a boolean for the button press.
 * Gets whether the limit switches have been triggered.
 * Activates the motor appropriately.
 *
 * To-do: get the button number from Constants.h
 */


void Dragger::operateDragger(Joystick * button, DigitalInput * limitSwitchDown, Talon * motor){

    bool buttonPressed = button->GetRawButton(1); //Gets button state, 1 is a placeholder value

    bool isUp = m_timer >= (m_liftDuration*200);//m_liftDuration is in seconds, and needs to converted to 200ths of seconds
    bool isDown = limitSwitchDown->Get(); //Is the down limit switch triggered?
    if(isDown){
        m_timer = 0;
    }else{
    	m_timer++;
    }
    std::ostringstream bob;
    bob << isUp << buttonPressed;
    SmartDashboard::PutString("DB/String 8", bob.str());


    /* Sets the motor speed to up, down or stopped depending on the button press and limit switches:
     *    If the upper limit switch is tripped: stop the motor, or, if the button is pressed, move the motor down
     *    If the lower limit switch is tripped: stop the motor, or, if the button is pressed, move the motor up
     *    If both limits are somehow tripped (???): stop the motor, to prevent the robot from breaking anything.
     *    If neither limit is tripped: do nothing, the motor will continue to move in its old direction.
     */


    if (isUp || isDown){
        if (buttonPressed && (isUp != isDown)){
            if (isUp){
                motor->Set(-m_downSpeed);
                m_timer = 0;
            } else if(isDown){
                motor->Set(m_upSpeed);
            }
        } else {
            motor->Set(0);
        }

    }
}
Dragger::~Dragger(){

}
