#pragma once

#ifndef CALELEMENT_H__
#define CALELEMENT_H__

#include "place.h"

class CalElement {

	/*private:
		CalElement* cont;
		CalElement* pre;
		SCPlace* place;
		double time;
*/
	public:
		CalElement* cont;
		CalElement* pre;
		SCPlace* place;
		double time;
		/**
		 *
		 */
		CalElement( SCPlace* place = 0, double time = 0.0 );

		/**
		 *
		 *
		 */
		CalElement( const CalElement& element );

		/**
		 *
		 */
		~CalElement(){}

		/**
		 *
		 */
		CalElement* getElemPre();

		/**
		 *
		 */
		CalElement* getElemCont();
		
		/**
		 *
		 */
		SCPlace* getPlace();

		/**
		 *
		 */
		double getTime();

};

#endif //CALELEMENT_H__
