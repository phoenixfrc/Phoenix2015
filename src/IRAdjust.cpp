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

    int16_t near = LI > RI ? LI : RI;

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

double IRAdjust::GetMove(double extraMove){
    //std::ostringstream builder1, builder2, builder3;

    int16_t LI = m_IRLeftInner->GetAverageValue();
    int16_t RI = m_IRRightInner->GetAverageValue();

    double vLI = (double) (LI) * 5 / 4096;
    double dLI = -4.88*vLI*vLI*vLI + 22.3*vLI*vLI - 35.43*vLI + 23.0;
    double vRI = (double) (RI) * 5 / 4096;
    double dRI = -4.88*vRI*vRI*vRI + 22.3*vRI*vRI - 35.43*vRI + 23.0;

    //builder1 << "Left: " << dLI;
    //builder2 << "Right: " << dRI;
    //SmartDashboard::PutString("DB/String 2", builder1.str());
    //SmartDashboard::PutString("DB/String 3", builder2.str());


    double moveDist = 0;

    double minDist = 3.0;
    double maxDist = 10.0;

    if (dRI > maxDist && dLI > maxDist){
        return 6.0;//or 2.0?
    } else {
        dRI = dRI < minDist ? minDist : dRI;//if it's giving a small reading change to the min dist
        dLI = dLI < minDist ? minDist : dLI;//if it's giving a small reading change to the min dist

        dRI = dRI < maxDist ? dRI : dLI;//if farther than the max dist assume same as other sensor
        dLI = dLI < maxDist ? dLI : dRI;//if farther than the max dist assume same as other sensor
    }


    moveDist = (dLI+dRI)/2.0;//take the average of the two sensors.

    moveDist -= minDist;//remove the extra from the min dist (lip on the robot base)
    moveDist += extraMove;//add in the extra movement

    //builder3 << "Move: " << moveDist;5
    //SmartDashboard::PutString("DB/String 4", builder3.str());
    //SmartDashboard::PutString("DB/String 9", "+3\" to Robot ");

    return moveDist;
}


IRAdjust::~IRAdjust(){}
