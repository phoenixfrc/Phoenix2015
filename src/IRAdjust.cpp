/*
 * IRAdjust.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: Ray
 */
#include "IRAdjust.h"
#include <Math.h>

IRAdjust::IRAdjust(AnalogInput* IRLeftInner, AnalogInput* IRLeftOuter, AnalogInput* IRRightInner, AnalogInput* IRRightOuter):
    m_ThresholdForward(0),//tbd
    m_IRLeftInner(IRLeftInner),
    m_IRLeftOuter(IRLeftOuter),
    m_IRRightInner(IRRightInner),
    m_IRRightOuter(IRRightOuter)
{

}


bool IRAdjust::IsOnTote(){
    int16_t LI = m_IRLeftInner->GetValue();
    int16_t LO = m_IRLeftOuter->GetValue();
    int16_t RI = m_IRRightInner->GetValue();
    int16_t RO = m_IRRightOuter->GetValue();

    bool turned = fabs(LI-RI) > 500;//Are we turned to far?

    bool isNear = (LI+RI)/2 < m_ThresholdForward;

    return !turned && isNear;
}

void IRAdjust::GrabTote(){

    bool readyToLift = false;

    while (!readyToLift) {
        readyToLift = IsOnTote();
    }
}


IRAdjust::~IRAdjust(){}
