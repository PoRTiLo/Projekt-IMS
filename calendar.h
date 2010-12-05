#pragma once

#ifndef CALENDAR_H__
#define CALENDAR_H__

#include "calElement.h"

class Calendar
{

	private:
		int count;						// pocet prvku v kalendari
		CalElement* head;				// hlavicka kalendare

		/**
		 * Iniializace kalendare.
		 */
		void init();

		/**
		 * Vyhleda pozadovanou pozici MISTA v kalendari.
		 * @param[in] <SCPlace*> place
		 * @retunr <CalElement> vraci ukazatel n apozici v kalendari, jez obsahuje place
		 */
		CalElement* search( SCPlace* place );

		/**
		 *
		 *
		 */
		CalElement* search( CalElement* elementIn );

		/**
		 * Smazani urciteho mista v kalendari.
		 * @param[in] <SCPlace*> misto v kalendari
		 */
		void remove( SCPlace* place );

		/**
		 * Smazani celeho kalendare.
		 */
		void remove();

		/**
		 *
		 */
		void insertData( CalElement* element );
		
	public:
		/**
		 * Konstruktor.
		 */
		Calendar();

		/**
		 * Destruktor.
		 */
		~Calendar();

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
		 * Vrati prvni prvek v kalendari. Smaze jej z kalendare. 					POTREBA HO PAK UVOLNIT
		 * @return<CalElement> prvni prvek v kalendari
		 */
		CalElement* getFirst();

		/**
		 *
		 *
		 */
		void insert( CalElement elementIn );

		/**
		 *
		 *
		 *
		 *
		 */
		void insert( SCPlace* place, double time );

};

#endif //CALENDAR_H__
