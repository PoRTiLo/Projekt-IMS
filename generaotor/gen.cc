/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     SCGen.cc
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */


#include "gen.h"

unsigned static ix = 1537;

double SCGen::GenNom() {

	ix = ix *69069+1;
	return ix/((double)ULONG_MAX+1);
}


double SCGen::GenRovInterval( double a, double b ) {

	return a + b*(rand()/(RAND_MAX+1.0));
}

double SCGen::GenNomInterval() {

	return 1*(rand()/(RAND_MAX+1.0));
}

double SCGen::GenExp( double exp ) {
	double x = GenNomInterval();
	return -exp * log(x);
}

double SCGen::GenExp( double exp, double x0 ) {

	double x = GenNomInterval();
	return x0 - exp * log(x);
}

double SCGen::GenNormal( double ex, double stx ) {

	double x = GenNomInterval();
	double y = GenNomInterval();
	return stx * sqrt(-2 * (log(x))) * cos(2*PI*y) + ex;
}

double SCGen::GenGaus( double min, double max ) {

	double x = GenNomInterval();
	double y = GenNomInterval();
	double ex = abs((max) - (min));
	double pom = max - ex;
	pom = pom/3;

	return (pom) * sqrt(-2 * (log(x))) * cos(2*PI*y) + ex;
}

double SCGen::GenPoisson( double poiss, double countMin) {

	return GenExp(countMin/poiss);
}

double SCGen::GenPoisson( double poiss) {

	return GenExp(60/poiss);
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

//		std::cout << GenNomInterval()<<std::endl;;
	//	std::cout <<" " <<  1.0*(rand()/(RAND_MAX+1.0)) << std::endl;
//		std::cout << 1.0 * (GenNom()*(RAND_MAX+1.0)) << std::endl;
//		std::cout << GenExp(5)<<std::endl;;
		std::cout << SCGen::GenGaus(1,3) << std::endl;
//		std::cout << SCGen::GenNormal(1,5) << std::endl;
	}

	return 0;

}



//}
