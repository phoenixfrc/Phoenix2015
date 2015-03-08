/*
 * IRAdjust.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: Ray
 */
#include "IRAdjust.h"
#include <math.h>

IRAdjust::IRAdjust(AnalogInput* IRLeftInner, AnalogInput* IRLeftOuter, AnalogInput* IRRightInner, AnalogInput* IRRightOuter, RobotDrive* drive):
    m_ThresholdForward(0),//tbd
    m_IRLeftInner(IRLeftInner),
    m_IRLeftOuter(IRLeftOuter),
    m_IRRightInner(IRRightInner),
    m_IRRightOuter(IRRightOuter),
    m_drive(drive)
{

}


bool IRAdjust::IsOnTote(){
    int16_t LI = m_IRLeftInner->GetValue();
    int16_t LO = m_IRLeftOuter->GetValue();
    int16_t RI = m_IRRightInner->GetValue();
    int16_t RO = m_IRRightOuter->GetValue();

    int16_t turn = abs(LI-RI);//Are we turned to far?

    int16_t near = (LI+RI)/2;

    static int count =0;
    bool ready = (turn < 500) && (near < m_ThresholdForward);

    if (count++ >= 100) {

    	std::ostringstream builder;


    	builder << "turn: " << turn << "dist: " << near;

    	SmartDashboard::PutString("DB/String 9", builder.str());

    	SmartDashboard::PutString("DB/String 8", ready ? "Ready" : "Not Ready");
    	count = 0;
       }


    return ready;
}

void IRAdjust::GrabTote(){
    IsOnTote();
}


IRAdjust::~IRAdjust(){}
