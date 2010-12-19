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

// typ modelu
#define MODEL_0 0									// vsechny modely
#define MODEL_1 1									// 1 model
#define MODEL_2 2									// modely ...
#define MODEL_3 3
#define MODEL_4 4
#define MODEL_5 5
#define MODEL_6 6
#define MODEL_7 7
#define MODEL_8 8

short int WhichModel(int argcIn, const char* argvIn[]);

void SetPrint(int argcIn, const char* argvIn[]);

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
//	else if( model == MODEL_5 )						//model dokumentacia strana TODO: X
	//{
		SCPlace p[12];
		SCDirectedArc a[27];
		SCTransition t[14];
	
		t[0].SetArgTime(10,TIME_EXP);
		TrToPl(&t[0],&p[0],&a[0]);
		PlToTr(&p[0],&t[1],&a[1]);
		t[1].SetArgTime(5);
		TrToPl(&t[1],&p[1],&a[2]);
		PlToTr(&p[1],&t[2],&a[3]);
		PlToTr(&p[1],&t[3],&a[4]);
		t[2].SetArgPrio(1);
		TrToPl(&t[2],&p[2],&a[5]);
		PlToTr(&p[2],&t[4],&a[6]); //koniec vetvy s prioritou 1
		t[3].SetArgPrio(2);
		TrToPl(&t[3],&p[3],&a[7]);
		PlToTr(&p[3],&t[5],&a[8]);
		t[5].SetArgTime((double)10,(double)20);
		TrToPl(&t[5],&p[4],&a[9]);
		PlToTr(&p[4],&t[6],&a[10]);
		TrToPl(&t[6],&p[5],&a[11]);
		TrToPl(&t[6],&p[6],&a[12]); //prechod k miestu s hodnotou 1 - vratenie
		p[6].SetArgStartVal(1);
		PlToTr(&p[5],&t[7],&a[13]); //koniec vetvy s prioritou 2
		PlToTr(&p[6],&t[3],&a[14]);
		//dolna vetva bez casu
		PlToTr(&p[0],&t[8],&a[15]);
		TrToPl(&t[8],&p[7],&a[16]);
		PlToTr(&p[7],&t[9],&a[17]); //vetva bez percent
		PlToTr(&p[7],&t[10],&a[18]);//vetva s 80 percentami zaciatok
		TrToPl(&t[9],&p[8],&a[19]);
		PlToTr(&p[8],&t[11],&a[20]);
		t[11].SetArgTime(5,TIME_EXP);
		TrToPl(&t[11],&p[9],&a[21]);
		PlToTr(&p[9],&t[12],&a[22]);//vetva bez percent koniec
		TrToPl(&t[10],&p[10],&a[23]);//vetva s 80 percentami pokracovanie
		PlToTr(&p[10],&t[13],&a[24]);
		t[13].SetArgTime(5);
		TrToPl(&t[13],&p[11],&a[25]);
		PlToTr(&p[11],&t[8],&a[26]);
		p[11].SetArgStartVal(5);

		SetSimulationLength(70);
		Run();
//	}
	/*
	SCPlace p[3];
	SCTransition t[3];
	SCDirectedArc a[6];

	p[0].SetArgStartVal(1);
	PlToTr(&p[0],&t[0],&a[0]);
	TrToPl(&t[0],&p[1],&a[1]);
	PlToTr(&p[1],&t[1],&a[2]);
	TrToPl(&t[1],&p[2],&a[3]);
	PlToTr(&p[2],&t[2],&a[4]);
	TrToPl(&t[2],&p[1],&a[5]);

	Run();
	*/
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
void SetPrint(int argcIn, const char* argvIn[]) {

	if( argcIn == 1 || (argcIn == 2 && argvIn[1][0] == 'm') )
	{
		cout << endl;
		g_print = true;
		g_printAll = true;
	}
	else if( argcIn > 1 && argcIn < 4 )
	{
		if( argvIn[1][0] == '-' && (argvIn[1][1] == 'n' || argvIn[1][9] == 'n') )
		{
			g_print = false;
			g_printAll = false;
		}
		else if( argvIn[1][0] == '-' && (argvIn[1][1] == 's' || argvIn[1][9] == 's') )
		{
			g_print = true;
			g_printAll = false;
		}
		else if( argvIn[1][0] == '-' && (argvIn[1][1] == 'a' || argvIn[1][9] == 'a') )
		{
			g_print = false;
			g_printAll = true;
		}
		cout << endl;
	}
	else
	{
		g_print = false;
		g_printAll = false;
	}
}
