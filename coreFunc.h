#pragma once
#include <vector>


class SCTransition;
class SCPlace;
class SCDirectedArc;
class SCCalendar;

extern std::vector<SCPlace*> g_allPlaces;
extern double g_time;
extern SCCalendar g_eventCal;
extern unsigned int g_transIndex;
extern unsigned int g_placeIndex;
extern unsigned int g_arcIndex;

int Run();
void SetSimulationLength(double length);
int PlToTr(SCPlace *start,SCTransition *end, SCDirectedArc *arc);
int TrToPl(SCTransition *start,SCPlace *end, SCDirectedArc *arc);
void PrintStat();
unsigned int GetSizeInt(unsigned int i);
int MaxPlaceCapacity();
int MaxPlaceStartValue();
int MaxPlaceName();
void PrintMain();
void PrintPlace();
void PrintTransition();
void PrintDirected();
