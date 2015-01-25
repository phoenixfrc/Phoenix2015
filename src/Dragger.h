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
    private:
        Talon motor;

    public:
        Dragger();

        void operateDragger(Joystick * button);

        ~Dragger();

};




#endif /* SRC_DRAGGER_H_ */
