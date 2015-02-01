
#include "Elevator.h"
#include "Constants.h"
#include <sstream>
#include <stdio.h>



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
    m_brake(ElevatorBrake)
{
    printf("in elevator constructor...\n");
    m_homeState = lookingForLowerLimit;
    m_encoder->SetDistancePerPulse(8.17 / Ticks);
    m_elevatorControl = new PIDController(0.1, 0.001, 0.0, encoder, this);
}

void Elevator::operateElevator()
{

    if(m_homeState == homingComplete)
    {
        controlElevator();
    }
    else
    {
        find_home();
    }


}
bool Elevator::elevatorIsHomed()
{
    return(m_homeState == homingComplete);
}
bool Elevator::elevatorIsAt(float position)
{
    float currentPosition = (m_encoder->Get() / 8.17);
    return((currentPosition < (position + 0.5)) && (currentPosition > (position - 0.5)));
}

void Elevator::find_home()
{
        double speed = 0.0;
        if (m_homeState == lookingForLowerLimit)
        {
            if(!(m_lowerLimit->Get())) // change from !(m_lowerLimit->Get()) to m_lowerLimit->Get() after lower limit is changed
            {
                m_homeState = goingUpToHome;
            }
            else
            {
                speed = -HomeSpeed;
            }
        }

        if (m_homeState == goingUpToHome)
        {
            if(!(m_lowerLimit->Get())) //if(m_homeSwitch->Get())
            {
                m_homeState = homingComplete;
                m_encoder->Reset();
                m_elevatorControl->Enable();

            }
            else
            {
                speed = HomeSpeed;
            }
        }

        PIDWrite(speed);
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
    bool rbPressed = m_gamepad->GetRawButton(6);
    bool rtPressed = m_gamepad->GetRawButton(8);

    bool rbWasPressed = false;
    bool rtWasPressed = false;

    //joystick
    double joystick = -m_gamePad->GetY(); // right Joystick, negative because up is negative

    float goalPosition = m_elevatorControl->GetSetpoint();

    // button computing
    if(rbPressed && !rbWasPressed)
    {
        goalPosition += 4;
        rbWasPressed = true;
    }
    else if(!rbPressed && rbWasPressed)
    {
        rbWasPressed = false;
    }

    if(rtPressed && !rtWasPressed)
    {
        goalPosition -= 4;
        rtWasPressed = true;
    }
    else if(!rtPressed && rtWasPressed)
    {
        rtWasPressed = false;
    }


    //Joystick computing
    if(!(joystick > -0.05 && joystick < 0.05))
    {
        goalPosition += (joystick / 5);
    }

    if (goalPosition > 85)
    {

    	goalPosition = 85; //Stop large queues of goal position
    }
    if (goalPosition < 0)
    {

    	goalPosition = 0; //stop large queues of goal position

    }

    ElevatorJoystickbuilder << "GoalPosition: ";
    ElevatorJoystickbuilder << goalPosition;
    SmartDashboard::PutString("DB/String 0", ElevatorJoystickbuilder.str());
    ElevatorJoystickbuilder2 << "position: ";
    ElevatorJoystickbuilder2 << (m_encoder->Get() / 8.17);
    SmartDashboard::PutString("DB/String 1", ElevatorJoystickbuilder2.str());

    setElevatorGoalPosition(goalPosition);

}

void Elevator::setElevatorGoalPosition(float position)
{
    m_elevatorControl->SetSetpoint(position);
}

void Elevator::PIDWrite(float desiredSpeed)
{
    bool atUpperLimit = m_upperLimit->Get();
    bool atLowerLimit = !(m_lowerLimit->Get()); // change from !(m_lowerLimit->Get()) to m_lowerLimit->Get() after lower limit is changed;
    float actualSpeed = desiredSpeed;
    float deadZone = 0.1;

    if (atUpperLimit && (desiredSpeed > 0.0))
    {
        actualSpeed = 0.0; // don't move past upper limit
    }
    if (atLowerLimit && (desiredSpeed < 0.0))
    {
        actualSpeed = 0.0; // don't move past lower limit
    }

    if (((actualSpeed < 0.0 - deadZone) || (actualSpeed > 0.0 + deadZone)) && !(m_brake->Get() == m_brake->kOff))
    {
        m_brake->Set(m_brake->kOff);
    }

    // set the motor speed
    m_motor1->Set(actualSpeed);
    m_motor2->Set(actualSpeed);

    if (((actualSpeed > 0.0 - deadZone) && (actualSpeed < 0.0 + deadZone)) && !(m_brake->Get() == m_brake->kForward))
    {
        m_brake->Set(m_brake->kForward);
    }
}


Elevator::~Elevator(){}

