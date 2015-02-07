#include "Configuration.h"
#include "WPILib.h"
#include <string>

using std::string;

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
    string intasstring = std::to_string(value);
    PutString(key, intasstring.c_str());
}

int Configuration::GetConfigInt (const char * key, int defaultValue)
{
    int theintvalue = 0;

    if (ContainsKey(key))
    {
        std::string intasstring = GetString(key);
        theintvalue = stoi(intasstring);
    }
    else
    {
        theintvalue = defaultValue;
    }
    return theintvalue;
}

Configuration::~Configuration()
{

}
