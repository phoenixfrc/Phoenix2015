/*
 * Dragger.h
 *
 *  Created on: Jan 15, 2015
 *      Author: Ray
 */

#ifndef SRC_DRAGGER_H_
#define SRC_DRAGGER_H_
#include "WPILib.h"


class Dragger {
public:
    Dragger(int liftTime, float liftSpeed);

    void operateDragger(Joystick * button, DigitalInput * limitSwitchDown, Talon * motor);
    ~Dragger();


private:
    int m_timer;
    const int m_liftDuration;
    const float m_speed;


};




#endif /* SRC_DRAGGER_H_ */
