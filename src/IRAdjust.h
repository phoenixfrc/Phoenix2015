/*
 * IRAdjust.h
 *
 *  Created on: Mar 6, 2015
 *      Author: Ray
 */


#ifndef IRADJUST_H_
#define IRADJUST_H_

#include "WPILib.h"
#include <sstream>

class IRAdjust {
public:
    IRAdjust(AnalogInput* IRLeftInner, AnalogInput* IRLeftOuter, AnalogInput* IRRightInner, AnalogInput* IRRightOuter, RobotDrive* drive);

    void GrabTote();
    bool IsOnTote();

    ~IRAdjust();
private:

    int16_t m_ThresholdForward;

    AnalogInput* m_IRLeftInner;
    AnalogInput* m_IRLeftOuter;
    AnalogInput* m_IRRightInner;
    AnalogInput* m_IRRightOuter;

    RobotDrive* m_drive;
};




#endif /* IRADJUST_H_ */
