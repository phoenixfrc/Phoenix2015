/*
 * driveStabilize.h
 *
 *  Created on: Feb 3, 2015
 *      Author: Ray
 */

#include "WPILib.h"

#ifndef SRC_DRIVESTABILIZE_H_
#define SRC_DRIVESTABILIZE_H_


class DriveStabilize {
public:
    DriveStabilize(Gyro * gyro, float referenceAngle, float scale);

    void SetReferenceAngle(float newAngle);

    float GetCorrectionAngle();

    ~DriveStabilize();
private:
    Gyro * m_gyro;
    float m_referenceAngle;
    float m_scale;
};


#endif /* SRC_DRIVESTABILIZE_H_ */
