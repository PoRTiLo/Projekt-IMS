/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     base.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once

#include <vector>
#include "coreFunc.h"
#include "directedArc.h"
#include "statusList.h"
#include "baseData.h"
#include "gen.h"
#include <cstring>
using namespace std;

class SCBase
{
protected:
	//members
	string m_name;
	unsigned int m_id;
	int m_status;
	vector<SCDirectedArc*> m_directedArcsFrom;
	vector<SCDirectedArc*> m_directedArcsTo;
	SSBaseData m_data;
	SCDirectedArc *m_lastCommited;
public:
	//methods
	SCDirectedArc* GetLastCommitedArc();
	void SetLastCommitedArc(SCDirectedArc *directedArc);
	string GetName();
	void SetName(string name);
	unsigned int GetId();
	virtual double GetExactTime();
	virtual int Run();
	virtual bool IsReadyToRun();
	virtual SSBaseData* GetData();
	virtual int Action(int code, int param = 1);
	int GetStatus();
	int AddDirectedArcFrom(SCDirectedArc *directedArc);
	int AddDirectedArcTo(SCDirectedArc *directedArc);
	vector<SCDirectedArc*>* GetDirectedArcsFrom();

	SCBase();
	~SCBase();
};
