#pragma once
#include "statusList.h"
#include "coreFunc.h"
#include <iostream>
#include <stdio.h>
using namespace std;

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
	unsigned int m_id;
	string m_name;
public:
	string GetName();
	void SetName(string name);
	unsigned int GetId();
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
