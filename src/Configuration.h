#include "WPILib.h"

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_

class Configuration : public Preferences
{
private:
    Configuration();
    static Configuration *_instance;
    ~Configuration();


public:
    static void configurationInit();
    static Configuration *getInstance();

};

#endif /* SRC_CONFIGURATION_H_ */
