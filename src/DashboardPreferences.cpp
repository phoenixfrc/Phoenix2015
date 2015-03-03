/*
 * DashboardPreferences.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Developer
 */
#include "DashboardPreferences.h"

DashboardPreferences::DashboardPreferences()
{}

void DashboardPreferences::customPreferences(){
	bool m_button1 = SmartDashboard::GetBoolean("DB/Button 1", true);
	bool m_button2 = SmartDashboard::GetBoolean("DB/Button 2", false);
	bool m_button3 = SmartDashboard::GetBoolean("DB/Button 3", false);

}

DashboardPreferences::~DashboardPreferences(){

}
