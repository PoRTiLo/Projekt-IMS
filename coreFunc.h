#pragma once
#include <vector>

class SCTransition;
class SCPlace;
class SCDirectedArc;

extern std::vector<SCPlace*> g_allPlaces;

int Run();
int PlToTr(SCPlace *start,SCTransition *end, SCDirectedArc *arc);
int TrToPl(SCTransition *start,SCPlace *end, SCDirectedArc *arc);
void printStat();
int getSizeInt(int i);
int maxPlaceCao();
