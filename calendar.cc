#include "calendar.h"

// Konstruktor.
SCCalendar::SCCalendar()
{
	SCCalendar::init();
}

// Inizializace kalendare.
void SCCalendar::init() {

	this->count = 0;											// pocet prvku = 0, hlavicka se do toho nepocita
	this->head = new SCCalendarUnit;						// tvorba hlavicky, prvni prvek, ukazuje sam na sebe
	this->head->cont = this->head;
	this->head->pre = this->head;
}

// Destruktor.
SCCalendar::~SCCalendar() {

	SCCalendar::remove();
	delete this->head;												// odstraneni hlavicky
}

// Odstrani pozadovany prvek z kalendare.
void SCCalendar::remove( SCCalendarUnit* calUnit ) {
	SCCalendarUnit* pom = this->head->cont;
	while( pom != this->head )
	{
		if( calUnit == pom && pom->cont != this->head )
		{
			pom->pre->cont = pom->cont;
			pom->cont->pre = pom->pre;
			this->count--;
			//if( pom->place != NULL )
			//	delete pom->place;
			delete pom;
			break;
		}
		else if( calUnit == pom )	// mazani posledniho prvku kalendare
		{
			head->cont = this->head;
			head->pre = this->head;
			this->count = 0;
			delete pom;
			break;
		}
		else
			pom = pom->cont;
	}
}

// vyprazdni kalendar
void SCCalendar::remove() {
	
	while( this->head->cont != this->head )
	{
		remove( this->head->cont );
	}
}

// vrati pocet elementu v kalendari
int SCCalendar::getCount() {

	return this->count;
}

// zjisti zda je kalendar prazdny
bool SCCalendar::isEmpty() {
	
	if( this->count == 0 )
		return true;

	return false;
}

// Vrati prvni prvek, ael ponecha ho v kalendari
SCCalendarUnit* SCCalendar::getFirst() {

	return this->head->cont;
}

// Vrati posledni prvek kalendare
SCCalendarUnit* SCCalendar::getLast() {
	
	return this->head->pre;
}

// vlozi data do kalendare
void SCCalendar::insertData( SCCalendarUnit* newEl, SCCalendarUnit* pom ) {

	if( SCCalendar::isEmpty() )	//kalendara je prazdny
	{
		this->head->cont = newEl;
		this->head->pre = newEl;
		newEl->cont = this->head;
		newEl->pre = this->head;
	}
	else	//kalendar neni prazdny
	{
		newEl->cont = pom;
		newEl->pre = pom->pre;
		pom->pre->cont = newEl;
		pom->pre = newEl;
	}
	this->count++;
}

// vlozi element do kalendare
void SCCalendar::insert( SCCalendarUnit elementIn ) {

	SCCalendarUnit* newEl = new SCCalendarUnit( elementIn );
	SCCalendarUnit* pom = SCCalendar::search( newEl->time );
	SCCalendar::insertData(newEl, pom);
}

// vlozeni dat do kalnedare
void SCCalendar::insert( SCPlace placeIn, double time ) {

	SCPlace* place = new SCPlace(placeIn);
	SCCalendarUnit* pom = SCCalendar::search( time );
	SCCalendarUnit* newEl = new SCCalendarUnit(place, time);
	SCCalendar::insertData(newEl, pom);
}

// hleda podle casu elementu
SCCalendarUnit* SCCalendar::search( const double timeIn ) {

	if( SCCalendar::isEmpty() )
		return this->head;

	SCCalendarUnit* pom;
	pom = this->head->cont;
	bool found = false;
	while( pom != this->head && !found )
	{
		if( pom->time > timeIn )		// udalost s vetsim casem
		{
			found = true;
			break;
		}
		else
			pom = pom->cont;				// nasledujici prvek
	}

	if( !found )
		pom = this->head;

	return pom;
}

// zobrazi obsah kalendare
void SCCalendar::show() {

	SCCalendarUnit* pom;
	pom = this->head->cont;

	int i = 1;
	while( pom != this->head )
	{
		cout << i++ << ".prvek-time: " << pom->time  << "-place-mode:" << pom->place->GetData()->mode << "-place-data:" << pom->place->GetData()->data << endl;  
		pom = pom->cont;
	}
}

// vrati prvni prvek v kalendari a odstrani jej
SCCalendarUnit SCCalendar::getNextUnit() {

	SCCalendarUnit calUnit;
//	calUnit = SCCalendar::getFirst();
	calUnit.place = this->head->cont->place;
	calUnit.time = this->head->cont->time;
	SCCalendar::remove(this->head->cont);

	return calUnit;
}

/*
// najde pozici pred kterou se ma element vlozit do kalendare
SCCalendarUnit * SCCalendar::search( SCCalendarUnit* elementS ) {
}

SCCalendarUnit* SCCalendar::search( SCPlace* place ) {
}
*/
