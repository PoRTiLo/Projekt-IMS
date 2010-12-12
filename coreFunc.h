#pragma once
#include <vector>
#include <limits>


class SCTransition;
class SCPlace;
class SCDirectedArc;
class SCCalendar;

extern std::vector<SCPlace*> g_allPlaces;
extern std::vector<SCTransition*> g_allTrans;
extern std::vector<SCDirectedArc*> g_allDirected;
extern double g_time;
extern SCCalendar g_eventCal;
extern unsigned int g_transIndex;
extern unsigned int g_placeIndex;
extern unsigned int g_arcIndex;
extern bool g_print;
extern bool g_printAll;

int Run();
void SetSimulationLength(double length);
int PlToTr(SCPlace *start,SCTransition *end, SCDirectedArc *arc);
int TrToPl(SCTransition *start,SCPlace *end, SCDirectedArc *arc);
void SetPrint(int argcIn, const char* atgvIn[]);
