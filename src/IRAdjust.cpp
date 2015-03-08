/*
 * IRAdjust.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: Ray
 */
#include "IRAdjust.h"
#include <math.h>

IRAdjust::IRAdjust(AnalogInput* IRLeftInner, AnalogInput* IRLeftOuter, AnalogInput* IRRightInner, AnalogInput* IRRightOuter, RobotDrive* drive):
    m_ThresholdForward(768),//tbd
    m_IRLeftInner(IRLeftInner),
    //m_IRLeftOuter(IRLeftOuter),
    m_IRRightInner(IRRightInner),
    //m_IRRightOuter(IRRightOuter),
    m_drive(drive)
{

}


bool IRAdjust::IsOnTote(){
    int16_t LI = m_IRLeftInner->GetValue();
    //int16_t LO = m_IRLeftOuter->GetValue();
    int16_t RI = m_IRRightInner->GetValue();
    //int16_t RO = m_IRRightOuter->GetValue();

    int16_t turn = abs(LI-RI);//Are we turned to far?

    int16_t near = LI < RI ? LI : RI;//(LI+RI)/2;

    static int count = 0;
    bool ready = (turn < 640) && (near < 1296);

    if (count++ >= 100) {
        std::ostringstream builder;
        builder << "turn: " << turn << ", dist: " << near;
        SmartDashboard::PutString("DB/String 9", builder.str());

        bool ready = (turn < 640) && (near > 1296);
    	SmartDashboard::PutString("DB/String 8", ready ? "Ready" : "Not Ready");
    	count = 0;
    }

    return ready;
}

void IRAdjust::GrabTote(){
    IsOnTote();
}

double IRAdjust::InchesForward(){
    int16_t LI = m_IRLeftInner->GetValue();
    int16_t RI = m_IRRightInner->GetValue();

    int16_t x = LI < RI ? LI : RI;

    double v = (double) x * 5 / 4096;

    double dist = -4.88*v*v*v + 22.3*v*v - 35.43*v + 23.0;

    return dist;
}


IRAdjust::~IRAdjust(){}
