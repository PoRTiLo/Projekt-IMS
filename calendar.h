/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     calendar.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once

#ifndef CALENDAR_H__
#define CALENDAR_H__

#include "calendarUnit.h"
#include "statusList.h"


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
		void Init();

		/**
		 * Vyhleda pozadovanou pozici MISTA v kalendari.
		 * @param[in] <SCBase*> base
		 * @retunr <SCCalendarUnit> vraci ukazatel n apozici v kalendari, jez obsahuje base
		 */
//		SCCalendarUnit* search( SCBase* base );

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
		SCCalendarUnit* Search( const double time );


		SCCalendarUnit* SearchRandom( const double time );

		/**
		 * Smazani urciteho mista v kalendari.
		 * @param[in] <SCCalndarUnit*> misto v kalendari
		 */
		void Remove( SCCalendarUnit* calUnit );

		/**
		 *
		 */
		void InsertData( SCCalendarUnit* element, SCCalendarUnit* pom );
		
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
		int GetCount();

		/**
		 * Zjisti zda je kalendar prazdny.
		 * @return <bool> treu je prazdny, false neni prazdny
		 */
		bool IsEmpty();

		/**
		 * Vrati prvni prvek v kalendari. NEsmaze ho z kalendare.
		 * @return<SCCalendarUnit> prvni prvek v kalendari
		 */
		SCCalendarUnit* GetFirst();

		/**
		 * Smazani celeho kalendare.
		 */
		void Remove();

		/**
		 * Vrati posledni prvek kalendare. NEsmaze ho z kalendare.
		 * @return <SCCalendarUnit> posledni prvek kalendare.
		 */
		SCCalendarUnit* GetLast();

		/**
		 *
		 *
		 */
		void Insert( SCCalendarUnit elementIn );

		/**
		 *
		 *
		 *
		 *
		 */
		void Insert( SCBase *base, double time );

		/**
		 *
		 *
		 *
		 *
		 */
		void InsertRandom( SCBase *base, double time );

		/**
		 * Zobrazi obsah kalendare. Vypise casy vsech prvku.
		 */
		void Show();

		/**
		 * Vrati prvnio prvek kalendare a smaze jej z nej.
		 * @return <SCCalendarUnit> Vrati dalsi prvek kalendare.
		 */
		SCCalendarUnit *GetNextUnit();

};

#endif //CALENDAR_H__
