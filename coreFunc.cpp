/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     coreFunc.cpp
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#include "coreFunc.h"
#include "place.h"
#include "transition.h"
#include "directedArc.h"
#include "calendar.h"
#include <limits.h>
#include <stdio.h>
#include "stats.h"

std::vector<SCPlace*> g_allPlaces;
std::vector<SCTransition*> g_allTrans;
std::vector<SCDirectedArc*> g_allDirected;
SCCalendar g_eventCal;
double g_time = 0;
double g_simLength = 0;
unsigned int g_transIndex = 0;
unsigned int g_placeIndex = 0;
unsigned int g_arcIndex = 0;
bool g_print = true;
bool g_printT = true;
bool g_printAll = true;

int Run()
{
	if(g_simLength == 0)
	{
		g_simLength = numeric_limits<double>::max();
	}
	if(!ValidateModel())
	{
		return -1;
	}
	std::vector<SCTransition*>::iterator it;
	for(it = g_allTrans.begin(); it < g_allTrans.end(); it++)
	{
		if((*it)->GetDirectedArcsFrom()->empty())
			g_eventCal.Insert(*it,(*it)->GetExactTime());
	}

	if( g_print )
		SCStat::PrintLegend();

	int ret = 0;
	SCCalendarUnit *unit = NULL;
	while(g_time < g_simLength)
	{
		unit = g_eventCal.GetNextUnit();
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
		if((ret = unit->GetBase()->Run()) != BASE_OK)
		{
			if(SCBase::EvaluateErrorCode(ret,unit->GetBase()) == BASE_FATAL)
			{
				delete unit;
				break;
			}
		}
		delete unit;
	}

	if(g_printAll)												// tiskne souhrnou statistiku
		SCStat::PrintStatAll();

	cout << endl;
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
bool ValidateModel()
{
	bool ret = true;
	bool res = false;
	cout<<"PetriSim version 1.0.0"<<endl<<endl;
	cout<<"Checking for model validity... ";
	//preskuma ci sa v modely nenachadza nekonecny cyklus s nulovym casom
	vector<SCTransition*>::iterator it;
	vector<SCPlace*>::iterator it2;
	//prehliada vsetky miesta
	for(it2 = g_allPlaces.begin(); it2 < g_allPlaces.end(); it2++)
	{
		if(!(*it2)->CheckTransitions())
		{
			ret = false;
		}
	}
	//prehlada vsetky prechody
	for(it = g_allTrans.begin(); it < g_allTrans.end(); it++)
	{
		if((*it)->CheckZeroTimeLoop())
		{
			if(ret)
			{
				cout<<"failed!"<<endl<<endl;
			}
			cout<<"MODEL LOGIC ERROR: Model contains infinite loop in zero time and cannot be simulated properly, Check model !!!"<<endl;
			ret = false;
			break;
		}
	}
	if(ret)
	{
		cout<<"sucess!"<<endl<<endl;
	}
	return ret;
}
