#pragma once

#ifndef CALELEMENT_H__
#define CALELEMENT_H__

#include "place.h"


/**
 * Prvek kalendare.
 */
class SCCalendarUnit {

	protected:
		SCPlace* place;										// misto
		double time;											// cas

	public:
		SCCalendarUnit* cont;								// predchozi element
		SCCalendarUnit* pre;									// nasledujici element

		/**
		 * Konstruktor.
		 * @param[in] <SCPlace*> place misto
		 * @param[in] <doouble> time cas
		 */
		SCCalendarUnit( SCPlace* place = 0, double time = 0.0 );

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
		 * @param[in] <SCPlace>
		 */
		void SetPlace( SCPlace* place );

		/**
		 * Vraci cas.
		 * @return <double> cas
		 */
		double GetTime();

		/**
		 * Vrati misto.
		 * @return <SCPlace*> misto
		 */
		SCPlace* GetPlace();

};

#endif //CALELEMENT_H__
