
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
        m_rbWasPressed(false),
        m_rtWasPressed(false),
        m_motor1(motor1),
        m_motor2(motor2),
        m_lowerLimit(lowerLimit),
        m_upperLimit(upperLimit),
        m_homeSwitch(homeSwitch),
        m_encoder(encoder),
        m_gamePad(gamePad),
        m_brake(ElevatorBrake),
        m_homeState(lookingForLowerLimit)
{
    printf("in elevator constructor...\n");
    m_homeState = lookingForLowerLimit;
    m_speedMultiplier = kNormalMultiplier;
    m_encoder->SetDistancePerPulse(1 / TicksPerInch);
    m_elevatorControl = new PIDController(0.1, 0.0, 0.0, encoder, this);
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
    float currentPosition = (m_encoder->Get() / TicksPerInch);
    return((currentPosition < (position + 0.5)) && (currentPosition > (position - 0.5)));
}

void Elevator::find_home()
{
    double speed = 0.0;
    if (m_homeState == lookingForLowerLimit)
    {
        if(m_lowerLimit->Get())
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
        if(m_lowerLimit->Get()) //if(m_homeSwitch->Get())
        {
            m_homeState = homingComplete;
            m_encoder->Reset();
            setElevatorGoalPosition(0.0, 1.0);
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

    float speedMult = m_speedMultiplier;

    //buttons
    bool xPressed = m_gamePad->GetRawButton(1);
    bool aPressed = m_gamePad->GetRawButton(2);
    bool bPressed = m_gamePad->GetRawButton(3);
    bool yPressed = m_gamePad->GetRawButton(4);
    bool rbPressed = m_gamePad->GetRawButton(6);
    bool rtPressed = m_gamePad->GetRawButton(8);



    //joystick
    double joystick = -m_gamePad->GetY(); // right Joystick, negative because up is negative

    float goalPosition = m_elevatorControl->GetSetpoint();

    // button computing
    if(rbPressed && !m_rbWasPressed)
    {
        speedMult = kShortLiftMultiplier;
        goalPosition += kLiftDelta;
        m_rbWasPressed = true;
    }
    else if(!rbPressed && m_rbWasPressed)
    {
        m_rbWasPressed = false;
    }

    if(rtPressed && !m_rtWasPressed)
    {
        speedMult = kNormalMultiplier;
        goalPosition -= kLiftDelta;
        m_rtWasPressed = true;
    }
    else if(!rtPressed && m_rtWasPressed)
    {
        m_rtWasPressed = false;
    }

    //Joystick computing
    // TODO limit offset from joystick
    if(!(joystick > -0.05 && joystick < 0.05))
    {
        speedMult = kNormalMultiplier;
        goalPosition += (joystick / 5);
    }

    if(aPressed)
    {
        speedMult = kNormalMultiplier;
        goalPosition = kElevatorHook1Ready;
    }
    if(bPressed)
    {
        speedMult = kNormalMultiplier;
        goalPosition = kElevatorHook2Ready;
    }

    if (goalPosition > kSoftUpperLimit)
    {

        goalPosition = kSoftUpperLimit; //Stop large queues of goal position
    }
    if (goalPosition < kSoftLowerLimit)
    {

        goalPosition = kSoftLowerLimit; //stop large queues of goal position

    }

    ElevatorJoystickbuilder << "GoalPosition: ";
    ElevatorJoystickbuilder << goalPosition;
    SmartDashboard::PutString("DB/String 0", ElevatorJoystickbuilder.str());
    ElevatorJoystickbuilder2 << "position: ";
    ElevatorJoystickbuilder2 << (m_encoder->Get() / TicksPerInch);
    SmartDashboard::PutString("DB/String 1", ElevatorJoystickbuilder2.str());

    setElevatorGoalPosition(goalPosition, speedMult);

}


void Elevator::setElevatorGoalPosition(float position, float SpeedMultiplier)
{
    m_speedMultiplier = SpeedMultiplier;
    m_elevatorControl->SetSetpoint(position);
}

/*
 * This function is responsible for enforcing limit switches, the brake and provides the call back for the PIDController
 * when it wants to move the motors.
 */
void Elevator::PIDWrite(float desiredSpeed)
{
    bool atUpperLimit = m_upperLimit->Get();
    bool atLowerLimit = m_lowerLimit->Get();
    float actualSpeed = desiredSpeed * m_speedMultiplier;

  //  std::ostringstream out;
  //  out.precision(2);
    //out << "EV: " << desiredSpeed << " " << m_speedMultiplier;
  //  SmartDashboard::PutString("DB/String 8", out.str());

    if(actualSpeed >= -0.1 && actualSpeed <= 0.1)
    {
        actualSpeed = 0.0;
    }
    if (atUpperLimit && (desiredSpeed > 0.0))
    {
        actualSpeed = 0.0; // don't move past upper limit
    }
    if (atLowerLimit && (desiredSpeed < 0.0))
    {
        actualSpeed = 0.0; // don't move past lower limit
    }

  //  std::ostringstream out2;
  //  out2.precision(2);
  //  out2 << "ACT: " << actualSpeed;
  //  SmartDashboard::PutString("DB/String 9", out2.str());

    //turn off the brake before moving
    if(actualSpeed != 0.0)
    {
        m_brake->Set(m_brake->kOff);
    }
    else
    {
        m_brake->Set(m_brake->kForward);

    }

    // set the motor speed

        m_motor1->Set(-actualSpeed);
        m_motor2->Set(-actualSpeed);
}



Elevator::~Elevator(){}

