/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     stats.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once

#ifndef STATS_H__
#define STATS_H__
#include "coreFunc.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <iomanip>

using namespace std;

/**
 * Trida reprezentujisi statistiku petriho site.
 */
class SCStat
{
	private:
		/**
		 * Velikost cisla - pocet znaku.
		 * @param[in] <unsigned int> i cislo potrebne zjistt pocet znaku.
		 * @return <unsigned int> pocet znaku cisla.
		 */
		static unsigned int GetSizeInt(unsigned int i);

		/**
		 * Velikost cisla - pocet znaku.
		 * @param[in] <double> i cislo potrebne zjistt pocet znaku.
		 * @return <unsigned int> pocet znaku cisla.
		 */
		static unsigned int GetSizeDouble( double i );

		/**
		 * Zjisti nejvetsi kapacitu mist.
		 * @return <int> nejvetsi kapacita mista.
		 */
		static int MaxPlaceCapacity();

		/**
		 * Zjisti nejvetsi pocatecni hodnotu mista.
		 * @return <int> nejvetsi pocatecni pocet kulicek v miste.
		 */
		static int MaxPlaceStartValue();

		/**
		 * Zjisti nejvetsi pocet vsech kulicek v miste.
		 * @return <int> nejvetsi pocet vsech kulicek.
		 */
		 static int MaxPlaceTotal();

		/**
		 * Zjisti nejdelsi jmeno mista.
		 * @return <int> pocet znaku nejvetsiho jmena mista.
		 */
		static int MaxPlaceName();

		/**
		 * Zjisti nejvetsi pravdepodobnost prechodu.
		 * @return <int> nejvesti prevdepodobnost prechodu.
		 */
		static double MaxTransitionProbability();

		/**
		 * Zjisti nejvetsi prioritu prechodu.
		 * @param <int> nejvetsi priorita prechodu.
		 */
		static int MaxTransitionPriority();

		/**
		 * Zjisti nejvetsi jmeno prechodu.
		 * @return <int> pocet znaku nejdelsiho jemna prechodu.
		 */
		static int MaxTransitionName();

		/**
		 * Zjisti nejvetsi pocet proslych kulicek pres prechod.
		 * @return <int> nejvetsi pocet kulicek proslych pres prechod.
		 */
		static int MaxTransitionTotalPassedOut();

		/**
		 * Zjisti nejvetsi pocet veslych kulicek pres prechod.
		 * @return <int> nejvetsi pocet kulicek proslych pres prechod.
		 */
		static int MaxTransitionTotalPassedIn();

		/**
		 * Typ casovaneho prechodu.
		 * @return <string> tyo casovaneho prechodu.
		 */
		static string GetTransitionTime( int i );

		/**
		 * Prevod cisla integru na retezec.
		 * @param[in] <double> num prevadene cislo.
		 * @return <string> cislo ve formatu retezce.
		 */
		static string convertDouble( double num );

		/**
		 * Zjisti nejdelsi jmeno hrany.
		 * @return <int> nejdelsi jmeno hrany.
		 */
		static int MaxDirectedName();

		/**
		 * Zjisti nejvetsi vahu hrany.
		 * @return <int> velikost nejvetsi vahy hrany.
		 */
		static int MaxDirectedWeight();


	public:
		/**
		 * Konstruktor.
		 */
		SCStat(){}

		/**
		 * Destruktor.
		 */
		~SCStat(){}

		/**
		 * Tisk souhrnych statistik - misto, prechod, hrana, celkem.
		 */
		static void PrintStatAll();

		/**
		 * Tisk statisiky 'celkem'.
		 */
		static void PrintMain();

		/**
		 * Tisk statistiky 'mista'.
		 */
		static void PrintPlace();

		/**
		 * Tsik statsitky 'prechod'.
		 */
		static void PrintTransition();

		/**
		 * Tisk statistiky 'hrana'.
		 */
		static void PrintDirected();

		/**
		 * Tisk koncovych hvezdicek.
		 */
		 static void PrintEnd();

		/**
		 * Tisk legendy pro jednotlive vypisy
		 */
		static void PrintLegend();
};
#endif //STATS_H__
