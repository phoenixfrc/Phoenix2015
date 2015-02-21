
#include "Elevator.h"
#include "Constants.h"
#include <sstream>
#include <stdio.h>



Elevator::Elevator(
        Talon* motor1,
        Talon* motor2,
        DigitalInput* lowerLimit,
        DigitalInput* upperLimit,
        Encoder* encoder,
        Joystick* gamePad,
        Team2342Joystick* joystick,
        Relay* ElevatorBrake):

        m_rbWasPressed(false),
        m_rtWasPressed(false),
        m_motor1(motor1),
        m_motor2(motor2),
        m_lowerLimit(lowerLimit),
        m_upperLimit(upperLimit),
        m_encoder(encoder),
        m_gamePad(gamePad),
        m_joystick(joystick),
        m_brake(ElevatorBrake),
        m_homeState(lookingForLowerLimit)
{
    printf("in elevator constructor...\n");
    m_homeState = lookingForLowerLimit;
    m_oldEncoder = 0;
    m_speedMultiplier = kNormalMultiplier;
    m_encoder->SetDistancePerPulse(1 / TicksPerInch);
    m_elevatorControl = new PIDController(0.14, 0.019, 0.00, encoder, this);
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
        if(m_lowerLimit->Get())
        {
            m_homeState = homingComplete;
            m_encoder->Reset();
            setElevatorGoalPosition(0.0);//, 0.75
            m_elevatorControl->Enable();
            m_currentSetPoint = 0;
            m_desiredSetPoint = 0.0;//Changed from 5.0f to 0.0


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
    bool rbPressed = (m_gamePad->GetRawButton(6) || m_joystick->GetRawButton(1));
    bool rtPressed = (m_gamePad->GetRawButton(8) || m_joystick->GetRawButton(2));
    int POV = m_joystick->GetPOV();



    //joystick
    double joystick = -m_gamePad->GetY(); // right Joystick, negative because up is negative

    float goalPosition = m_desiredSetPoint;


    // button computing
    if(rbPressed && !m_rbWasPressed)
    {
        speedMult = kShortLiftMultiplier;
        goalPosition += kButtonLift;
        m_rbWasPressed = true;
    }
    else if(!rbPressed && m_rbWasPressed)
    {
        m_rbWasPressed = false;
    }

    if(rtPressed && !m_rtWasPressed)
    {
        speedMult = kShortLiftMultiplier;
        goalPosition -= kButtonLift;
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
        goalPosition += (joystick / 4);
    }

    if(POV == 0 || POV == 45 || POV == 315)
    {
        speedMult = kNormalMultiplier;
        goalPosition += (0.15);
    }

    if(POV == 180 || POV == 225 || POV == 135)
    {
        speedMult = kNormalMultiplier;
        goalPosition -= (0.15);
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
    if(yPressed)
    {
        speedMult = kNormalMultiplier;
        goalPosition = kElevatorHook3Ready;
    }
    if(xPressed)
    {
        speedMult = kNormalMultiplier;
        goalPosition = kElevatorHook4Ready;
    }



    ElevatorJoystickbuilder << "GoalPosition: ";
    ElevatorJoystickbuilder << goalPosition;
    SmartDashboard::PutString("DB/String 0", ElevatorJoystickbuilder.str());
    ElevatorJoystickbuilder2 << "position: ";
    ElevatorJoystickbuilder2 << (m_encoder->Get() / TicksPerInch);
    SmartDashboard::PutString("DB/String 1", ElevatorJoystickbuilder2.str());

    setElevatorGoalPosition(goalPosition);//used to have "speedMult" as a second parameter (it was causing build errors)

}


void Elevator::setElevatorGoalPosition(float position)
{
    if (position > kSoftUpperLimit)
    {

        position = kSoftUpperLimit; //Stop large queues of goal position
    }
    if (position < kSoftLowerLimit)
    {

        position = kSoftLowerLimit; //stop large queues of goal position

    }


    //m_elevatorControl->SetSetpoint(position);
    m_desiredSetPoint = position;
    updateProfile();

}
void Elevator::updateProfile()
{
    m_elevatorControl->SetSetpoint(accelCurve());
}


float Elevator::getElevatorGoalPosition()
{
    return  m_elevatorControl->GetSetpoint();
}

/*
 * This function is responsible for enforcing limit switches, the brake and provides the call back for the PIDController
 * when it wants to move the motors.
 */
void Elevator::PIDWrite(float desiredSpeed)
{
    bool atUpperLimit = m_upperLimit->Get();
    bool atLowerLimit = m_lowerLimit->Get();

    //calculateSpeedMutiplier();

    float actualSpeed = desiredSpeed; //* m_speedMultiplier;

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
    else if (m_brake->Get() == m_brake->kOff)
    {
        m_brake->Set(m_brake->kForward);
    }

    // set the motor speed

        m_motor1->Set(-actualSpeed);
        m_motor2->Set(-actualSpeed);
}

void Elevator::calculateSpeedMutiplier()
{
    int deltaEncoder = abs(int(m_oldEncoder - m_encoder->Get()));

    if((deltaEncoder > GoalDeltaEncoder) && m_speedMultiplier > 0.5)
    {
        m_speedMultiplier -= 0.01;
    }
    else if((deltaEncoder < GoalDeltaEncoder) && (m_speedMultiplier < 0.75))
    {
        m_speedMultiplier += 0.01;
    }
    m_oldEncoder = m_encoder->Get();

}

bool Elevator::elevatorIsDeccelerating()
{
    // this estimate with a constant deceleration if it needs to slow down.
    return (fabs(m_desiredSetPoint - m_currentSetPoint) < ((m_currentVelocity * m_currentVelocity) / (2.0f * Accel)));
}


/*
 * computes the movement profile based on current and desired speeds and volcities
 * may result in a triangle or a trapizoidal pattern.
 */
float Elevator::accelCurve()
{
    static int count = 0;

    //if we are close enough
    if(((m_currentSetPoint - EndPointTolorance) < m_desiredSetPoint) && ((m_currentSetPoint + EndPointTolorance) > m_desiredSetPoint))
    {
        m_currentVelocity = 0.0f;
        m_currentSetPoint = m_desiredSetPoint;
        return m_currentSetPoint;
    }

    bool isDeccel = elevatorIsDeccelerating(); // slowing down in either direction????

    bool goingUp = (m_currentSetPoint < m_desiredSetPoint); // are we going up????
    float acceleration = 0.0f;

    //accelerating in either direction.
    if(goingUp && m_currentVelocity < MaxVelocity)
    {
        acceleration = Accel;
    }
    if(!(goingUp) && m_currentVelocity > -MaxVelocity)
    {
        acceleration = -Accel;
    }

    //declerating in either direction
    if(isDeccel)
    {
        acceleration = Accel;
        if(goingUp)
        {
            acceleration = -Accel;
        }

    }

    // update up expected velocity and position
    m_currentVelocity += (acceleration / 200); //inches per second
    m_currentSetPoint += (m_currentVelocity / 200); // called 200 times per second

    printf("Count:%d, Decel:%c, Dpos:%8.3f Cpos:%12.9f Vel:%8.3f Acc:%8.3f\n",
            count, isDeccel?'t':'f', m_desiredSetPoint, m_currentSetPoint, m_currentVelocity, acceleration);
    fflush(stdout);
    count++;
    return m_currentSetPoint;


}



Elevator::~Elevator(){}

