#include "Configuration.h"
#include "WPILib.h"
#include <string>

using std::string;

enum configTypes { configFloat, configInt, configString, endOfList };

struct ourConfiguration_t {
    const char * key;
    const char * humanName;
    enum configTypes type;
    const char * defaultValue;
};

/*
 * This structure defines what parameters we save on the roborio flash disk
 *
 * The first column, that appears in the file, must not contain spaces or symbols
 *
 * The second column, the human readable name, appears in driver station
 *
 * The third column is the type
 *
 * The fourth column is the default value (if not found in the roborio config upon starting)
 */
struct ourConfiguration_t ourConfiguration [] =
{
        {"foo", "this is foo", configFloat, "12.34"},
        {"bar", "this is bar", configString, "this is string bar"},
        //Add new entries above here
        {"0", "0", endOfList, "0"}//Keep this here ALWAYS!
};

Configuration * Configuration::_instance = 0; // pointer to our only instance of the Configuration class

Configuration::Configuration()
{

}

/*
 * This function creates the Singleton instance, if not already done
 */
void Configuration::configurationInit()
{
    if (_instance != 0)
    {
        return; // Don't do anything, because the instance already exists
    }
    _instance = new Configuration();
    _instance->ReadValues();
    _instance->Save();
    Wait(0.25);
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

/*
 * Read the values and create defaults, if they do not already exist
 */
void Configuration::ReadValues()
{
    int currentConfigEntry = 0;
    while(ourConfiguration[currentConfigEntry].type != endOfList)
    {
        if (ContainsKey(ourConfiguration[currentConfigEntry].key)){
            printf("Already have key %s\n", ourConfiguration[currentConfigEntry].key);
            currentConfigEntry++;
            continue; //Already have value from file so we're all set, go to the next part.
        }

        printf("%s\n", ourConfiguration[currentConfigEntry].humanName);
        if(ourConfiguration[currentConfigEntry].type == configFloat)
        {
            printf("Found a float %s\n", ourConfiguration[currentConfigEntry].humanName);
            float valueToSave = std::stof("123.456");
            PutFloat(ourConfiguration[currentConfigEntry].key, valueToSave);
        }
        else if(ourConfiguration[currentConfigEntry].type == configInt)
        {
            printf("Found an int %s\n", ourConfiguration[currentConfigEntry].humanName);
        }
        else if(ourConfiguration[currentConfigEntry].type == configString)
        {
            printf("Found a string %s\n", ourConfiguration[currentConfigEntry].humanName);
        }
        currentConfigEntry++;
    }
    fflush(stdout);
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
