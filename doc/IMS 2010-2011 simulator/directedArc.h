/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     derectedArc.h
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#pragma once
#include "statusList.h"
#include "coreFunc.h"
#include <iostream>
#include <stdio.h>
using namespace std;

class SCBase;
//todo dorobit inhibicnu hranu v pripade potreby
class SCDirectedArc
{
private:
	//members
	SCBase *m_target;							//target place/transition
	SCBase *m_start;							//start place/transition
	int m_status;								//status
	int m_inhib;								//inhib. arc - not implemented
	unsigned int m_weight;						//current weight
	unsigned int m_id;							//id
	string m_name;								//name
public:
	//methods
	string GetName();							//returns name
	void SetName(string name);					//sets name
	unsigned int GetId();						//returns Id
	int SetTarget(SCBase *target);				//Sets Target place/transition of current arc
	int SetStart(SCBase *start);				//Sets Start place/transition of current arc
	int SetArgWeight(unsigned int weight);		//Sets weight of current arc
	unsigned int GetArgWeight();				//returns current weight
	//int SetArgInhib();						//inhib. arcs are not implemented
	int GetArgInhib();							//inhib. arcs are not implemented - default no value
	SCBase* GetTarget();						//returns target place/transition
	SCBase* GetStart();							//returns start place/transition
	int GetStatus();							//returns current status
	SCDirectedArc();							//constructor
	~SCDirectedArc();							//destructor
};
