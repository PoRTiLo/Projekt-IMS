/*IMS-----------------
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     gen.cc
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */


#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits.h>

using namespace std;

//namespace ptNet {

//PT_NET_IMPLEMENTATION;

#define PI 3.1415926535897932384626433832795
unsigned static ix = 1537;


/**
 * Generator .... rozlozeni
 * @return <double> pseudonahodne cislo
 */
double genNom() {
	ix = ix *69069+1;
	return ix/((double)ULONG_MAX+1);
}


/**
 * Generator pseudonahodnych cisel v urcitem rozsahu
 * @param[in] <int> a dolni hranice
 * @param[in] <int> b horni hranice
 * @return <double> nahodne cislo v intervalu (a,b)
 */
double genNomInterval(int a, int b) {

	return a + b*(rand()/(RAND_MAX+1.0));
}

/**
 * Generator pseudonahodnych cisel v intervalu (0,1)
 * @return <double> nahodne cislo v intervalu (0,1)
 */
double genNomInterval() {

	return 1*(rand()/(RAND_MAX+1.0));
}

/**
 * Exponencialni rozlozeni - pro nahodna cisla v R(0,1)
 * rozlozeni dob obsluhy, casove intervaly mezi poruchami a prichody do front
 * @param[in] <int> exp stredni hodnota
 * @return <double>
 */
double genExp(int exp) {
	double x = genNomInterval();
	return -exp * log(x);
}

/**
 * Exponencialni rozlozeni - pro nahodna cisla v R(0,1)
 * @param[in] <int> exp stredni hodnota
 * @param[in] <int> x0 pocatecni hodnota-posunuti
 * return <double>
 */
double genExp(int exp, int x0) {
	double x = genNomInterval();
	return x0 - exp * log(x);
}

/**
 * Normalni rozlozeni-Gaussovo rozlozeni - nahodna cisla v R(0,1)
 * @param[in] <double> ex stredni hodnota
 * @param[in] <double> stx sigma ( pro 3stx ..99% obsahu)
 * @return <double>
 */
double genGaus(double ex, double stx) {
	double x = genNomInterval();
	double y = genNomInterval();
	return stx * sqrt(-2 * (log(x))) * cos(2*PI*y) + ex;
}

/**
 * Poissonovo rozlozeni
 * @param[in] <int> countMin
 * @param[in] <int> poiss
 * @return <double>
 */
double genPoisson(int poiss, int countMin) {

	return genExp(countMin/poiss);
}


/**
 * Poissonovo rozlozeni
 * Transformace na exponencialni rozlozeni, podelenim casove jednotky - pocet prichodu za hodinu
 * @param[in] <int> poiss
 * @return <double>
 */
double genPoisson(int poiss) {

	return genExp(60/poiss);
}



/**
 * MAIN
 * @param[in] <int> argc
 * @param[in] <char*> argv[]
 * @return <int> 
 */
int main(int argc, const char* argv[])
{
	for(int i = 0; i < 1000000; i++)
	{
//		std::cout << 1.0*(rand()/(RAND_MAX+1.0))<<std::endl;;

//		std::cout << genNomInterval()<<std::endl;;
	//	std::cout <<" " <<  1.0*(rand()/(RAND_MAX+1.0)) << std::endl;
//		std::cout << 1.0 * (genNom()*(RAND_MAX+1.0)) << std::endl;
//		std::cout << genExp(5)<<std::endl;;
		std::cout << genGaus(5,1) << std::endl;
	}

	return 0;

}



//}
