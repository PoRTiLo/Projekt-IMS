#include "calendar.h"

// Konstruktor.
SCCalendar::SCCalendar()
{
	SCCalendar::Init();
}

// Inizializace kalendare.
void SCCalendar::Init() {

	this->count = 0;											// pocet prvku = 0, hlavicka se do toho nepocita
	this->head = new SCCalendarUnit;						// tvorba hlavicky, prvni prvek, ukazuje sam na sebe
	this->head->cont = this->head;
	this->head->pre = this->head;
}

// Destruktor.
SCCalendar::~SCCalendar()
{
	SCCalendar::Remove();
	delete this->head;												// odstraneni hlavicky
}

// Odstrani pozadovany prvek z kalendare.
void SCCalendar::Remove( SCCalendarUnit* calUnit ) {
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
void SCCalendar::Remove() {
	
	while( this->head->cont != this->head )
	{
		Remove( this->head->cont );
	}
}

// vrati pocet elementu v kalendari
int SCCalendar::GetCount() {

	return this->count;
}

// zjisti zda je kalendar prazdny
bool SCCalendar::IsEmpty() {
	
	if( this->count == 0 )
		return true;

	return false;
}

// Vrati prvni prvek, ael ponecha ho v kalendari
SCCalendarUnit* SCCalendar::GetFirst() {

	if( this->head->cont == head )
		return NULL;

	return this->head->cont;
}

// Vrati posledni prvek kalendare
SCCalendarUnit* SCCalendar::GetLast() {
	
	if( this->head->pre == head )
		return NULL;

	return this->head->pre;
}

// vlozi data do kalendare
void SCCalendar::InsertData( SCCalendarUnit* newEl, SCCalendarUnit* pom ) {

	if( SCCalendar::IsEmpty() )	//kalendara je prazdny
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
void SCCalendar::Insert( SCCalendarUnit elementIn ) {

	SCCalendarUnit* newEl = new SCCalendarUnit( elementIn );
	SCCalendarUnit* pom = SCCalendar::Search( newEl->GetTime() );
	SCCalendar::InsertData(newEl, pom);
}

// vlozeni dat do kalnedare
void SCCalendar::Insert( SCPlace placeIn, double time ) {

	SCPlace* place = new SCPlace(placeIn);
	SCCalendarUnit* pom = SCCalendar::Search( time );
	SCCalendarUnit* newEl = new SCCalendarUnit(place, time);
	SCCalendar::InsertData(newEl, pom);
}

// hleda podle casu elementu
SCCalendarUnit* SCCalendar::Search( const double timeIn ) {

	if( SCCalendar::IsEmpty() )
		return this->head;

	SCCalendarUnit* pom;
	pom = this->head->cont;
	bool found = false;
	while( pom != this->head && !found )
	{
		if( pom->GetTime() > timeIn )		// udalost s vetsim casem
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
void SCCalendar::Show() {

	SCCalendarUnit* pom;
	pom = this->head->cont;

	int i = 1;
	while( pom != this->head )
	{
		cout << i++ << ".prvek-time: " << pom->GetTime()  << "-place-mode:" << pom->GetPlace()->GetData()->mode << "-place-data:" << pom->GetPlace()->GetData()->data << endl;  
		pom = pom->cont;
	}
}

// vrati prvni prvek v kalendari a odstrani jej
SCCalendarUnit SCCalendar::GetNextUnit() {

	if( this->head->cont == head )
		return NULL;

	SCCalendarUnit calUnit;
//	calUnit = SCCalendar::getFirst();
	calUnit.SetPlace( this->head->cont->GetPlace() );
	calUnit.SetTime( this->head->cont->GetTime() );
	SCCalendar::Remove(this->head->cont);

	return calUnit;
}

/*
// najde pozici pred kterou se ma element vlozit do kalendare
SCCalendarUnit * SCCalendar::search( SCCalendarUnit* elementS ) {
}

SCCalendarUnit* SCCalendar::search( SCPlace* place ) {
}
*/
