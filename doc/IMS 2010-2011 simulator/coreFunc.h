/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     coreFunc.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once
#include <vector>
#include <limits>


class SCTransition;
class SCPlace;
class SCDirectedArc;
class SCCalendar;

extern std::vector<SCPlace*> g_allPlaces;			//vector of all Places
extern std::vector<SCTransition*> g_allTrans;		//vector of all Transitions
extern std::vector<SCDirectedArc*> g_allDirected;	//vector of all Directed Arcs
extern double g_time;								//simulation time
extern SCCalendar g_eventCal;						//calendar
extern unsigned int g_transIndex;					//index for transiton idetifying
extern unsigned int g_placeIndex;					//index for place idetifying
extern unsigned int g_arcIndex;						//index for directed arcs idetifying
extern bool g_print;								//step stats
extern bool g_printT;															
extern bool g_printAll;								//summary stats

/* Runs the simulation */
int Run();
/* Sets simulation length */
void SetSimulationLength(double length);
/* Connects place to transition */
int PlToTr(SCPlace *start,SCTransition *end, SCDirectedArc *arc);
/* Connects transition to place */
int TrToPl(SCTransition *start,SCPlace *end, SCDirectedArc *arc);
/* Validates model */
bool ValidateModel();
/* Sets print statistics by steps option */
void PrintSteps( bool stat );
/* Sets print statistics summary option */
void PrintSummary( bool stat );
/* Resets all simulation data to default */
void ClearSimulation();
