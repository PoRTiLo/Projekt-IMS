#include "calendarUnit.h"

// Konstruktor.
SCCalendarUnit::SCCalendarUnit( SCPlace* place, double time )
{
	this->cont = 0;
	this->pre = 0;
	this->time = time;
	this->place = place;

}

// Kopirovaci konstruktor.
SCCalendarUnit::SCCalendarUnit( const SCCalendarUnit& element )
{
	this->cont = element.cont;
	this->pre = element.pre;
	this->time = element.time;
	this->place = element.place;
}

// Nastaveni casu.
void SCCalendarUnit::SetTime( const double time ) {

	this->time = time;
}

// Nastaveni mista.
void SCCalendarUnit::SetPlace( SCPlace* place ) {

	this->place = place;
}
// Vraci promennou cas.
double SCCalendarUnit::GetTime() {

	return this->time;
}

// Vrati misto.
SCPlace* SCCalendarUnit::GetPlace() {

	return this->place;
}
