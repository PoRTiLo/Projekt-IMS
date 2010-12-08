#pragma once

#ifndef CALELEMENT_H__
#define CALELEMENT_H__

#include "place.h"


/**
 * Prvek kalendare.
 */
class SCCalendarUnit {

	public:
		SCCalendarUnit* cont;								// predchozi element
		SCCalendarUnit* pre;									// nasledujici element
		SCPlace* place;										// misto
		double time;											// cas

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

};

#endif //CALELEMENT_H__
