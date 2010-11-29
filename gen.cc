/*IMS-----------------
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     gen.cc
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */


#include "gen.h"

double Gen::genNom() {
	ix = ix *69069+1;
	return ix/((double)ULONG_MAX+1);
}


double Gen::genNomInterval(int a, int b) {

	return a + b*(rand()/(RAND_MAX+1.0));
}

double Gen::genNomInterval() {

	return 1*(rand()/(RAND_MAX+1.0));
}

double Gen::genExp(int exp) {
	double x = genNomInterval();
	return -exp * log(x);
}

double Gen::genExp(int exp, int x0) {
	double x = genNomInterval();
	return x0 - exp * log(x);
}

double Gen::genGaus(double ex, double stx) {
	double x = genNomInterval();
	double y = genNomInterval();
	return stx * sqrt(-2 * (log(x))) * cos(2*PI*y) + ex;
}

double Gen::genPoisson(int poiss, int countMin) {

	return genExp(countMin/poiss);
}

double Gen::genPoisson(int poiss) {

	return genExp(60/poiss);
}



/**
 * MAIN
 * @param[in] <int> argc
 * @param[in] <char*> argv[]
 * @return <int> 
 */
//int main(int argc, const char* argv[])
//{
//	for(int i = 0; i < 1000000; i++)
//	{
//		std::cout << 1.0*(rand()/(RAND_MAX+1.0))<<std::endl;;

//		std::cout << genNomInterval()<<std::endl;;
	//	std::cout <<" " <<  1.0*(rand()/(RAND_MAX+1.0)) << std::endl;
//		std::cout << 1.0 * (genNom()*(RAND_MAX+1.0)) << std::endl;
//		std::cout << genExp(5)<<std::endl;;
//		std::cout << Gen::genGaus(5,1) << std::endl;
//	}

//	return 0;

//}



//}
