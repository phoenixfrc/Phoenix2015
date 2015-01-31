
#include "Elevator.h"
#include "Constants.h"
#include <sstream>




Elevator::Elevator(
        Talon* motor1,
        Talon* motor2,
        DigitalInput* lowerLimit,
        DigitalInput* upperLimit,
        DigitalInput* homeSwitch,
        Encoder* encoder,
        Joystick* gamePad,
        Relay* ElevatorBrake):

    m_homeState(lookingForLowerLimit),
    m_motor1(motor1),
    m_motor2(motor2),
    m_lowerLimit(lowerLimit),
    m_upperLimit(upperLimit),
    m_homeSwitch(homeSwitch),
    m_encoder(encoder),
    m_gamePad(gamePad),
    m_brake(ElevatorBrake),
    m_goalPosition(0),
    m_position(0)
{
    m_homeState = lookingForLowerLimit;
}

void Elevator::operateElevator()
{
    bool rightTrigger = m_gamePad->GetRawButton(8);


    if(m_homeState == homingComplete)
    {
        if(rightTrigger)
        {
            m_homeState = lookingForLowerLimit;
        }
        else
        {
            controlElevator();
        }
    }
    else
    {
        //find_home();
        m_homeState = homingComplete;

    }


}



void Elevator::find_home()
{
        double speed = 0.0;
        switch(m_homeState)
        {
            case lookingForLowerLimit:
                if(!(m_lowerLimit->Get())) // change from !(m_lowerLimit->Get()) to m_lowerLimit->Get() after lower limit is changed
                {
                    m_homeState = goingUpToHome;
                }
                else
                {
                    speed = -MotorSpeed;
                }
            break;
            case goingUpToHome:
                if(m_homeSwitch->Get())
                {
                    m_homeState = homingComplete;
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
    std::ostringstream ElevatorJoystickbuilder;
    std::ostringstream ElevatorJoystickbuilder2;

    //buttons
    bool xPressed = m_gamePad->GetRawButton(1);
    bool aPressed = m_gamePad->GetRawButton(2);
    bool bPressed = m_gamePad->GetRawButton(3);
    bool yPressed = m_gamePad->GetRawButton(4);

    //joystick
    double joystick = -m_gamePad->GetY(); // right Joystick, negative because up is negative

    // distance from home
    m_position = (m_encoder->Get() * 8.17) / Ticks;



    // button computing
    if(xPressed)
    {
        m_goalPosition = Heights[0];
    }
    if(aPressed)
    {
        m_goalPosition = Heights[1];
    }
    if(bPressed)
    {
        m_goalPosition = Heights[2];
    }
    if(yPressed)
    {
        m_goalPosition = Heights[3];
    }

    //Joystick computing
    if(!(joystick > -0.05 && joystick < 0.05))
    {
        m_goalPosition += (joystick / 5);
    }

    if (m_goalPosition > 85) {

    	m_goalPosition = 85; //Stop large queues of goal position
    }
    if (m_goalPosition < - 85) {

    	m_goalPosition = -85; //stop large queues of goal position

    }

    ElevatorJoystickbuilder << "GoalPosition: ";
    ElevatorJoystickbuilder << m_goalPosition;
    SmartDashboard::PutString("DB/String 0", ElevatorJoystickbuilder.str());
    ElevatorJoystickbuilder2 << "Position: ";
    ElevatorJoystickbuilder2 << m_position;
    SmartDashboard::PutString("DB/String 1", ElevatorJoystickbuilder2.str());

    moveElevator();

}


void Elevator::moveElevator()
{
    if(m_position > (m_goalPosition - Range) && m_position < (m_goalPosition + Range))
    {
        moveMotors(0.0);
    }

    else if(m_position > m_goalPosition)
    {
        moveMotors(-MotorSpeed);
    }

    else if(m_position < m_goalPosition)
    {
        moveMotors(MotorSpeed);
    }

    else
    {
        moveMotors(0.0);
    }



}

void Elevator::moveMotors(double desiredSpeed)
{
    bool atUpperLimit = m_upperLimit->Get();
    bool atLowerLimit = !(m_lowerLimit->Get()); // change from !(m_lowerLimit->Get()) to m_lowerLimit->Get() after lower limit is changed;
    double actualSpeed = desiredSpeed;


    if (atUpperLimit && (desiredSpeed > 0.0))
    {
        actualSpeed = 0.0; // don't move past upper limit
    }
    if (atLowerLimit && (desiredSpeed < 0.0))
    {
        actualSpeed = 0.0; // don't move past lower limit
    }

    if (actualSpeed != 0.0 && !(m_brake->Get() == m_brake->kOff))
    {
        m_brake->Set(m_brake->kOff);
    }

    // set the motor speed
    m_motor1->Set(actualSpeed);
    m_motor2->Set(actualSpeed);

    if (actualSpeed == 0.0 && !(m_brake->Get() == m_brake->kForward))
    {
        m_brake->Set(m_brake->kForward);
    }
}


Elevator::~Elevator(){}

