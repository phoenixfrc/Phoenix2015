
/*
 * Elevator.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "WPILib.h"
#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_

class Elevator  : public PIDOutput
{

    float MotorSpeed = 1.0;
    float HomeSpeed = 0.25;
    int Ticks = 2048;
    bool m_rbWasPressed = false;
    bool m_rtWasPressed = false;

    double Range = 1; // range on either side of goalDistance
    enum homingStates
    {
        lookingForLowerLimit,
        goingUpToHome,
        homingComplete
    } m_homeState;

    // initialized at class constructions then constant
    Talon* m_motor1;
    Talon* m_motor2;
    DigitalInput* m_lowerLimit;
    DigitalInput* m_upperLimit;
    DigitalInput* m_homeSwitch;
    Encoder* m_encoder;
    Joystick* m_gamePad;
    Relay* m_brake;
    PIDController* m_elevatorControl;


    void find_home();
    void controlElevator();
    void moveElevator();

public:
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
    #define kElevatorHome         0
    #define kElevatorHook1Ready   0
    #define kElevatorHook1Lifted  kElevatorHook1Ready + 4
    #define kElevatorHook2Ready   kElevatorHook1Ready + 14.5
    #define kElevatorHook2Lifted  kElevatorHook2Ready + 4
    #define kElevatorHook3Ready   kElevatorHook2Ready + 14.5
    #define kElevatorHook3Lifted  kElevatorHook3Ready + 4
    #define kElevatorHook4Ready   kElevatorHook3Ready + 14.5
    #define kElevatorHook4Lifted  kElevatorHook4Ready + 4

    void setElevatorGoalPosition(float position); // use consts above

    ~Elevator();

    void PIDWrite(float output);
};





#endif /* SRC_ELEVATOR_H_ */

