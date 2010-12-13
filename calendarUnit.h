/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     calendarUnit.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once

#ifndef CALELEMENT_H__
#define CALELEMENT_H__

#include "base.h"


/**
 * Prvek kalendare.
 */
class SCCalendarUnit {

	protected:
		SCBase* base;										// misto
		double time;											// cas

	public:
		SCCalendarUnit* cont;								// predchozi element
		SCCalendarUnit* pre;									// nasledujici element

		/**
		 * Konstruktor.
		 * @param[in] <SCBase*> base misto
		 * @param[in] <doouble> time cas
		 */
		SCCalendarUnit( SCBase* base = 0, double time = 0.0 );

		/**
		 * Kopirovaci konstruktor.
		 * @param[in] <const CalElement&> element Prvek kalendare jehoz se vytvori kopie.
		 */
		SCCalendarUnit( const SCCalendarUnit& element );

		/**
		 * Destruktor.
		 */
		~SCCalendarUnit(){}

		/**
		 * Nastaveni casu.
		 * @param[in] <double> time cas
		 */
		void SetTime( const double time );

		/**
		 * Nastaveni mista.
		 * @param[in] <SCBase>
		 */
		void SetBase( SCBase* base );

		/**
		 * Vraci cas.
		 * @return <double> cas
		 */
		double GetTime();

		/**
		 * Vrati misto.
		 * @return <SCBase*> misto
		 */
		SCBase* GetBase();

};

#endif //CALELEMENT_H__
