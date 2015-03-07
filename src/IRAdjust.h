/*
 * IRAdjust.h
 *
 *  Created on: Mar 6, 2015
 *      Author: Ray
 */


#ifndef IRADJUST_H_
#define IRADJUST_H_

#include "WPILib.h"
#include "constants.h"

class IRAdjust {
public:
    IRAdjust(AnalogInput* IRLeftInner, AnalogInput* IRLeftOuter, AnalogInput* IRRightInner, AnalogInput* IRRightOuter);

    void GrabTote();
    bool IsOnTote();

    ~IRAdjust();
private:

    int16_t m_ThresholdForward;

    AnalogInput* m_IRLeftInner;
    AnalogInput* m_IRLeftOuter;
    AnalogInput* m_IRRightInner;
    AnalogInput* m_IRRightOuter;
};




#endif /* IRADJUST_H_ */
