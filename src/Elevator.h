
/*
 * Elevator.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "WPILib.h"
#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_

static const float MAX_MOTOR_SPEED = .5;
static const float HomeSpeed = 0.25;
//static const int Ticks = 2048; //old robot
static const int Ticks = 384; //ticks per revolution on new robot
static const float TicksPerInch = Ticks / 8.17;


class Elevator  : public PIDOutput
{

    bool m_rbWasPressed;
    bool m_rtWasPressed;

    // initialized at class constructions then constant
    Talon* m_motor1;
    Talon* m_motor2;
    DigitalInput* m_lowerLimit;
    DigitalInput* m_upperLimit;
    DigitalInput* m_homeSwitch;
    Encoder* m_encoder;
    Joystick* m_gamePad;
    Relay* m_brake;



    void find_home();
    void controlElevator();
    void moveElevator();

public:
    enum homingStates
    {
        lookingForLowerLimit,
        goingUpToHome,
        homingComplete
    } m_homeState;

    PIDController* m_elevatorControl;
    Elevator(Talon* motor1,
            Talon* motor2,
            DigitalInput* lowerLimit,
            DigitalInput* upperLimit,
            DigitalInput* homeSwitch,
            Encoder* encoder,
            Joystick* gamePad,
            Relay* ElevatorBrake);
    //Ecpected usage in teleop loop while(!elevatorIsHomed()) {operateElevator();}
    // after that call setElevatorGoalPosition using the const below.

    void operateElevator(); // for use in teleop
    bool elevatorIsHomed();
    bool elevatorIsAt(float position);



    // for use in setElevatorGoalPosition call
    #define kLiftDelta            (8)
    #define kToteDelta            (14.5)
    #define kElevatorHome         (0)
    #define kElevatorHook1Ready   (0)
    #define kElevatorHook1Lifted  (kElevatorHook1Ready + kLiftDelta)
    #define kElevatorHook2Ready   (kElevatorHook1Ready + kToteDelta)
    #define kElevatorHook2Lifted  (kElevatorHook2Ready + kLiftDelta)
    #define kElevatorHook3Ready   (kElevatorHook2Ready + kToteDelta)
    #define kElevatorHook3Lifted  (kElevatorHook3Ready + kLiftDelta)
    #define kElevatorHook4Ready   (kElevatorHook3Ready + kToteDelta)
    #define kElevatorHook4Lifted  (kElevatorHook4Ready + kLiftDelta)

    void setElevatorGoalPosition(float position); // use consts above
    float getElevatorGoalPosition();


    ~Elevator();

    void PIDWrite(float output);
};





#endif /* SRC_ELEVATOR_H_ */

