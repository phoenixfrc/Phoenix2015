/*
 * Elevator.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "Elevator.h"
#include "Constants.h"

Elevator::Elevator():
    lowerLimit(1),
    upperLimit(2),
    home(3),
    motor1(4),
    motor2(5),
    encoder(PortAssign::encoderChannelA, PortAssign::encoderChannelB )
{

	currentMode = buttonMode;
	offSetState = none;

}

void Elevator::find_home()
{
    bool triped = false;
    while (!home.Get())
    {
        if(lowerLimit.Get())
        {
            triped = true;
        }

        if (!triped)
        {

            motor1.Set(-motorSpeed);		//go down
            motor2.Set(-motorSpeed);

        }

        else
        {

            motor1.Set(motorSpeed);			//go up
            motor2.Set(motorSpeed);

        }
    }
    encoder.Reset();
    distance = 0;
    motor1.Set(0);
    motor2.Set(0);
}





void Elevator::operateElevator(Joystick * gamePad)
{
    if (upperLimit.Get())
    {

        motor1.Set(0);
        motor2.Set(0);
    }
    else if (lowerLimit.Get())
    {
        motor1.Set(0);
        motor2.Set(0);
    }
    if(home.Get())
    {
        encoder.Reset();
    }

    distance = (encoder.Get() / ticks) * 8.17; // distance in inches from home.

    // switch mode
    if(gamePad->GetRawButton(3) && !switchWasPressed)
    {
        switch (currentMode)
        {
            case(buttonMode):
                currentMode = joystickMode;
                // gets the next goal distance,
                goalStep = int(distance / 13);
            break;

            case(joystickMode):
               currentMode = buttonMode;
            break;
        }
        switchWasPressed = true;
    }
    else if (!gamePad->GetRawButton(3) && switchWasPressed)
    {
        switchWasPressed = false;
    }

    //move code
    switch (currentMode)
    {

        case buttonMode:
            // 1 for up
            // 2 for down

            if(gamePad->GetRawButton(1) && !upperWasPressed)
            {
                if (goalStep < 3)
                {
                    goalStep += 1;
                }
                upperWasPressed = true;
            } else if (!gamePad->GetRawButton(1) && upperWasPressed)
            {
                upperWasPressed = false;
            }

            if(gamePad->GetRawButton(2) && lowerWasPressed)
            {
                if (goalStep > 0)
                {
                    goalStep -= 1;
                }
                lowerWasPressed = true;
            } else if (!gamePad->GetRawButton(2) && lowerWasPressed)
            {
                upperWasPressed = false;
            }

            moveElevator();
            break;

        case joystickMode:
            // Y > 0 up
            // Y < 0 down
            if((gamePad->GetY() > 0) && upperLimit.Get())
            {
                motor1.Set(motorSpeed);
                motor2.Set(motorSpeed);
            }
            else if((gamePad->GetY() < 0) && lowerLimit.Get())
            {
                motor1.Set(-motorSpeed);
                motor2.Set(-motorSpeed);
            }
            break;
    }
}


void Elevator::moveElevator()
{
    /* 0 = 0in
     * 1 = 13in
     * 2 = 26in
     * 3 = 39in
     * 4 = 52in
     */
    switch(goalStep)
    {
        case 0:
            if((distance > -0.5) && (distance < 0.5))
            {
                motor1.Set(0);
                motor2.Set(0);
            }
            else if (distance < -0.5)
            {
                motor1.Set(motorSpeed);
                motor2.Set(motorSpeed);
            }
            else if (distance > 0.5)
            {
                motor1.Set(-motorSpeed);
                motor2.Set(-motorSpeed);
            }
            break;

        case 1:
            if(distance > 12.5 && distance < 13.5 )
                {
                    motor1.Set(0);
                    motor2.Set(0);
                }
                else if (distance < 12.5)
                {
                    motor1.Set(motorSpeed);
                    motor2.Set(motorSpeed);
                }
                else if (distance > 13.5)
                {
                    motor1.Set(-motorSpeed);
                    motor2.Set(-motorSpeed);
                }
            break;

        case 2:
            if(distance > 25.5 && distance < 26.5 )
                {
                    motor1.Set(0);
                    motor2.Set(0);
                }
                else if (distance < 25.5)
                {
                    motor1.Set(motorSpeed);
                    motor2.Set(motorSpeed);
                }
                else if (distance > 26.5)
                {
                    motor1.Set(-motorSpeed);
                    motor2.Set(-motorSpeed);
                }
            break;

        case 3:
            if(distance > 38.5 && distance < 39.5 )
                {
                    motor1.Set(0);
                    motor2.Set(0);
                }
                else if (distance < 38.5)
                {
                    motor1.Set(motorSpeed);
                    motor2.Set(motorSpeed);
                }
                else if (distance > 39.5)
                {
                    motor1.Set(-motorSpeed);
                    motor2.Set(-motorSpeed);
                }
            break;

        case 4:
            if(distance > 51.5 && distance < 52.5 )
                {
                    motor1.Set(0);
                    motor2.Set(0);
                }
                else if (distance < 51.5)
                {
                    motor1.Set(motorSpeed);
                    motor2.Set(motorSpeed);
                }
                else if (distance >52.5)
                {
                    motor1.Set(-motorSpeed);
                    motor2.Set(-motorSpeed);
                }
            break;
    }
}





Elevator::~Elevator(){}
