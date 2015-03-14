
/*
 * Elevator.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "WPILib.h"
#include "Team2342Joystick.h"
#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_

static const float MotorSpeed = 1.0;
static const float HomeSpeed = 0.40;
static const int Ticks = 384;
static const float TicksPerInch = Ticks / 8.17;
static const int GoalDeltaEncoder = 29;
static const float Accel = 50.0f; //inches per second
static const float MaxVelocity = 50.0f; // Accel should allways be double maxVelocity for good performance
static const float EndPointTolorance = 0.1f;

class Elevator  : public PIDOutput
{

    bool m_rbWasPressed;
    bool m_rtWasPressed;
    int m_oldEncoder;
    float m_desiredSetPoint;
    float m_currentSetPoint;
    float m_currentVelocity;

    // initialized at class constructions then constant
    Talon* m_motor1;
    Talon* m_motor2;
    DigitalInput* m_lowerLimit;
    DigitalInput* m_upperLimit;
    Encoder* m_encoder;
    Joystick* m_gamePad;
    Team2342Joystick* m_joystick;
    Relay* m_brake;



    void find_home();
    void controlElevator();
    void moveElevator();

    bool elevatorIsDeccelerating();
    float accelCurve();



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
            Encoder* encoder,
            Joystick* gamePad,
            Team2342Joystick* joytick,
            Relay* ElevatorBrake);
    //Ecpected usage in teleop loop while(!elevatorIsHomed()) {operateElevator();}
    // after that call setElevatorGoalPosition using the const below.

    void operateElevator(); // for use in teleop
    bool elevatorIsHomed();
    bool elevatorIsAt(float position);
    float elevatorPosition();
    void updateProfile();




    // for use in setElevatorGoalPosition call
    #define kSoftLowerLimit       (0.0)
    #define kSoftUpperLimit       (64)
    #define kButtonLift           (4)
    #define kLiftDelta            (6)
    #define kToteDelta            (18)
    #define kElevatorHome         (kSoftLowerLimit)
    // 3
    #define kElevatorHook1Ready   (3)
    #define kElevatorHook1Lifted  (kElevatorHook1Ready + kLiftDelta)
    //22
    #define kElevatorHook2Ready   (kElevatorHook1Ready + kToteDelta)
    #define kElevatorHook2Lifted  (kElevatorHook2Ready + kLiftDelta)
    //40
    #define kElevatorHook3Ready   (kElevatorHook2Ready + kToteDelta)
    #define kElevatorHook3Lifted  (kElevatorHook3Ready + kLiftDelta)
    //58
    #define kElevatorHook4Ready   (kElevatorHook3Ready + kToteDelta)
    #define kElevatorHook4Lifted  (kElevatorHook4Ready + kLiftDelta)

    void setElevatorGoalPosition(float position); // use consts above
    float getElevatorGoalPosition();

    ~Elevator();

    void PIDWrite(float output);
    void ElevatorInit();
    void ElevatorEnd();

};





#endif /* SRC_ELEVATOR_H_ */

