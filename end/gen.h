/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     gen.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once

#ifndef SCGen_H__
#define SCGen_H__



#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits.h>
#include <time.h>
#include <sys/time.h>

#define PI 3.1415926535897932384626433832795

class SCGen
{

	public:

		/**
		 * Konstruktor
		 */
		SCGen();

		/**
		 * Destruktor
		 */
		~SCGen(){}

		/**
	 	* SCGenerator .... rozlozeni
	 	* @return <double> pseudonahodne cislo
	 	*/
		static double GenNom();

		/**
		 * SCGenerator pseudonahodnych cisel v urcitem rozsahu
		 * @param[in] <double> a dolni hranice
		 * @param[in] <double> b horni hranice
		 * @return <double> nahodne cislo v doubleervalu (a,b)
		 */
		static double GenNomInterval( double a, double b );

		/**
		 * SCGenerator pseudonahodnych cisel v doubleervalu (0,1)
		 * @return <double> nahodne cislo v doubleervalu (0,1)
		 */
		static double GenNomInterval();

		static int GenNomInterval( int a, int b );

		/**
		 * Exponencialni rozlozeni - pro nahodna cisla v R(0,1)
		 * rozlozeni dob obsluhy, casove doubleervaly mezi poruchami a prichody do front
		 * @param[in] <double> exp stredni hodnota
		 * @return <double>
		 */
		static double GenExp( double exp );

		/**
		 * Exponencialni rozlozeni - pro nahodna cisla v R(0,1)
		 * @param[in] <double> exp stredni hodnota
		 * @param[in] <double> x0 pocatecni hodnota-posunuti
		 * return <double>
		 */
		static double GenExp( double exp, double x0 );

		/**
		 * Normalni rozlozeni-Gaussovo rozlozeni - nahodna cisla v R(0,1)
		 * @param[in] <double> ex stredni hodnota
		 * @param[in] <double> stx sigma ( pro 3stx ..99% obsahu)
		 * @return <double>
		 */
		static double GenNormal( double ex, double stx );

		/**
		 * Normalni rozlozeni-Gaussovo rozlozeni - nahodna cisla v R(0,1)
		 * @param[in] <double> min minimalni hodnota
		 * @param[in] <double> max maximalni hodnota
		 * @return <double>
		 */
		static double GenGaus( double min, double max );

		/**
		 * Poissonovo rozlozeni
		 * @param[in] <double> countMin
		 * @param[in] <double> poiss
		 * @return <double>
		 */
		static double GenPoisson( double poiss, double countMin );

		/**
		 * Poissonovo rozlozeni
		 * Transformace na exponencialni rozlozeni, podelenim casove jednotky - pocet prichodu za hodinu
		 * @param[in] <double> poiss
		 * @return <double>
		 */
		static double GenPoisson( double poiss );

		static void InitGenSeed();

};


#endif //SCGen_H__
