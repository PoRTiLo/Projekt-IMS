#pragma once

#include <vector>
#include "statusList.h"
#include "base.h"

#include <cstring>

class SCTransition : public SCBase
{
	//members
protected:
	unsigned short m_timeType;
	unsigned int m_priority;
	double m_time;
	double m_probability;
	//methods
public:
	virtual int Run();
	virtual bool IsReadyToRun();
	virtual SSBaseData* GetData();
	int SetArgPrio(unsigned int prio);
	int SetArgTime(double time, unsigned short type = TIME_ABS);
	int SetArgProbability(double probability);
	int GetStatus();
	SCTransition();
	virtual ~SCTransition();
};
