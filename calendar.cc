#include "calendar.h"

Calendar::Calendar()
{
	init();
}

void Calendar::init() {

	this->count = 0;
	this->head = new CalElement;
	this->head->cont = head;
	this->head->pre = head;
}

Calendar::~Calendar() {

	remove();
	delete head;
}

void Calendar::remove( SCPlace* place ) {

	CalElement* delElement = Calendar::search(place);
	if( delElement == this->head->cont )
	{
		this->head->cont = delElement->cont;
		delElement->cont->pre = head;
	}
	else
	{
		delElement->pre->cont = delElement->cont;
		delElement->cont->pre = delElement->pre;
	}
	this->count--;
	delete delElement->place;
	delete delElement;
}

void Calendar::remove() {
	
	while( head->cont != head )
	{
		remove( head->cont->place );
	}
}

int Calendar::getCount() {

	return this->count;
}

bool Calendar::isEmpty() {
	
	if( this->head == this->head->cont )
		return true;

	return false;
}

CalElement* Calendar::getFirst() {

	CalElement* pom = this->head->cont;
	this->head->cont = pom->cont;
	pom->cont->pre = head;
	return pom;
}

void Calendar::insertData( CalElement* element ) {

	if( isEmpty() )	//kalendara je prazdny
	{
		this->head->cont = element;
		this->head->pre = element;
		element->cont = head;
		element->pre = head;
	}
	else	//kalendar neni prazdny
	{
		CalElement* pom = Calendar::search( element );
		element->cont = pom;
		element->pre = pom->pre;
		pom->pre->cont = element;
		pom->pre  = element;
	}
	this->count++;
}


void Calendar::insert( CalElement elementIn ) {

	CalElement* element = new CalElement( elementIn );
	Calendar::insertData(element);
}

void Calendar::insert( SCPlace* place, double time ) {

	CalElement* element = new CalElement( place, time );
	Calendar::insertData( element );
}

CalElement * Calendar::search( CalElement* elementS ) {

	if( isEmpty() )
		return this->head;

	bool found = false;
	CalElement* pom = head->cont;
	CalElement* newEl = elementS;

	while( pom != head || !found )
	{
		if( pom->time > newEl->time )	// ma vetsi cas
		{
			found = true;
			break;
		}
		else
		{
			pom = pom->cont;
		}
	}

	if( !found )
		pom = head;

	delete newEl;

	return pom;
}

CalElement* Calendar::search( SCPlace* place ) {

}
