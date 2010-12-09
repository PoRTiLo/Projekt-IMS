#include "coreFunc.h"
#include "place.h"
#include "transition.h"
#include "directedArc.h"
#include "calendar.h"

#include <iostream>
#include <iomanip>
#include <stdio.h>
std::vector<SCPlace*> g_allPlaces;
SCCalendar g_eventCal;
double g_time = 0;
double g_simLength = 0;

int Run()
{
	/*
	vector<SCPlace*>::iterator it;
	int result;
	while(1)
	{
		result = PLACE_EMPTY;
		//for(it=g_allPlaces.begin();it!=g_allPlaces.end();it++)
		for( unsigned int i = 1; i < g_allPlaces.size(); i++ )
		{
			int partialResult = g_allPlaces[i]->Run();//(*it)->Run();
			if(partialResult == PLACE_SUCC || PLACE_SIM_END)
			{
				result = partialResult;
			}
		}
		if(result == PLACE_EMPTY)
		{
			break;
		}
		//todo - dorobit zaciatok simulacie a vyhdzovanie sa z vectoru v placech v pripade 0 guliciek
	}
	*/
	SCCalendarUnit *unit = NULL;
	while(g_time < g_simLength)
	{
		unit = g_eventCal.GetFirst();
		if(unit == NULL)
		{
			break;
		}
		else if(unit->GetTime() > g_simLength)
		{
			delete unit;
			break;
		}
		g_time = unit->GetTime();
		unit->GetPlace()->Run();
		delete unit;
	}
	return 0;
}
void SetSimulationLength(double length)
{
	g_simLength = length;
}
int PlToTr(SCPlace *start,SCTransition *end,SCDirectedArc *arc)
{
	start->AddDirectedArcTo(arc);
	end->AddDirectedArcFrom(arc);
	return 0;
}
int TrToPl(SCTransition *start,SCPlace *end,SCDirectedArc *arc)
{
	start->AddDirectedArcTo(arc);
	end->AddDirectedArcFrom(arc);
	return 0;
}

void printStat() {

	
		for( unsigned int i = 1; i < g_allPlaces.size(); i++ )
		{
			//g_allPlaces[i]->;
		}
	/* STATSISTIKY CELKEM
			- pocet mist
			- pocet prehodu
			- pocet hran
			- doba trvani simulatoru
		MISTO -statsistika kazdeho mista
			- kapacita
			- pocatecni stav
			- koncovy stav
			- celkovy pocet kulicek na tomto miste
		PREHOD - statistika kazdeho prechodu
			- priorita
			- casovani
			- inhibicni hrana
			- pravdepodobnost
			- pocet preslych kulicek
		HRANA - statistika kazde hrany
			- kapacita
	*/

	int sizePlace = getSizeInt(g_allPlaces.size()) + 3;
	cout << "******************************** STATISTIKY *****************************" << endl;
	cout << "*	C" <<endl;
	cout << "*	E        Pocet mist     : " << g_allPlaces.size() << endl;
	cout << "*	L        Pocet prechodu : " << endl;
	cout << "*	K        Pocet hran     : " << endl;
	cout << "*	E" <<endl;
	cout << "*	M" <<endl;
	cout << "*" <<endl;
	cout << "* ---------------------------------- mista -------------------------------" << endl;
	cout << "*" << endl;
	cout << "*   "<< setfill(' ')<<setw(sizePlace)<<"."<<" | jmeno |"<<setw(12)<<"kapacita"<<" | pocatecni stav | koncovy stav | celkem kulicek"<< endl;
	cout << "* "<<setw(sizePlace)<<" "<<"..................................................................." <<endl;
	char p[7] = "MISTA ";
	int k = 0;
	int cap = 2;//
	string space = "       ";// 7

	for(unsigned int i = 1; i != g_allPlaces.size(); i++ )
	{
		cout << "*  "<< p[k]<<setfill(' ')<<setw(sizePlace)<<i<< " |       |"<<setw(12)<<cap<<" |                |              |               "<< endl;
		if( k < 5 )
			k++;
		else if( i > 8 )
		{
			k = 5;
			if( i > 98 )
				space = "      ";//6
		}
		cap = cap *2;
	//	i/10;

	}
	cout << "*" <<endl;
	cout << "* ---------------- prechod ----------------" << endl;
	cout << "*" << endl;
	cout << "*	P" << endl;
	cout << "*	R" << endl;
	cout << "*	E" << endl;
	cout << "*	C" << endl;
	cout << "*	H" << endl;
	cout << "*	O" << endl;
	cout << "*	D" << endl;
	cout << "*" <<endl;
	cout << "* ----------------- hrana -----------------" << endl;
	cout << "*" << endl;
	cout << "*	H" << endl;
	cout << "*	R" << endl;
	cout << "*	A" << endl;
	cout << "*	N" << endl;
	cout << "*	A" << endl;
	cout << "*" <<endl;
	cout << "*******************************************" << endl;


}
int getSizeInt( int i ) {

	char num[30];
	sprintf(num, "%i", i);
	for(int k = 0; k < 30; k++ )
	{
		if( num[k] == '\0' )
			return k;
	}
}

int maxPlaceCap() {

/*	int size = g_allPlaces[0].GetData();
	for( unsigned int i = 1; i < g_allPlaces.size(); i++ )
	{
		if( size < g_allPlaces[i].GetData())
			size = g_allPlaces[i].GetData();
	}
	return size;
	*/
	return 1;
}

int maxPlaceStartValue() {
/*
	int size = g_allPlaces[0].GetData();
	for( unsigned int i = 1; i < g_allPlaces.size(); i++ )
	{
		if( size < g_allPlaces[i].GetData())
			size = g_allPlaces[i].GetData();
	}
	return size;
	*/
	return 1;
}

