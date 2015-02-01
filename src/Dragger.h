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
        Dragger();
        void operateDragger(Joystick * button, DigitalInput * limitSwitchDown, DigitalInput * limitSwitchUp, Talon * motor);
        ~Dragger();

};




#endif /* SRC_DRAGGER_H_ */
