#include "coreFunc.h"
#include "place.h"

std::vector<SCPlace*> g_allPlaces;

int Run()
{
	vector<SCPlace*>::iterator it;
	int result;
	while(1)
	{
		result = PLACE_EMPTY;
		for(it=g_allPlaces.begin();it!=g_allPlaces.end();it++)
		{
			int partialResult = (*it)->Run();
			if(partialResult == PLACE_SUCC)
			{
				result = partialResult;
			}
		}
		if(result == PLACE_EMPTY)
		{
			break;
		}
		//todo - dorobit zaciatok simulacie a vyhdzovanie sa z vectoru v placech v pripade 0 guliciek
	}
	return 0;
}