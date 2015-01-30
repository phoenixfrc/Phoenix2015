
#include "Elevator.h"
#include "Constants.h"

Elevator::Elevator(
        Talon* motor1,
        Talon* motor2,
        DigitalInput* lowerLimit,
        DigitalInput* upperLimit,
        DigitalInput* homeSwitch,
        Encoder* encoder,
        Joystick* gamePad):

    m_motor1(motor1),
    m_motor2(motor2),
    m_lowerLimit(lowerLimit),
    m_upperLimit(upperLimit),
    m_homeSwitch(homeSwitch),
    m_encoder(encoder),
    m_gamePad(gamePad)
{
    homeState = lookingForLowerLimit;


}
void Elevator::operateElevator()
{
    bool rightTrigger = m_gamePad->GetRawButton(8);
    if(rightTrigger && (homeState == homingComplete))
    {
        homeState = lookingForLowerLimit;
    }

    if(homeState == homingComplete)
    {
        controlElevator();
    }
    else
    {
        find_home();
    }


}



void Elevator::find_home()
{
        double speed = 0.0;
        switch(homeState)
        {
            case lookingForLowerLimit:
                if(m_lowerLimit->Get())
                {
                    homeState = goingUpToHome;
                }
                else
                {
                    speed = -MotorSpeed;
                }
            break;
            case goingUpToHome:
                if(m_homeSwitch->Get())
                {
                    homeState = homingComplete;
                    m_encoder->Reset();
                }
                else
                {
                    speed = HomeSpeed;
                }

            break;
            case homingComplete:
            break;
        }
        moveMotors(speed);
}





void Elevator::controlElevator()
{
    //buttons
    bool xPressed = m_gamePad->GetRawButton(1);
    bool aPressed = m_gamePad->GetRawButton(2);
    bool bPressed = m_gamePad->GetRawButton(3);
    bool yPressed = m_gamePad->GetRawButton(4);

    //joystick
    double joystick = m_gamePad->GetY(); // right Joystick

    // distance from home
    m_distance = (m_encoder->Get() * 8.17) / Ticks;

    // button computing
    if(xPressed)
    {
        m_goalDistance = Heights[0];
    }
    if(aPressed)
    {
        m_goalDistance = Heights[1];
    }
    if(bPressed)
    {
        m_goalDistance = Heights[2];
    }
    if(yPressed)
    {
        m_goalDistance = Heights[3];
    }

    //Joystick computing
    if(!(joystick > -0.05 && joystick < 0.05))
    {
        m_goalDistance += (joystick / 20);
    }

    moveElevator();

}


void Elevator::moveElevator()
{
    if(m_distance > (m_goalDistance - Range) && m_distance < (m_goalDistance + Range))
    {
        moveMotors(0.0);
    }

    if(m_distance > m_goalDistance)
    {
        moveMotors(-MotorSpeed);
    }

    if(m_distance < m_goalDistance)
    {
        moveMotors(MotorSpeed);
    }



}

void Elevator::moveMotors(double desiredSpeed)
{
    bool atUpperLimit = m_upperLimit->Get();
    bool atLowerLimit = m_lowerLimit->Get();
    double actualSpeed = desiredSpeed;


    if (atUpperLimit && (desiredSpeed > 0.0))
    {
        actualSpeed = 0.0; // don't move past upper limit
    }
    if (atLowerLimit && (desiredSpeed < 0.0))
    {
        actualSpeed = 0.0; // don't move past lower limit
    }

    // set the motor speed
    m_motor1->Set(actualSpeed);
    m_motor2->Set(actualSpeed);
}




Elevator::~Elevator(){}

