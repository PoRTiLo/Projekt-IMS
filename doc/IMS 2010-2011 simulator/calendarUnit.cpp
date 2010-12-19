/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     calendarUnit.cpp
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#include "calendarUnit.h"

// Konstruktor.
SCCalendarUnit::SCCalendarUnit( SCBase* base, double time )
{
	this->cont = 0;
	this->pre = 0;
	this->time = time;
	this->base = base;

}

// Kopirovaci konstruktor.
SCCalendarUnit::SCCalendarUnit( const SCCalendarUnit& element )
{
	this->cont = element.cont;
	this->pre = element.pre;
	this->time = element.time;
	this->base = element.base;
}

// Nastaveni casu.
void SCCalendarUnit::SetTime( const double time ) {

	this->time = time;
}

// Nastaveni mista.
void SCCalendarUnit::SetBase( SCBase* base ) {

	this->base = base;
}
// Vraci promennou cas.
double SCCalendarUnit::GetTime() {

	return this->time;
}

// Vrati misto.
SCBase* SCCalendarUnit::GetBase() {

	return this->base;
}
