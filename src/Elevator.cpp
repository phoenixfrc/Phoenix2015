#include "Elevator.h"
#include "Constants.h"

Elevator::Elevator():
    lowerLimit(PortAssign::lowerLimitSwitch),
    upperLimit(PortAssign::upperLimitSwitch),
    homeSwitch(PortAssign::homeSwitch),
    motor1(PortAssign::elevatorMotor1),//more discriptive names for motor1 and motor2
    motor2(PortAssign::elevatorMotor2),
    encoder(PortAssign::encoderChannelA, PortAssign::encoderChannelB )
{



}

void Elevator::find_home()
{
    bool tripped = false;
    while (!homeSwitch.Get())
    {
        if(lowerLimit.Get())
        {
            tripped = true;
        }

        if (!tripped)
        {

            moveMotors(-HomeSpeed);

        }

        else
        {

            moveMotors(HomeSpeed);

        }
    }
    encoder.Reset();
    m_distance = 0;
    moveMotors(0);
}





void Elevator::operateElevator(Joystick * gamePad)
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

void Elevator::moveMotors(double speed)
{
    bool upper = upperLimit.Get();
    bool lower = lowerLimit.Get();

    if(speed < 0 && !lower)
    {
        motor1.Set(speed);
        motor2.Set(speed);
    }
    else if(speed > 0 && !upper)
    {
        motor1.Set(speed);
        motor2.Set(speed);
    }
    else if(!speed)
    {
        motor1.Set(speed);
        motor2.Set(speed);
    }


}




Elevator::~Elevator(){}
