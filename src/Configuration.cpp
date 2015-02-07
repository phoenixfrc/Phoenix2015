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

Configuration::~Configuration()
{

}
