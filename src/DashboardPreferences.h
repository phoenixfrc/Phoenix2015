/*
 * DashboardPreferences.h
 *
 *  Created on: Mar 2, 2015
 *      Author: Developer
 */

#ifndef SRC_DASHBOARDPREFERENCES_H_
#define SRC_DASHBOARDPREFERENCES_H_
#include "WPILib.h"
#include "Constants.h"
#include <sstream>

class DashboardPreferences{
public:
	DashboardPreferences();

	void updateButtons();
	//bool m_newName;
	bool m_button1;
	bool m_button2;
	bool m_button3;
	bool m_button4;

	~DashboardPreferences();

private:

};



#endif /* SRC_DASHBOARDPREFERENCES_H_ */
