#pragma once

#include "coreFunc.h"
#include <vector>
#include "statusList.h"
#include "base.h"
#include "transPrioData.h"

#include <cstring>

class SCPlace : public SCBase
{
protected:
	//members
	unsigned int m_capacity;
	unsigned int m_value;
	unsigned int m_startVal;
	SCDirectedArc *m_lastCommited;
public:
	//methods
	SCDirectedArc* GetLastCommitedArc();
	void SetLastCommitedArc(SCDirectedArc *directedArc);
	int Compare(SCPlace *place);
	virtual int Run();
	virtual SSBaseData* GetData();
	virtual int Action(int code, int param = 1);
	int SetArgCapacity(unsigned int capacity);
	int SetArgStartVal(unsigned int startVal);
	unsigned int GetArgCapacity();
	unsigned int GetArgCurrentVal();
	unsigned int GetArgStartVal();
	SCPlace();
	virtual ~SCPlace();
};
