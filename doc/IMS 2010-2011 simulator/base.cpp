/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     base.cpp
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#include "base.h"
void SCBase::SetProbabCallback(double probab)
{
}
SSBaseData* SCBase::GetData()
{
	return &this->m_data;
}
int SCBase::GetStatus()
{
	return this->m_status;
}
bool SCBase::IsReadyToRun()
{
	return false;
}
string SCBase::GetName()
{
	return this->m_name;
}
void SCBase::SetName(string name)
{
	this->m_name = name;
}
int SCBase::AddDirectedArcFrom(SCDirectedArc *directedArc)
{
	if(directedArc != NULL)
	{
		directedArc->SetTarget(this);
		this->m_directedArcsFrom.push_back(directedArc);
	}
	else
	{
		this->m_status = BASE_NULL_ARG;
	}
	return this->m_status;
}
int SCBase::AddDirectedArcTo(SCDirectedArc *directedArc)
{
	if(directedArc != NULL)
	{
		directedArc->SetStart(this);
		this->m_directedArcsTo.push_back(directedArc);
	}
	else
	{
		this->m_status = BASE_NULL_ARG;
	}
	return this->m_status;
}
double SCBase::GetExactTime()
{
	return g_time;
}
int SCBase::Run()
{
	return BASE_OK;
}
int SCBase::Action(int code,int param)
{
	return BASE_OK;
}
vector<SCDirectedArc*>* SCBase::GetDirectedArcsFrom()
{
	return &this->m_directedArcsFrom;
}
vector<SCDirectedArc*>* SCBase::GetDirectedArcsTo()
{
	return &this->m_directedArcsTo;
}
SCBase::SCBase()
{
	memset(&m_data.data,0,8);
	this->m_name = "Base default name, do not use this class!";
	this->m_id = 0;
	this->m_status = BASE_OK;
	this->m_lastCommited = NULL;
}
SCBase::~SCBase()
{
}
unsigned int SCBase::GetId()
{
	return this->m_id;
}
SCDirectedArc* SCBase::GetLastCommitedArc()
{
	return this->m_lastCommited;
}
void SCBase::SetLastCommitedArc(SCDirectedArc* directedArc)
{
	this->m_lastCommited = directedArc;
}
/*static*/int SCBase::EvaluateErrorCode(int code,SCBase* subject)
{
	int ret = BASE_OK;
	switch(code)
	{
		case BASE_FATAL:
			ret = BASE_FATAL;
			break;
		case TRANSITION_BAD_DATA:
			cout<<endl<<"MODEL RUNTIME ERROR: Unexpected data arrived: Check model !!!" <<endl;
			ret = BASE_FATAL;
			break;
		case TRANSITION_BAD_ARGS:
			if(subject != NULL)
				cout<<endl<<"MODEL RUNTIME ERROR: Unexpected parameters for transition name: "<<subject->GetName().c_str()<<", Check model !!!" <<endl;
			else
				cout<<endl<<"MODEL RUNTIME ERROR: Unexpected parameters for transition, Check model !!!" <<endl;
			ret = BASE_FATAL;
			break;
		case RUNTIME_TRANSITION_CRASH:
			if(subject != NULL)
				cout<<endl<<"MODEL RUNTIME ERROR: Bad transition combination for place name: "<<subject->GetName().c_str()<<", Check model !!!" <<endl;
			else
				cout<<endl<<"MODEL RUNTIME ERROR: Bad transition combination for place, Check model !!!" <<endl;
			ret = BASE_FATAL;
			break;
		case RUNTIME_TRANS_PROB_LIMIT:
			if(subject != NULL)
				cout<<endl<<"MODEL RUNTIME ERROR: The sum of transition probabilities for place name: "<<subject->GetName().c_str()<<" is more then 100%, Check model !!!" <<endl;
			else
				cout<<endl<<"MODEL RUNTIME ERROR: The sum of transition probabilities is more then 100%, Check model !!!" <<endl;
			ret = BASE_FATAL;
			break;
		case RUNTIME_TRANS_PROB_LOW:
			if(subject != NULL)
				cout<<endl<<"MODEL RUNTIME ERROR: The sum of transition probabilities for place name: "<<subject->GetName().c_str()<<" is not 100%, Check model !!!" <<endl;
			else
				cout<<endl<<"MODEL RUNTIME ERROR: The sum of transition probabilities is not 100%, Check model !!!" <<endl;
			ret = BASE_FATAL;
			break;
		case PLACE_SIM_END:
		case PLACE_EMPTY:
		case TRANSITION_SIM_END:
		case TRANSITION_NOT_RUN:
		case TRANSITION_ACTION_FAIL:
		default:
			ret = BASE_OK;
	}
	return ret;
}
bool SCBase::IsCycle(vector<SCBase*> *base)
{
	vector<SCBase*>::iterator itB;
	for(itB = base->begin(); itB < base->end(); itB++)
	{
		if(this == *itB)
			return true;
	}
	
	base->push_back(this);
	SSBaseData* data = NULL;
	data = this->GetData();
	bool ret = false;

	if(data != NULL)
	{
		vector<SCDirectedArc*>::iterator it;
		double time = 0;
		switch(data->mode)
		{
		case  TRANSITION_WAIT:
			memcpy(&time,data->data,sizeof(double));
			if(time != 0)
			{
				return false;
			}
		case TRANSITION_PROBAB:
		case TRANSITION_PRIO:
		case TRANSITION_NOPARAM:
		case PLACE_CAP:
			break;
		}
	}
	vector<SCDirectedArc*>::iterator it;
	for(it = this->m_directedArcsTo.begin(); it < this->m_directedArcsTo.end(); it++)
	{
		if((*it)->GetTarget()->IsCycle(base))
		{
			ret = true;
			break;
		}
	}
	return ret;
}