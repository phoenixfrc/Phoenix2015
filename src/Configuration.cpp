#include "Configuration.h"
#include "WPILib.h"

Configuration * Configuration::_instance = 0; // pointer to our only instance of the Configuration class

Configuration::Configuration()
{

}

void Configuration::configurationInit()
{
    if (_instance != 0)
    {
        return;
    }
    _instance = new Configuration();
}

/*
 * Get the only copy of me (Configuration object) that should ever exist
 */
Configuration * Configuration::getInstance()
{
    if (_instance == 0)
    {
        configurationInit();
    }
    return _instance;
}

void Configuration::PutConfigInt(const char * key, int value)
{

}

int Configuration::GetConfigInt (const char * key, int defaultValue)
{
return 0;
}

Configuration::~Configuration()
{

}