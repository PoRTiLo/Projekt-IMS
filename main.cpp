/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     main.cpp
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#include "PetriSim.h"

short int WhichModel(int argcIn, const char* argvIn[]);

int main(int argc,const char* argv[])
{
	SetPrint( argc, argv);
	short model = WhichModel(argc, argv);

	if( model == MODEL_1 )                          //model cvicenie 1, slidy strana 12, horny obrazok
	{
		SCPlace p[5];
		SCDirectedArc a[8];
		SCTransition t[3];

		p[0].SetArgStartVal(3);
		p[1].SetArgStartVal(1);

		PlToTr(&p[0],&t[0],&a[0]);
		TrToPl(&t[0],&p[2],&a[1]);
		PlToTr(&p[1],&t[0],&a[2]);
		PlToTr(&p[2],&t[1],&a[3]);
		TrToPl(&t[1],&p[3],&a[4]);
		PlToTr(&p[3],&t[2],&a[5]);
		TrToPl(&t[2],&p[1],&a[6]);
		TrToPl(&t[2],&p[4],&a[7]);

		Run();
	}
	else if( model == MODEL_2 )							//model cvicenie 1, slidy strana 12, dolny obrazok
	{
		SCPlace p[4];
		SCDirectedArc a[6];
		SCTransition t[3];

		p[0].SetArgStartVal(1);
	
		PlToTr(&p[0],&t[0],&a[0]);
		TrToPl(&t[0],&p[1],&a[1]);
		TrToPl(&t[1],&p[2],&a[2]);
		PlToTr(&p[2],&t[2],&a[3]);
		TrToPl(&t[2],&p[3],&a[4]);
		PlToTr(&p[0],&t[2],&a[5]);

		Run();
	}
	else if( model == MODEL_3 )						//model dokumentacia strana TODO: X
	{
		SCPlace p[3];
		SCDirectedArc a[4];
		SCTransition t[2];

		p[0].SetArgStartVal(2);
		t[0].SetArgProbability(70);

		PlToTr(&p[0],&t[0],&a[0]);
		PlToTr(&p[0],&t[1],&a[1]);
		TrToPl(&t[0],&p[1],&a[2]);
		TrToPl(&t[1],&p[2],&a[3]);

		Run();
	}
	else if( model == MODEL_4 )						//model dokumentacia strana TODO: X
	{
		SCPlace p[3];
		SCDirectedArc a[4];
		SCTransition t[2];

		p[0].SetArgStartVal(3);
		t[0].SetArgPrio(5);
		t[1].SetArgPrio(4);

		PlToTr(&p[0],&t[0],&a[0]);
		PlToTr(&p[0],&t[1],&a[1]);
		TrToPl(&t[0],&p[1],&a[2]);
		TrToPl(&t[1],&p[2],&a[3]);

		Run();
	}
	else if( model == MODEL_5 )						//model dokumentacia strana TODO: X
	{
		
	}
	
	SCPlace p[3];
	SCDirectedArc a[4];
	SCTransition t[2];

	p[0].SetArgStartVal(100);
	t[0].SetArgTime(5);
	t[1].SetArgTime(4);

	PlToTr(&p[0],&t[0],&a[0]);
	PlToTr(&p[0],&t[1],&a[1]);
	TrToPl(&t[0],&p[1],&a[2]);
	TrToPl(&t[1],&p[2],&a[3]);

	Run();

	g_allPlaces;
	return 0;
}

short int WhichModel( int argcIn, const char* argvIn[] ) {

	short int model = -1;
	if( argcIn == 1 )
	{
		// vsehny modely
	}
	else if( argcIn == 2 || argcIn == 3 ) //run model1 && run -stat model1
	{
		string pom = "";
		char pomChar[10];
		if( argcIn == 2 && argvIn[1][0] == 'm' )
			strcpy(pomChar, argvIn[1]);
		else if( argcIn == 3 && argvIn[2][0] == 'm' )
			strcpy(pomChar, argvIn[2]);
		for( unsigned int i = 5; i < strlen(pomChar); i++ )
			pom += pomChar[i];
		model = atoi(pom.c_str());
	}

	return model;
}
