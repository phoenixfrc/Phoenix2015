#include "Elevator.h"
#include "Constants.h"

Elevator::Elevator():
    lowerLimit(PortAssign::ElevatorLowerLimitChannel),
    upperLimit(PortAssign::ElevatorUpperLimitChannel),
    homeSwitch(PortAssign::ElevatorHomeSwitchChannel),
    motor1(PortAssign::ElevatorMotorPort1),
    motor2(PortAssign::ElevatorMotorPort2),
    encoder(PortAssign::ElevatorEncoderChannelA, PortAssign::ElevatorEncoderChannelA)
{
    homeState = lookingForLowerLimit;


}
void Elevator::operateElevator(Joystick * gamePad)
{
    bool rightTrigger = gamePad->GetRawButton(8);

    if(!rightTrigger && (homeState == homingComplete))
    {
        controlElevator(gamePad);
    }
    else if(rightTrigger && (homeState == homingComplete))
    {
        homeState = lookingForLowerLimit;
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
                if(lowerLimit.Get())
                {
                    homeState = goingUpToHome;
                }
                else
                {
                    speed = -MotorSpeed;
                }
            break;
            case goingUpToHome:
                if(homeSwitch.Get())
                {
                    homeState = homingComplete;
                }
                else
                {
                    speed = HomeSpeed;
                }

            break;
        }
        moveMotors(speed);
}





void Elevator::controlElevator(Joystick * gamePad)
{
    //buttons
    bool xPressed = gamePad->GetRawButton(1);
    bool aPressed = gamePad->GetRawButton(2);
    bool bPressed = gamePad->GetRawButton(3);
    bool yPressed = gamePad->GetRawButton(4);

    //joystick
    double joystick = gamePad->GetY(); // right Joystick

    // distance from home
    m_distance = (encoder.Get() * 8.17) / Ticks;

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

    bool home = homeSwitch.Get();

    if(home)
    {
        encoder.Reset();
    }

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
    bool atUpperLimit = upperLimit.Get();
    bool atLowerLimit = lowerLimit.Get();
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
    motor1.Set(actualSpeed);
    motor2.Set(actualSpeed);
}




Elevator::~Elevator(){}
