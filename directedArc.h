#pragma once
#include "statusList.h"

class SCBase;
//todo dorobit inhibicnu hranu
class SCDirectedArc
{
private:
	SCBase *m_target;
	SCBase *m_start;
	int m_status;
	int m_inhib;
	unsigned int m_weight;
public:
	int SetTarget(SCBase *target);
	int SetStart(SCBase *start);
	int SetArgWeight(unsigned int weight);
	int GetArgWeight();
	int SetArgInhib();
	int GetArgInhib();
	SCBase* GetTarget();
	SCBase* GetStart();
	int GetStatus();
	SCDirectedArc();
	~SCDirectedArc();
};