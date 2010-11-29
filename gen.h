/*IMS-----------------
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     gen.h
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once

#ifndef GEN_H__
#define GEN_H__



#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits.h>


#define PI 3.1415926535897932384626433832795
unsigned static ix = 1537;

class Gen
{

	public:

		/**
		 * Konstruktor
		 */
		Gen(){}

		/**
		 * Destruktor
		 */
		~Gen(){}

		/**
	 	* Generator .... rozlozeni
	 	* @return <double> pseudonahodne cislo
	 	*/
		static double genNom();

		/**
		 * Generator pseudonahodnych cisel v urcitem rozsahu
		 * @param[in] <int> a dolni hranice
		 * @param[in] <int> b horni hranice
		 * @return <double> nahodne cislo v intervalu (a,b)
		 */
		static double genNomInterval( int a, int b ); 

		/**
		 * Generator pseudonahodnych cisel v intervalu (0,1)
		 * @return <double> nahodne cislo v intervalu (0,1)
		 */
		static double genNomInterval(); 

		/**
		 * Exponencialni rozlozeni - pro nahodna cisla v R(0,1)
		 * rozlozeni dob obsluhy, casove intervaly mezi poruchami a prichody do front
		 * @param[in] <int> exp stredni hodnota
		 * @return <double>
		 */
		static double genExp( int exp ); 

		/**
		 * Exponencialni rozlozeni - pro nahodna cisla v R(0,1)
		 * @param[in] <int> exp stredni hodnota
		 * @param[in] <int> x0 pocatecni hodnota-posunuti
		 * return <double>
		 */
		static double genExp( int exp, int x0 );

		/**
		 * Normalni rozlozeni-Gaussovo rozlozeni - nahodna cisla v R(0,1)
		 * @param[in] <double> ex stredni hodnota
		 * @param[in] <double> stx sigma ( pro 3stx ..99% obsahu)
		 * @return <double>
		 */
		static double genGaus( double ex, double stx ); 

		/**
		 * Poissonovo rozlozeni
		 * @param[in] <int> countMin
		 * @param[in] <int> poiss
		 * @return <double>
		 */
		static double genPoisson( int poiss, int countMin );

		/**
		 * Poissonovo rozlozeni
		 * Transformace na exponencialni rozlozeni, podelenim casove jednotky - pocet prichodu za hodinu
		 * @param[in] <int> poiss
		 * @return <double>
		 */
		static double genPoisson( int poiss );

};


#endif //GEN_H__
