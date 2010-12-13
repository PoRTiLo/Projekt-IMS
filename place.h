/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     place.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once

#include "coreFunc.h"
#include <vector>
#include "statusList.h"
#include "base.h"
#include "transPrioData.h"

#include <cstring>

class SCPlace : public SCBase
{
private:
	void CommitTransNoParam();
	void CommitTransTime();
	void CommitTransPrio();
	void CommitTransProbab();

protected:
	//members
	bool m_print;
	unsigned int m_capacity;
	unsigned int m_value;
	unsigned int m_startVal;
	unsigned int m_total;
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
	void SetArgPrint( bool print );
	unsigned int GetArgCapacity();
	unsigned int GetArgCurrentVal();
	unsigned int GetArgStartVal();
	unsigned int GetArgTotal();
	bool IsPrint();
	SCPlace();
	virtual ~SCPlace();
};
