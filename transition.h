#pragma once

#include <vector>
#include "statusList.h"
#include "base.h"

#include <string.h>

class SCTransition : SCBase
{
	//members
protected:
	unsigned int m_priority;
	double m_time;
	double m_probability;
	//methods
public:
	virtual int Run();
	virtual SSBaseData GetData();
	int SetArgPrio(unsigned int prio);
	int SetArgTime(double time);
	int SetArgProbability(double probability);
	int GetStatus();
	SCTransition();
	virtual ~SCTransition();
};
