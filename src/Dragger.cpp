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
isDown(false),
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

    bool buttonPressed = button->GetRawButton(5); //Gets button state, 1 is a placeholder value
    bool button7 = button->GetRawButton(7);

    bool isUp = m_timer >= (m_liftDuration*200);//m_liftDuration is in seconds, and needs to converted to 200ths of seconds
    //Is the down limit switch triggered?

    if (limitSwitchDown->Get()){
    	isDown = true;
    }


    std::ostringstream bob, draggerState;
    bob << isUp << buttonPressed;
    SmartDashboard::PutString("DB/String 8", bob.str());

    //Read the button then toggle the variable
     /*   if(m_draggerDirection && (isUp = false)){
            m_timer++;
        }else{
        	m_timer = 0;
        } */
    /* Sets the motor speed to up, down or stopped depending on the button press and limit switches:
     *    If the upper limit switch is tripped: stop the motor, or, if the button is pressed, move the motor down
     *    If the lower limit switch is tripped: stop the motor, or, if the button is pressed, move the motor up
     *    If both limits are somehow tripped (???): stop the motor, to prevent the robot from breaking anything.
     *    If neither limit is tripped: do nothing, the motor will continue to move in its old direction.
     */
    switch (m_mode){
    	case upState:
    		draggerState << "Up State";
    		SmartDashboard::PutString("DB/String 9", draggerState.str());
    		motor->Set(0);
    		m_timer = 0;

    		if (button7){
    			m_mode = loweringState;
    		}
    		break;
    	case loweringState:
    		draggerState << "Lowering State";
    		SmartDashboard::PutString("DB/String 9", draggerState.str());
    		motor->Set(-m_downSpeed);
    		m_timer = 0;

    		if (limitSwitchDown){
    			m_mode = downState;
    		}
    		break;
    	case downState:
    		draggerState << "Down State";
    		SmartDashboard::PutString("DB/String 9", draggerState.str());
    		motor->Set(0);
    		m_timer = 0;

    		if (button7){
    			m_mode = liftingState;
    		}
    		break;
    	case liftingState:
    		draggerState << "Lifting State";
    		SmartDashboard::PutString("DB/String 9", draggerState.str());
    		motor->Set(-m_upSpeed);
    		m_timer ++;

    		if (isUp){
    			m_mode = upState;
    		}
    		break;
    	default:
    		m_mode = upState;
    		break;
    }

    /*    if (buttonPressed){
    	if(m_draggerDirection){
    		m_draggerDirection = false;
    	}else{
    		m_draggerDirection = true;
    		if(isDown){
    		        m_timer = 0;
    		    }
    	}

    }


  if (isUp || isDown){


        if ((isUp != isDown)){
        	if (m_draggerDirection){


        		if (isUp){


                motor->Set(0);
            } else if(isDown){
            	m_timer = 0;
            	motor->Set(-m_upSpeed);
            }
        } else if(m_draggerDirection == false){
        	if(isUp){
        		motor->Set(m_downSpeed);
        	}else if(isDown){
        		motor->Set(0);
        	}

            }
        } else {
            motor->Set(0);
        }

    } */
}
Dragger::~Dragger(){

}
