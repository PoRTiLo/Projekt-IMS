#pragma once
#include <vector>


class SCTransition;
class SCPlace;
class SCDirectedArc;
class SCCalendar;

extern std::vector<SCPlace*> g_allPlaces;
extern double g_time;
extern SCCalendar g_eventCal;

int Run();
void SetSimulationLength(double length);
int PlToTr(SCPlace *start,SCTransition *end, SCDirectedArc *arc);
int TrToPl(SCTransition *start,SCPlace *end, SCDirectedArc *arc);
void printStat();
int getSizeInt(int i);
int maxPlaceCao();
