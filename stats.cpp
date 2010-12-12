#include "stats.h"

#include "place.h"
#include "transition.h"
#include "directedArc.h"
#include "stats.h"

void SCStat::PrintStatAll() {

	PrintMain();
	PrintPlace();
	PrintTransition();
	PrintDirected();
}

void SCStat::PrintMain() {
	cout << endl << endl;
	cout << "******************************** STATISTIKY *****************************" << endl;
	cout << "*       C" <<endl;
	cout << "*       E        Pocet mist     : " << g_allPlaces.size() << endl;
	cout << "*       L        Pocet prechodu : " << g_allTrans.size() << endl;
	cout << "*       K        Pocet hran     : " << g_allDirected.size() << endl;
	cout << "*       E" <<endl;
	cout << "*       M        Doba trvani simulace : " <<endl;
	cout << "*" <<endl;
}

void SCStat::PrintPlace() {

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

	for(unsigned int i = 0; i != g_allPlaces.size(); i++ )
	{
		cout << "*       "<< p[k] << setfill(' ') << setw(sizePlace) << i+1 << " | " 
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

void SCStat::PrintTransition() {

	unsigned int sizePri = GetSizeInt( MaxTransitionPriority() );
	unsigned int sizeTime = 0;
	unsigned int sizePro = GetSizeInt( MaxTransitionProbability() );
	unsigned int sizeCount = GetSizeInt( MaxTransitionTotalPassed() );
	int sizeTrans = GetSizeInt(g_allTrans.size()) + 3;
	unsigned int sizeName =  MaxTransitionName();
	char priority[15] = "priorita";
	if( sizePri < strlen(priority) )
		sizePri = strlen(priority);
	char time[30] = "casovany prechod";
	if( sizeTime < strlen(time) )
		sizeTime = strlen(time); 
	char probability[30] = "pravdepodobnost";
	if( sizePro < strlen(probability) )
		sizePro = strlen(probability); 
	char count[19] = "pocet kulicek";
	if( sizeCount < strlen(count) )
		sizeCount = strlen(count);
	char name[30] = "jmeno";
	if( sizeName < strlen(name) )
		sizeName = strlen(name);

	int sizeT = sizeName + sizePri + sizeTime +  sizePro + sizeCount + 2 + 11 + 6;
	cout << "* " << setfill('-') << setw((sizeT-2)/2) << "" << " prechody " << setw((sizeT-1)/2) << "" << endl;
	cout << "*" << endl;
	cout << "*        " << setfill(' ') << setw(sizeTrans) << "." << " | " 
						<< setw(sizeName) << name << " | " 
	               << setw(sizePri) << priority << " | " 
						<< setw(sizeTime) << time << " | " 
						<< setw(sizePro) << probability << " | "
						<< setw(sizeCount) << count << endl;
	cout << "*       " << setw(sizeTrans) << " " << setfill('.') << setw(sizeT-2) << "." << endl;
	char p1[13] = "PRECHOD  ";
	unsigned int k = 0;
	for(unsigned int i = 0; i != g_allTrans.size(); i++ )
	{
		cout << "*       "<< p1[k] << setfill(' ') << setw(sizeTrans) << i+1 << " | " 
								<< setw(sizeName) << g_allTrans[i]->GetName() << " | " 
	               		<< setw(sizePri) << g_allTrans[i]->GetPriority() << " | " 
								<< setw(sizeTime) << GetTransitionTime(i) << " | " 
								<< setw(sizePro) << g_allTrans[i]->GetProbability() << " | "
								<< setw(sizeCount) << g_allTrans[i]->GetTotalPassed() << endl;
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

void SCStat::PrintDirected() {

	unsigned int sizeWeight = GetSizeInt( MaxDirectedWeight() );
	unsigned int sizeName = MaxDirectedName();
	int sizeCount = (GetSizeInt(g_allDirected.size()) + 3);
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

	for(unsigned int i = 0; i != g_allDirected.size(); i++ )
	{
		cout << "*       "<< p[k] << setfill(' ') << setw(sizeCount) << i+1 << " | " 
								<< setw(sizeName) << g_allDirected[i]->GetName() << " | " 
	               		<< setw(sizeWeight) << g_allDirected[i]->GetArgWeight() << endl;
		if( k < 5 )
			k++;
		else if( i > 6 )
			k = 6;
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

unsigned int SCStat::GetSizeInt( unsigned int i ) {

	char num[30];
	sprintf(num, "%u", i);
	return strlen(num);
}

int SCStat::MaxPlaceCapacity() {
	unsigned int size = g_allPlaces[0]->GetArgCapacity();
	for( unsigned int i = 1; i < g_allPlaces.size(); i++ )
	{
		if( size <= g_allPlaces[i]->GetArgCapacity() )
			size = g_allPlaces[i]->GetArgCapacity();
	}
	return size;
}

int SCStat::MaxTransitionPriority() {
	unsigned int size = g_allTrans[0]->GetPriority();
	for( unsigned int i = 1; i < g_allTrans.size(); i++ )
	{
		if( size <= g_allTrans[i]->GetPriority() )
			size = g_allTrans[i]->GetPriority();
	}
	return size;
}

int SCStat::MaxTransitionProbability() {
	unsigned int size = g_allTrans[0]->GetProbability();
	for( unsigned int i = 1; i < g_allTrans.size(); i++ )
	{
		if( size <= g_allTrans[i]->GetProbability() )
			size = g_allTrans[i]->GetProbability();
	}
	return size;
}

int SCStat::MaxTransitionTotalPassed() {
	unsigned int size = g_allTrans[0]->GetTotalPassed();
	for( unsigned int i = 1; i < g_allTrans.size(); i++ )
	{
		if( size <= g_allTrans[i]->GetTotalPassed() )
			size = g_allTrans[i]->GetTotalPassed();
	}
	return size;
}

int SCStat::MaxPlaceStartValue() {

	unsigned int size = g_allPlaces[0]->GetArgCurrentVal();
	for( unsigned int i = 1; i < g_allPlaces.size(); i++ )
	{
		if( size < g_allPlaces[i]->GetArgCurrentVal() )
			size = g_allPlaces[i]->GetArgCurrentVal();
	}
	return size;
}

int SCStat::MaxPlaceName() {

	unsigned int size = g_allPlaces[0]->GetName().size();
	for( unsigned int i = 1; i < g_allPlaces.size(); i++ )
	{
		if( size < g_allPlaces[i]->GetName().size() )
			size = g_allPlaces[i]->GetName().size();
	}
	return size;
}

int SCStat::MaxTransitionName() {

	unsigned int size = g_allTrans[0]->GetName().size();
	for( unsigned int i = 1; i < g_allTrans.size(); i++ )
	{
		if( size < g_allTrans[i]->GetName().size() )
			size = g_allTrans[i]->GetName().size();
	}
	return size;
}

string SCStat::GetTransitionTime( int i ) {

	string type;

	if( TIME_ABS == g_allTrans[i]->GetTimeType() )
		type = "";
	else if( TIME_EXP == g_allTrans[i]->GetTimeType() )
		type = "exp(";
	else if( TIME_POIS ==  g_allTrans[i]->GetTimeType() )
		type = "pois(";
	else if( TIME_NORM == g_allTrans[i]->GetTimeType() )
		type = "norm(";
	else
		type = "";

	if( type != "" )
		type += convertInt( g_allTrans[i]->GetTime() ) + ")";

	return type;
}

string SCStat::convertInt( int num ) {
	
	stringstream ss;
	ss << num;
	return ss.str();
}

int SCStat::MaxDirectedName() {

	unsigned int size = g_allDirected[0]->GetName().size();
	for( unsigned int i = 1; i < g_allDirected.size(); i++ )
	{
		if( size < g_allDirected[i]->GetName().size() )
			size = g_allDirected[i]->GetName().size();
	}
	return size;
}

int SCStat::MaxDirectedWeight() {

	unsigned int size = g_allDirected[0]->GetArgWeight();
	for( unsigned int i = 1; i < g_allDirected.size(); i++ )
	{
		if( size < g_allDirected[i]->GetArgWeight() )
			size = g_allDirected[i]->GetArgWeight();
	}
	return size;
}