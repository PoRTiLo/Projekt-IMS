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

SCGen::SCGen()
{
	SCGen::InitGenSeed();
}

void SCGen::InitGenSeed() {

	struct timeval time;
	gettimeofday(&time,NULL);
	srand((unsigned int) time.tv_usec);
}

double SCGen::GenNom() {

	ix = ix *69069+1;
	return ix/((double)ULONG_MAX+1);
}


double SCGen::GenNomInterval( double a, double b ) {

	SCGen::InitGenSeed();
	return a + b*(rand()/(RAND_MAX+1.0));
}

int SCGen::GenNomInterval( int a, int b ) {

	SCGen::InitGenSeed();
	return a+ (rand()%( ++b - a));
}

double SCGen::GenNomInterval() {

	SCGen::InitGenSeed();
	return 1*(rand()/(RAND_MAX+1.0));
}

double SCGen::GenExp( double exp ) {
	double x = GenNomInterval();
	return (exp * log(x))*(-1);
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
	double ex = abs(max - min)/2;
	return max * sqrt(-2 * (log(x))) * cos(2*PI*y) + ex;
}

double SCGen::GenPoisson( double poiss, double countMin) {

	return GenExp(countMin/poiss);
}

double SCGen::GenPoisson( double poiss) {

	return GenExp(60/poiss);
}
