#include "calElement.h"

CalElement::CalElement( SCPlace* place, double time )
{
	this->cont = 0;
	this->pre = 0;
	this->time = time;
	this->place = place;

}

CalElement::CalElement( const CalElement& element )
{
	this->cont = element.cont;
	this->pre = element.pre;
	this->time = element.time;
	this->place = element.place;
}

CalElement* CalElement::getElemPre() {

	return this->pre;
}

CalElement* CalElement::getElemCont() {

	return this->cont;
}

SCPlace* CalElement::getPlace() {

	return this->place;
}

double CalElement::getTime() {

	return this->time;
}
