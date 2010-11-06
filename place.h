#pragma once

#include "coreFunc.h"
#include <vector>
#include "statusList.h"
#include "base.h"
#include "transPrioData.h"

#include <string.h>

class SCPlace : SCBase
{
protected:
	//members
	unsigned int m_capacity;
	unsigned int m_value;
public:
	//methods
	virtual int Run();
	virtual SSBaseData GetData();
	virtual int Action(int code, int param = 1);
	int SetArgCapacity(unsigned int capacity);
	int SetArgStartVal(unsigned int startVal);
	SCPlace();
	virtual ~SCPlace();
};
