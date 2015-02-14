#include "WPILib.h"

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_

class Configuration : public Preferences
{
private:
    Configuration();
    static Configuration *_instance;
    ~Configuration();
    void ReadValues();


public:
    static void configurationInit();
    static Configuration *getInstance();
    void PutConfigInt(const char * key, int value);
    int GetConfigInt (const char * key, int defaultValue = 0);
};

#endif /* SRC_CONFIGURATION_H_ */
