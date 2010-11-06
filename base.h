#pragma once

#include <vector>
#include "directedArc.h"
#include "statusList.h"
#include "baseData.h"

using namespace std;

class SCBase
{
protected:
	//members
	int m_status;
	vector<SCDirectedArc*> m_directedArcsFrom;
	vector<SCDirectedArc*> m_directedArcsTo;
public:
	//methods
	virtual int Run();
	virtual SSBaseData GetData();
	virtual int Action(int code, int param = 1);
	int GetStatus();
	int AddDirectedArcFrom(SCDirectedArc *directedArc);
	int AddDirectedArcTo(SCDirectedArc *directedArc);
	vector<SCDirectedArc*>* GetDirectedArcsFrom();

	SCBase();
	~SCBase();
};