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
	string m_name;														//name
	unsigned int m_id;													//uniq id
	int m_status;														//status
	vector<SCDirectedArc*> m_directedArcsFrom;							//arcs that direct to this object							
	vector<SCDirectedArc*> m_directedArcsTo;							//arcs that direct from this object
	SSBaseData m_data;													//data - depends on virtual method
	SCDirectedArc *m_lastCommited;										//last commited place/transition
public:
	//methods
	virtual void AddTransToCommit(SCTransition *tr);
	static int EvaluateErrorCode(int code,SCBase* subject = NULL);		//checks the error weight
	SCDirectedArc* GetLastCommitedArc();								//return last commited place/trans
	void SetLastCommitedArc(SCDirectedArc *directedArc);				//sets last commited place/trans
	string GetName();													//returns current name
	void SetName(string name);											//sets name
	unsigned int GetId();												//returns current id
	virtual double GetExactTime();										//returns exact time,the next event of this type ocures
	virtual int Run();													//tries to commit transition/place
	virtual void SetProbabCallback(double probab);						//sets probabiliy for transitions with zero if they are in probability group
	virtual bool IsReadyToRun();										//checks if current place/transition is ready to run	
	virtual SSBaseData* GetData();										//returns data, depends on object type
	virtual int Action(int code, int param = 1);						//removes,add marks to current place- depends on parameter
	int GetStatus();													//returns status
	int AddDirectedArcFrom(SCDirectedArc *directedArc);					//adds arc to vector of all arcs that directs to this place/transition 
	int AddDirectedArcTo(SCDirectedArc *directedArc);					//adds arc to vector of all arcs that from to this place/transition 
	bool IsCycle(vector<SCBase*> *base);								//checks if this place/transition is in zero time loop
	vector<SCDirectedArc*>* GetDirectedArcsFrom();						//returns vector of all arcs that directs to this place/transition 
	vector<SCDirectedArc*>* GetDirectedArcsTo();						//returns vector of all arcs that directs from this place/transition 

	SCBase();															//constructor
	~SCBase();															//destructor
};
