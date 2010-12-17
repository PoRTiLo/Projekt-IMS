/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     transition.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once

#include <vector>
#include "statusList.h"
#include "base.h"
#include "coreFunc.h"

#include <cstring>
class SCTransition : public SCBase
{
	//members
protected:
	int m_timeType;
	unsigned int m_priority;
	unsigned int m_totalOut;
	unsigned int m_totalIn;
	double m_time;
	double m_timeEnd;
	double m_probability;
	//methods
public:
	bool CheckZeroTimeLoop();
	unsigned int GetTotalPassedIn();
	unsigned int GetTotalPassedOut();
	unsigned int GetPriority();
	double GetProbability();
	unsigned short GetTimeType();
	double GetTime();
	double GetTimeEnd();
	virtual double GetExactTime();
	virtual int Run();
	virtual bool IsReadyToRun();
	virtual SSBaseData* GetData();
	int SetArgPrio(unsigned int prio);
	int SetArgTime(double time, int type = TIME_ABS);
	int SetArgTime(double from,double to,int type = TIME_NORM);
	int SetArgProbability(double probability);
	int GetStatus();
	SCTransition();
	virtual ~SCTransition();
};
