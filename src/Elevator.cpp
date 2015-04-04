
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
    m_encoder->SetDistancePerPulse(1 / TicksPerInch);
    //m_elevatorControl = new PIDController(0.28, 0.038, 0.00, encoder, this);//This worked for new code
    m_elevatorControl = new PIDController(0.21, 0.0095, 0.00, encoder, this);//This worked for old code
    //m_elevatorControl = new PIDController(0.28, 0.0095, 0.00, encoder, this);//For testing use in comp
    m_currentSetPoint = 0;
    m_currentVelocity = 0;
    m_desiredSetPoint = 0;
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
    return((currentPosition < (position + 1.0)) && (currentPosition > (position - 1.0)));
}

float Elevator::elevatorPosition()
{
    return (m_encoder->Get() / TicksPerInch);
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
            setElevatorGoalPosition(0.0);
            m_elevatorControl->Enable();
            m_currentSetPoint = 0;
            m_desiredSetPoint = 0.0f;


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
    bool rbPressed = (m_gamePad->GetRawButton(6) || m_joystick->GetRawButton(1));
    bool rtPressed = (m_gamePad->GetRawButton(8) || m_joystick->GetRawButton(2));

    bool lbPressed = m_gamePad->GetRawButton(7);

    int POV = m_joystick->GetPOV();



    //joystick
    double joystick = -m_gamePad->GetY(); // right Joystick, negative because up is negative

    float goalPosition = m_desiredSetPoint;


    // button computing
    if(rbPressed && !m_rbWasPressed)
    {

        goalPosition += kButtonLift;
        m_rbWasPressed = true;
    }
    else if(!rbPressed && m_rbWasPressed)
    {
        m_rbWasPressed = false;
    }

    if(rtPressed && !m_rtWasPressed)
    {

        goalPosition -= kButtonLift;
        m_rtWasPressed = true;
    }
    else if(!rtPressed && m_rtWasPressed)
    {
        m_rtWasPressed = false;
    }

    if(lbPressed && !m_lbWasPressed)
    {

        goalPosition = kElevatorHook1Lifted;
        m_lbWasPressed = true;
    }
    else if(!lbPressed && m_lbWasPressed)
    {
        m_lbWasPressed = false;
    }


    //Joystick computing
    // TODO limit offset from joystick
    if(!(joystick > -0.05 && joystick < 0.05))
    {

        goalPosition += (joystick / 5);
    }
    else if(POV == 0 || POV == 45 || POV == 315)
    {

        goalPosition += (0.2);
    }
    else if(POV == 180 || POV == 225 || POV == 135)
    {

        goalPosition -= (0.2);
    }

    if(aPressed)
    {

        goalPosition = kElevatorHook1Ready;
    }
    if(bPressed)
    {

        goalPosition = kElevatorHook2Ready;
    }
    if(yPressed)
    {

        goalPosition = kElevatorHook3Ready;
    }
    if(xPressed)
    {

        goalPosition = kElevatorHook4Ready;
    }


    /*
    ElevatorJoystickbuilder << "GoalPosition: ";
    ElevatorJoystickbuilder << goalPosition;
    SmartDashboard::PutString("DB/String 0", ElevatorJoystickbuilder.str());
    ElevatorJoystickbuilder2 << "position: ";
    ElevatorJoystickbuilder2 << (m_encoder->Get() / TicksPerInch);
    SmartDashboard::PutString("DB/String 1", ElevatorJoystickbuilder2.str());
    */
    setElevatorGoalPosition(goalPosition);

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



    float actualSpeed = desiredSpeed;

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
    if (m_currentVelocity == 0.0f && !isDeccel){
    	if(goingUp){
    		m_currentVelocity = 5.0f;
    	}else{
    		m_currentVelocity = -5.0f;
    	}

    }
    m_currentVelocity += (acceleration / 200); //inches per second
    m_currentSetPoint += (m_currentVelocity / 200); // called 200 times per second

    printf("Count:%d, Decel:%c, Dpos:%8.3f Cpos:%12.9f Vel:%8.3f Acc:%8.3f\n",
           count, isDeccel?'t':'f', m_desiredSetPoint, m_currentSetPoint, m_currentVelocity, acceleration);
    fflush(stdout);
    count++;
    return m_currentSetPoint;


}


void Elevator::ElevatorInit()
{
    m_homeState = lookingForLowerLimit;
}

void Elevator::ElevatorEnd()
{
    m_elevatorControl->Disable();
}

Elevator::~Elevator(){}



