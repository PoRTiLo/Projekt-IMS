#pragma once

#ifndef CALENDAR_H__
#define CALENDAR_H__

#include <iostream>
#include "calendarUnit.h"


/**
 * Kalendar.
 * Implementovan jako obousmerny seznam s hlavickou.
 */
class SCCalendar
{

	private:
		int count;								// pocet prvku v kalendari
		SCCalendarUnit* head;				// hlavicka kalendare

		/**
		 * Iniializace kalendare. Vytvoreni hlavicky seznamu. Pocet prvku nastaven na nulu.
		 */
		void init();

		/**
		 * Vyhleda pozadovanou pozici MISTA v kalendari.
		 * @param[in] <SCPlace*> place
		 * @retunr <SCCalendarUnit> vraci ukazatel n apozici v kalendari, jez obsahuje place
		 */
//		SCCalendarUnit* search( SCPlace* place );

		/**
		 *
		 *
		 */
//		SCCalendarUnit* search( SCCalendarUnit* elementIn );

		/**
		 *
		 *
		 *
		 */
		SCCalendarUnit* search( const double time );

		/**
		 * Smazani urciteho mista v kalendari.
		 * @param[in] <SCCalndarUnit*> misto v kalendari
		 */
		void remove( SCCalendarUnit* calUnit );

		/**
		 *
		 */
		void insertData( SCCalendarUnit* element, SCCalendarUnit* pom );
		
	public:
		/**
		 * Konstruktor.
		 */
		SCCalendar();

		/**
		 * Destruktor.
		 */
		~SCCalendar();

		/**
		 * Vrati pocet prvku v kalendari.
		 * @return <int> pocet prvku v kalendari
		 */
		int getCount();

		/**
		 * Zjisti zda je kalendar prazdny.
		 * @return <bool> treu je prazdny, false neni prazdny
		 */
		bool isEmpty();

		/**
		 * Vrati prvni prvek v kalendari. NEsmaze ho z kalendare.
		 * @return<SCCalendarUnit> prvni prvek v kalendari
		 */
		SCCalendarUnit* getFirst();

		/**
		 * Smazani celeho kalendare.
		 */
		void remove();

		/**
		 * Vrati posledni prvek kalendare. NEsmaze ho z kalendare.
		 * @return <SCCalendarUnit> posledni prvek kalendare.
		 */
		SCCalendarUnit* getLast();

		/**
		 *
		 *
		 */
		void insert( SCCalendarUnit elementIn );

		/**
		 *
		 *
		 *
		 *
		 */
		void insert( SCPlace place, double time );

		/**
		 * Zobrazi obsah kalendare. Vypise casy vsech prvku.
		 */
		void show();

		/**
		 * Vrati prvnio prvek kalendare a smaze jej z nej.
		 * @return <SCCalendarUnit> Vrati dalsi prvek kalendare.
		 */
		SCCalendarUnit getNextUnit();

};

#endif //CALENDAR_H__
