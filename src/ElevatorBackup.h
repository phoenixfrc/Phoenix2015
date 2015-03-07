/*
 * ElevatorBackup.h
 *
 * The ElevatorBackup class will take over from the Elevator class in the event
 * of an encoder failure.  It will track encoder values per tick, and if after a certain
 * timeframe (probably about 0.5 seconds), there is no change, then the ElevatorBackup
 * class will take over.
 *
 *  Created on: Mar 2, 2015
 *      Author: Brin
 */

#ifndef ELEVATORBACKUP_H_
#define ELEVATORBACKUP_H_

class ElevatorBackup
{
public:
    void motionTester(bool hayMovimiento); // This function will test for the motion of the encoder

private:
};




#endif /* ELEVATORBACKUP_H_ */
