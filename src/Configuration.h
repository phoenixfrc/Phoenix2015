#include "WPILib.h"

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_



class Configuration : public Preferences {



private:

	Configuration();
	~Configuration();


public:


	void ConfigurationInit();
	static Configuration *GetInstance();

};


#endif /* SRC_CONFIGURATION_H_ */
