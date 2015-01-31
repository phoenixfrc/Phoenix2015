
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
    /*
     * motor speeds are n < 0 for up, n > 0 for down
     */
    float MotorSpeed = -0.5;
    float HomeSpeed = -0.1;
    int Ticks = 2048;

    int Heights[4] = {0, 13, 26, 39};

    double Range = 100; // tick range on either side of goalTicks
    enum homingStates
    {
        lookingForLowerLimit,
        goingUpToHome,
        homingComplete
    } homeState;

    // initialized at class constructions then constant
    Talon* m_motor1;
    Talon* m_motor2;
    DigitalInput* m_lowerLimit;
    DigitalInput* m_upperLimit;
    DigitalInput* m_homeSwitch;
    Encoder* m_encoder;
    Joystick* m_gamePad;


    double m_goalTicks = 0;
    double m_ticks = 0; // distance from home (ticks)


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
	int toTicks(double distance);
	~Elevator();

};





#endif /* SRC_ELEVATOR_H_ */

