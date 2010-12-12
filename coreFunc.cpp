#include <iostream>
#include <iomanip>
#include "coreFunc.h"
#include "place.h"
#include "transition.h"
#include "directedArc.h"
#include "calendar.h"
#include <limits.h>


#include <stdio.h>
std::vector<SCPlace*> g_allPlaces;
std::vector<SCTransition*> g_allTrans;
SCCalendar g_eventCal;
double g_time = 0;
double g_simLength = 0;
unsigned int g_transIndex = 0;
unsigned int g_placeIndex = 0;
unsigned int g_arcIndex = 0;

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

void PrintStat() {

	PrintMain();
	PrintPlace();
	PrintTransition();
	PrintDirected();
}

void PrintMain() {

	cout << "******************************** STATISTIKY *****************************" << endl;
	cout << "*       C" <<endl;
	cout << "*       E        Pocet mist     : " << g_allPlaces.size() << endl;
	cout << "*       L        Pocet prechodu : " << endl;
	cout << "*       K        Pocet hran     : " << endl;
	cout << "*       E" <<endl;
	cout << "*       M        Doba trvani simulace : " <<endl;
	cout << "*" <<endl;
}

void PrintPlace() {

	int sizePlace = GetSizeInt(g_allPlaces.size()) + 3;

	unsigned int sizeCap = GetSizeInt( MaxPlaceCapacity() );
	unsigned int sizeVal = GetSizeInt( MaxPlaceStartValue() );
	unsigned int sizeName =  MaxPlaceName();
	unsigned int sizeEnd = GetSizeInt(1);
	unsigned int sizeCount = GetSizeInt(1);
	char capacity[15] = "kapacita";
	if( sizeCap < strlen(capacity) )
		sizeCap = strlen(capacity);
	char value[30] = "konecny stav kulicek";
	if( sizeVal < strlen(value) )
		sizeVal = strlen(value); 
	char name[30] = "jmeno";
	if( sizeName < strlen(name) )
		sizeName = strlen(name); 
	char end[30] = "pocatecni stav";
	if( sizeEnd < strlen(end) )
		sizeEnd = strlen(end); 
	char count[30] = "celkem kulicek";
	if( sizeCount < strlen(count) )
		sizeCount = strlen(count); 
	unsigned int size = sizeCap + sizeVal + sizeName + sizeEnd + sizeCount + 7 + 11 + 6;
	unsigned int sizeHalf = size/2;

	cout << "* " << setfill('-') << setw(sizeHalf) << "" << " mista " << setw(sizeHalf) << "" << endl;
	cout << "*" << endl;
	cout << "*        " << setfill(' ') << setw(sizePlace) << "." << " | " 
						<< setw(sizeName) << name << " | " 
	               << setw(sizeCap) << capacity << " | " 
						<< setw(sizeVal) << value << " | " 
						<< setw(sizeEnd) << end << " | "
						<< setw(sizeCount) << count << endl;
	cout << "*       " << setw(sizePlace) << " " << setfill('.') << setw(size-sizePlace) << "." << endl;

	char p[10] = "MISTA ";
	unsigned int k = 0;

	for(unsigned int i = 1; i != g_allPlaces.size(); i++ )
	{
		cout << "*       "<< p[k] << setfill(' ') << setw(sizePlace) << i << " | " 
		                     << setw(sizeName) << g_allPlaces[i]->GetName() << " | "
									<< setw(sizeCap) << g_allPlaces[i]->GetArgCapacity() << " | "
									<< setw(sizeVal) << g_allPlaces[i]->GetArgCurrentVal() <<" | " 
									<< setw(sizeEnd) << g_allPlaces[i]->GetArgStartVal() << " | " 
									<< setw(sizeCount) << " " << endl;
		if( k < 5 )
			k++;
		else if( i > 8 )
			k = 5;
	}

	if( strlen(p) > g_allPlaces.size() )
	{
		for(;k<strlen(p)-1;k++)
		{
			cout << "*       "<< p[k] << endl;
		}
	}

	cout << "*" <<endl;
}

void PrintTransition() {

	unsigned int sizePri = GetSizeInt(1);
	unsigned int sizeTime = GetSizeInt(1);
	unsigned int sizeInh = GetSizeInt(1);
	unsigned int sizePro = GetSizeInt(1);
	unsigned int sizeCount = GetSizeInt(1);
	unsigned int sizeName =  MaxPlaceName();
	char priority[15] = "priorita";
	if( sizePri < strlen(priority) )
		sizePri = strlen(priority);
	char time[30] = "cas zpozdeni";
	if( sizeTime < strlen(time) )
		sizeTime = strlen(time); 
	char inhi[30] = "inhibicni prechod";
	if( sizeInh < strlen(inhi) )
		sizeInh = strlen(inhi); 
	char probability[30] = "pravdepodobnost";
	if( sizePro < strlen(probability) )
		sizePro = strlen(probability); 
	char count[10] = "pocet";
	if( sizeCount < strlen(count) )
		sizeCount = strlen(count);
	char name[30] = "jmeno";
	if( sizeName < strlen(name) )
		sizeName = strlen(name);

	int sizeT = sizeName + sizePri + sizeTime + sizeInh + sizePro + sizeCount + 6 + 11 + 6;
	cout << "* " << setfill('-') << setw((sizeT-2)/2) << "" << " prechody " << setw((sizeT-1)/2) << "" << endl;
	int size= sizeCount;
	cout << "*" << endl;
	cout << "*        " << setfill(' ') << setw(size) << "." << " | " 
						<< setw(sizeName) << name << " | " 
	               << setw(sizePri) << priority << " | " 
						<< setw(sizeTime) << time << " | " 
						<< setw(sizeInh) << inhi << " | "
						<< setw(sizePro) << probability << " | "
						<< setw(sizeCount) << count << endl;
	cout << "*       " << setw(size) << " " << setfill('.') << setw(sizeT-2) << "." << endl;
	char p1[13] = "PRECHOD  ";
	unsigned int k = 0;
	for(unsigned int i = 1; i != g_allPlaces.size(); i++ )
	{
		cout << "*       "<< p1[k] << setfill(' ') << setw(size) << "." << " | " 
								<< setw(sizeName) << name << " | " 
	               		<< setw(sizePri) << priority << " | " 
								<< setw(sizeTime) << time << " | " 
								<< setw(sizeInh) << inhi << " | "
								<< setw(sizePro) << probability << " | "
								<< setw(sizeCount) << count << endl;
		if( k < 6 )
			k++;
		else if( i > 7 )
			k = 7;

	}
	if( strlen(p1) > g_allPlaces.size() )
	{
		for(;k<strlen(p1)-1;k++)
		{
			cout << "*       "<< p1[k] << endl;
		}
	}
	cout << "*" <<endl;
}

void PrintDirected() {

	unsigned int sizeWeight = GetSizeInt(1);
	unsigned int sizeName = MaxPlaceName();
	int sizeCount = (GetSizeInt(g_allPlaces.size()) + 3);///TODO-pocet prechodu
	char weight[15] = "vaha";
	if( sizeWeight < strlen(weight) )
		sizeWeight = strlen(weight);
	char name[30] = "jmeno";
	if( sizeName < strlen(name) )
		sizeName = strlen(name);
	int sizeD = sizeName + sizeWeight + 6 + 11 + 6;
	cout << "* " << setfill('-') << setw((sizeD-2)/2) << "" << " hrany " << setw((sizeD-1)/2) << "" << endl;
	cout << "*" << endl;
	cout << "*        " << setfill(' ') << setw(sizeCount) << "." << " | " 
						<< setw(sizeName) << name << " | " 
	               << setw(sizeWeight) << weight << endl; 
	cout << "*       "<<setw(sizeCount) <<"" << setfill('.') << setw(sizeD - sizeCount-10) << "." << endl;
	char p[13] = "HRANA  ";
	unsigned int k = 0;

	for(unsigned int i = 1; i != g_allPlaces.size(); i++ )
	{
		cout << "*       "<< p[k] << setfill(' ') << setw(sizeCount) << "." << " | " 
								<< setw(sizeName) << name << " | " 
	               		<< setw(sizeWeight) << weight << endl;
		if( k < 4 )
			k++;
		else if( i > 5 )
			k = 5;

	}
	if( strlen(p) > g_allPlaces.size() )
	{
		for( ; k<strlen(p)-1; k++)
		{
			cout << "*       "<< p[k] << endl;
		}
	}
	cout << "*" <<endl;
}

unsigned int GetSizeInt( unsigned int i ) {

	char num[30];
	sprintf(num, "%u", i);
	return strlen(num);
}

int MaxPlaceCapacity() {
	unsigned int size = g_allPlaces[1]->GetArgCapacity();
	for( unsigned int i = 2; i < g_allPlaces.size(); i++ )
	{
		if( size <= g_allPlaces[i]->GetArgCapacity() )
			size = g_allPlaces[i]->GetArgCapacity();
	}
	return size;
}

int MaxPlaceStartValue() {

	unsigned int size = g_allPlaces[1]->GetArgCurrentVal();
	for( unsigned int i = 2; i < g_allPlaces.size(); i++ )
	{
		if( size < g_allPlaces[i]->GetArgCurrentVal() )
			size = g_allPlaces[i]->GetArgCurrentVal();
	}
	return size;
}

int MaxPlaceName() {

	unsigned int size = g_allPlaces[1]->GetName().size();
	for( unsigned int i = 2; i < g_allPlaces.size(); i++ )
	{
		if( size < g_allPlaces[i]->GetName().size() )
			size = g_allPlaces[i]->GetName().size();
	}
	return size;
}

