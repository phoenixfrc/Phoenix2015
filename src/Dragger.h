/*
 * Dragger.h
 *
 *  Created on: Jan 15, 2015
 *      Author: Ray
 */

#ifndef SRC_DRAGGER_H_
#define SRC_DRAGGER_H_
#include "WPILib.h"
#define kDraggerReverseTime 1.5
#define kDraggerMotorDownSpeed 0.75
#define kDraggerMotorUpSpeed -0.25


class Dragger {
public:
    Dragger();

    void operateDragger(Joystick * button, DigitalInput * limitSwitchDown, Talon * motor);
    ~Dragger();


private:
    int m_timer;
    const float m_liftDuration;
    const float m_downSpeed;
    const float m_upSpeed;
    bool m_draggerDirection;
    enum draggerStates{defaultState, upState, loweringState, downState, liftingState};
    int m_mode;

};




#endif /* SRC_DRAGGER_H_ */
