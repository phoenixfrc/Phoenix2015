
/*
 * Elevator.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Developer
 */
#include "WPILib.h"
#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_
class Elevator {

    float MotorSpeed = 0.5;
    float HomeSpeed = 0.1;
    int Ticks = 2048;

    int Heights[4] = {0, 13, 26, 39};

    #define kElevatorHome         0
    #define kElevatorHook1Ready   0
    #define kElevatorHook1Lifted  kElevatorHook1Ready + 4
    #define kElevatorHook2Ready   kElevatorHook1Ready + 14.5
    #define kElevatorHook2Lifted  kElevatorHook2Ready + 4
    #define kElevatorHook3Ready   kElevatorHook2Ready + 14.5
    #define kElevatorHook3Lifted  kElevatorHook3Ready + 4
    #define kElevatorHook4Ready   kElevatorHook3Ready + 14.5
    #define kElevatorHook4Lifted  kElevatorHook4Ready + 4


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



    double m_goalPosition;
    double m_position; // distance from home (in)


public:
	Elevator(Talon* motor1,
	        Talon* motor2,
	        DigitalInput* lowerLimit,
	        DigitalInput* upperLimit,
	        DigitalInput* homeSwitch,
	        Encoder* encoder,
	        Joystick* gamePad,
	        Relay* ElevatorBrake);
	void operateElevator();
	void find_home();
	void controlElevator();
	void moveElevator();
	void moveMotors(double speed);
	~Elevator();

};





#endif /* SRC_ELEVATOR_H_ */

