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
	unsigned short m_timeType;
	unsigned int m_priority;
	double m_time;
	double m_timeEnd;
	double m_probability;
	//methods
public:
	unsigned int GetTotalPassed();
	unsigned int GetPriority();
	unsigned int GetProbability();
	unsigned short GetTimeType();
	double GetTime();
	virtual double GetExactTime();
	virtual int Run();
	virtual bool IsReadyToRun();
	virtual SSBaseData* GetData();
	int SetArgPrio(unsigned int prio);
	int SetArgTime(double time, unsigned short type = TIME_ABS);
	int SetArgTime(double from,double to,unsigned short type = TIME_NORM);
	int SetArgProbability(double probability);
	int GetStatus();
	SCTransition();
	virtual ~SCTransition();
};
