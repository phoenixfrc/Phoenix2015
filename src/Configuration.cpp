#include "Configuration.h"
#include "WPILib.h"
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>

using std::string;

enum configTypes { configFloat, configInt, configString, endOfList };

struct ourConfiguration_t {
    const char * key;
    const char * humanName;
    enum configTypes type;
    const char * defaultValue;
    float floatValue;
    int intValue;
    char * stringValue;
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
static struct ourConfiguration_t ourConfiguration [] =
{
        {"b", "this is b", configFloat, "12.34"},
        {"second", "this is second float", configFloat, "222.34"},
        {"third", "this is third", configFloat, "333.34"},
        {"bar", "this is bar", configString, "this is string bar"},
        {"teamNumber", "team number", configInt, "2342"},
        //Add new entries above here
        {"0", "0", endOfList, "0"}//Keep this here ALWAYS!
};

Configuration * Configuration::_configInstance = 0; // pointer to our only instance of the Configuration class

Configuration::Configuration()
{

}

/*
 * This function creates the Singleton instance, if not already done
 */
void Configuration::configurationInit()
{
    if (_configInstance != 0)
    {
        return; // Don't do anything, because the instance already exists
    }
    _configInstance = new Configuration();
   // _configInstance->ReadValues();
    //_configInstance->Save();
    //Wait(0.25);
}

/*
 * Get the only copy of me (Configuration object) that should ever exist
 */
Configuration * Configuration::getInstance()
{
    if (_configInstance == 0)
    {
        configurationInit();
        //TODO remove after ouput testing done
        ourConfiguration[0].floatValue = 111.111F;
        ourConfiguration[1].floatValue = 222.222F;
        ourConfiguration[2].floatValue = 333.333F;
        ourConfiguration[3].stringValue = "here is new text";
        ourConfiguration[4].intValue = 42;

    }
    return _configInstance;
}

/*
 * Read the values and create defaults, if they do not already exist
 */
void Configuration::ReadValues()
{
    int currentConfigEntry = 0;
    while(ourConfiguration[currentConfigEntry].type != endOfList)
    {
        //if (ContainsKey(ourConfiguration[currentConfigEntry].key)){
        if (false)
        {
            printf("Already have key %s\n", ourConfiguration[currentConfigEntry].key);
            currentConfigEntry++;
            continue; //Already have value from file so we're all set, go to the next part.
        }

        printf("%s\n", ourConfiguration[currentConfigEntry].humanName);
        if(ourConfiguration[currentConfigEntry].type == configFloat)
        {
             printf("have key %s\n", ourConfiguration[currentConfigEntry].key);
             float valueToSave = std::stof(ourConfiguration[currentConfigEntry].defaultValue);
             printf("value for float key %s is %f\n", ourConfiguration[currentConfigEntry].key, valueToSave);
      //      PutFloat("f", 15.23F);
            // _configInstance->PutFloat(ourConfiguration[currentConfigEntry].key, valueToSave);

           // printf("Found a float %s\n", ourConfiguration[currentConfigEntry].humanName);
           // float valueToSave = 123.456;// std::stof("123.456");
           // _configInstance->PutFloat(ourConfiguration[currentConfigEntry].key, valueToSave);
        }
        else if(ourConfiguration[currentConfigEntry].type == configInt)
        {
//            printf("Found an int %s\n", ourConfiguration[currentConfigEntry].humanName);
          // PutInt("abc", currentConfigEntry + 100);
// ourConfiguration[currentConfigEntry].key,
        }
        else if(ourConfiguration[currentConfigEntry].type == configString)
        {
            printf("Found a string %s\n", ourConfiguration[currentConfigEntry].humanName);
        }
        currentConfigEntry++;
    }
   // PutFloat("f", 15.53F);
   // PutInt("d", 555);
}

void Configuration::saveConfig(const char * fname)
{
    using std::endl;

    printf("Top of saveConfig\n");

    std::ofstream configFile("/home/lvuser/testConfig.ini");
    if(!configFile){
        printf ("Cannot open file for output\n");
        return;
    }
    configFile << "[Preferences]\n" << endl;

    //loop and print our all parameters
    int currentConfigEntry = 0;
    while(ourConfiguration[currentConfigEntry].type != endOfList)
    {
        printf("Prossesing key %s\n", ourConfiguration[currentConfigEntry].key);
        configFile << ourConfiguration[currentConfigEntry].key << '=' << '"';
        if(ourConfiguration[currentConfigEntry].type == configFloat)
        {
            configFile << ourConfiguration[currentConfigEntry].floatValue; //added for testing
        }
        else if(ourConfiguration[currentConfigEntry].type == configInt)
        {
            configFile << ourConfiguration[currentConfigEntry].intValue; //added for testing
        }
        else if(ourConfiguration[currentConfigEntry].type == configString)
        {
            configFile << ourConfiguration[currentConfigEntry].stringValue; //added for testing
        }
        configFile << '"';
        configFile << endl;
        currentConfigEntry++;
    }
    //std::vector<std::string> theKeys = GetKeys();


    //std::string theTakenString2 = _configInstance->GetString("e");
    //printf("Got string e = %s\n", theTakenString2.c_str());
    //if (ContainsKey("e"))
    //   {
       //std::string theTakenString = _configInstance->GetString("e");
       //printf("Got string e = %s\n", theTakenString.c_str());
    //   }
    //else{
    //}


    configFile << std::flush;
    configFile.close();
}

void Configuration::readConfig(const char * fname)
{

}

void Configuration::PutConfigInt(const char * key, int value)
{
    string intasstring = std::to_string(value);
//    PutString(key, intasstring.c_str());
}

int Configuration::GetConfigInt (const char * key, int defaultValue)
{
    int theintvalue = 0;

//    if (ContainsKey(key))
    {
//        std::string intasstring = GetString(key);
//        theintvalue = stoi(intasstring);
//    }
//    else
//    {
        theintvalue = defaultValue;
    }
    return theintvalue;
}

Configuration::~Configuration()
{

}
