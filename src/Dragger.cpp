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
m_upSpeed(kDraggerMotorUpSpeed),
m_draggerDirection(true),
m_mode(defaultState)
{}

/* Dragger operateDragger method:
 * Takes one Joystick parameter, to get a boolean for the button press.
 * Gets whether the limit switches have been triggered.
 * Activates the motor appropriately.
 *
 * To-do: get the button number from Constants.h
 */


void Dragger::operateDragger(Joystick * button, DigitalInput * limitSwitchDown, Talon * motor){

    bool button7 = button->GetRawButton(7);

    bool isUp = m_timer >= (m_liftDuration*200);//m_liftDuration is in seconds, and needs to converted to 200ths of seconds
    //Is the down limit switch triggered?
    bool isDown = limitSwitchDown->Get();

    /*std::ostringstream bob, draggerState;
    bob << "up:" << isUp << " dn:" << isDown << " B7:" << button7;
    SmartDashboard::PutString("DB/String 8", bob.str());

    * Sets the motor speed to up, down or stopped depending on the button press and limit switches:
     *    If the upper limit switch is tripped: stop the motor, or, if the button is pressed, move the motor down
     *    If the lower limit switch is tripped: stop the motor, or, if the button is pressed, move the motor up
     *    If both limits are somehow tripped (???): stop the motor, to prevent the robot from breaking anything.
     *    If neither limit is tripped: do nothing, the motor will continue to move in its old direction.
     */
    switch (m_mode){
    	case upState:
    		//draggerState << "up";
    		motor->Set(0);
    		m_timer = 0;

    		if (button7){
    			m_mode = loweringState;
    		}
    		break;
    	case loweringState:
    		//draggerState << "lowering";
    		motor->Set(m_downSpeed);
    		m_timer = 0;

    		if (isDown){
    			m_mode = downState;
    		}
    		break;
    	case downState:
    		//draggerState << "down";
    		motor->Set(0);
    		m_timer = 0;

    		if (button7){
    			m_mode = liftingState;
    		}
    		break;
    	case liftingState:
    		//draggerState << "lifting";
    		motor->Set(m_upSpeed);
    		m_timer ++;

    		if (isUp){
    			m_mode = upState;
    		}
    		break;
    	default:
    		m_mode = upState;
    		break;
    }

   // draggerState << " tim:" << m_timer;
    //SmartDashboard::PutString("DB/String 9", draggerState.str());

}
Dragger::~Dragger(){

}
