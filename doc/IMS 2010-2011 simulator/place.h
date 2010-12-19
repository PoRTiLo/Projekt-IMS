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
	//private methods
	int CommitTransNoParam();						//in case of no param transition group detected
	int CommitTransTime();							//in case of time transition group detected
	int CommitTransPrio();							//in case of priority transition group detected
	int CommitTransProbab();						//in case of probab. transition detected

protected:
	//members
	bool m_print;									//print stats yes/no
	unsigned int m_capacity;						//max capacity
	unsigned int m_value;							//current value
	unsigned int m_startVal;						//start value
	unsigned int m_total;							//total value passed
public:
	//methods
	bool CheckTransitions();						//check if this transition is not in inf. loop
	int Compare(SCPlace *place);					//compare
	virtual int Run();								//tryies to commit possible transitions		
	virtual SSBaseData* GetData();					//returns data - type,value,capacity
	virtual int Action(int code, int param = 1);	//takes, adds marks to current place
	int SetArgCapacity(unsigned int capacity);		//sets max capacity
	int SetArgStartVal(unsigned int startVal);		//sets starting value
	void SetArgPrint( bool print );					//sets if print this place or not
	unsigned int GetArgCapacity();					//returns capacity
	unsigned int GetArgCurrentVal();				//returns current value of marks
	unsigned int GetArgStartVal();					//returns start number of marks
	unsigned int GetArgTotal();						//returns total value of marks passed
	bool IsPrint();									//returns print status	
	SCPlace();										//constructor
	virtual ~SCPlace();								//destructor
};
