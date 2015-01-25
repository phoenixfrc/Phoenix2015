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

    // constants
    float MotorSpeed = 0.5;
    float HomeSpeed = 0.1;
    int Ticks = 200;

    int Heights[4] = {0, 13, 26, 39};

    double Range = 0.25; // range on either side of goalDistance
    enum homingStates
    {
        lookingForLowerLimit,
        goingUpToHome,
        homingComplete
    } homeState;

    // initialized at class constructions then constant
    DigitalInput* m_lowerLimit;
    DigitalInput* m_upperLimit;
    DigitalInput* m_homeSwitch;
    Talon* m_motor1;
    Talon* m_motor2;
    Encoder* m_encoder;
    Joystick* m_gamePad;


    double m_goalDistance = 0;
    double m_distance = 0; // distance form home (in)


public:
	Elevator(Talon* motor1,
	        Talon* motor2,
	        DigitalInput* lowerLimit,
	        DigitalInput* upperLimit,
	        DigitalInput* homeSwitch,
	        Encoder* encoder,
	        Joystick* gamePad);
	void operateElevator();
	void find_home();
	void controlElevator();
	void moveElevator();
	void moveMotors(double speed);
	~Elevator();

};





#endif /* SRC_ELEVATOR_H_ */
