#pragma once

#ifndef STATS_H__
#define STATS_H__
#include "coreFunc.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <iomanip>

using namespace std;

class SCStat
{
	private:
		static unsigned int GetSizeInt(unsigned int i);
		static int MaxPlaceCapacity();
		static int MaxPlaceStartValue();
		static int MaxPlaceName();
		static int MaxTransitionProbability();
		static int MaxTransitionPriority();
		static int MaxTransitionName();
		static int MaxTransitionTotalPassed();
		static string GetTransitionTime( int i );
		static string convertInt( int num );
		static int MaxDirectedName();
		static int MaxDirectedWeight();
	public:
		SCStat(){}

		~SCStat(){}
		static void PrintStatAll();
		static void PrintMain();
		static void PrintPlace();
		static void PrintTransition();
		static void PrintDirected();
};
#endif //STATS_H__
