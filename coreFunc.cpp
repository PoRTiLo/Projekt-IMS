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
	std::vector<SCTransition*>::iterator it;
	for(it = g_allTrans.begin(); it < g_allTrans.end(); it++)
	{
		if((*it)->GetDirectedArcsFrom()->empty())
			g_eventCal.Insert(*it,g_time);
	}

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
		unit->GetBase()->Run();
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