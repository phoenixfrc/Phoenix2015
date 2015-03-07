/*
 * DashboardPreferences.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Developer
 */
#include "DashboardPreferences.h"

DashboardPreferences::DashboardPreferences():

	//m_newName(false),
	m_button1(false),
	m_button2(false),
	m_button3(false)
{}

void DashboardPreferences::updateButtons(){
	//m_newName = SmartDashboard::GetBoolean("New Name");
	m_button1 = SmartDashboard::GetBoolean("DB/Button 1");
	m_button2 = SmartDashboard::GetBoolean("DB/Button 2");
	m_button3 = SmartDashboard::GetBoolean("DB/Button 3");
}

DashboardPreferences::~DashboardPreferences(){

}
