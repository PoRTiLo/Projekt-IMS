/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     transition.cpp
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#include "transition.h"
#include "calendar.h"

SCTransition::SCTransition()
{
	g_allTrans.push_back(this);
	this->m_timeType = TIME_ABS;
	this->m_priority = 0;
	this->m_probability = 0;
	this->m_time = 0;
	this->m_totalIn = 0;
	this->m_totalOut = 0;
	this->m_status = TRANSITION_OK;
	this->m_id  = g_transIndex++;
	this->m_timeEnd = 0;
	char buff[30];
	sprintf(buff,"Transition %d",this->m_id);
	this->m_name = buff;
}
SCTransition::~SCTransition()
{
}
unsigned int SCTransition::GetTotalPassedOut()
{
	return this->m_totalOut; //TODO: not implemented yet
}
unsigned int SCTransition::GetTotalPassedIn()
{
	return this->m_totalIn;
}
unsigned int SCTransition::GetPriority()
{
	return this->m_priority;
}
unsigned int SCTransition::GetProbability()
{
	return this->m_probability;
}
unsigned short SCTransition::GetTimeType()
{
	return this->m_timeType;
}
double SCTransition::GetTime()
{
	return this->m_time;
}
int SCTransition::SetArgPrio(unsigned int prio)
{
	if(this->m_probability == 0 && this->m_time == 0)
	{
		this->m_priority = prio;
		this->m_status = TRANSITION_OK;
	}
	else
	{
		this->m_status = TRANSITION_BAD_ARGS;
	}
	return this->m_status;
}
int SCTransition::SetArgProbability(double probability)
{
	if(this->m_priority == 0 && this->m_time == 0 && probability <= 100)
	{
		this->m_probability = probability;
		this->m_status = TRANSITION_OK;
	}
	else
	{
		this->m_status = TRANSITION_BAD_ARGS;
	}
	return this->m_status;
}
int SCTransition::SetArgTime(double time, unsigned short type)
{
	if(this->m_priority == 0 && this->m_probability == 0)
	{
		this->m_timeType = type;
		this->m_time = time;
		this->m_timeEnd = time;
		this->m_status = TRANSITION_OK;
	}
	else
	{
		this->m_status = TRANSITION_BAD_ARGS;
	}
	return this->m_status;
}
int SCTransition::SetArgTime(double from,double to,unsigned short type)
{
	if(this->m_priority == 0 && this->m_probability == 0)
	{
		this->m_timeType = type;
		this->m_time = from;
		this->m_timeEnd = to;
		this->m_status = TRANSITION_OK;
	}
	else
	{
		this->m_status = TRANSITION_BAD_ARGS;
	}
	return this->m_status;
}
bool SCTransition::IsReadyToRun()
{
	SSBaseData *data;
	bool status = true;
	vector<SCDirectedArc*>::iterator it;
	for(it = this->m_directedArcsFrom.begin();it<this->m_directedArcsFrom.end();it++)
	{
		data = (*it)->GetStart()->GetData();
		unsigned int value = 0;
		if(data->mode != PLACE_CAP)
		{
			this->m_status = TRANSITION_BAD_DATA;
			return false;
		}
		memcpy(&value,data->data,sizeof(int));
		if((value < (*it)->GetArgWeight()) && (*it)->GetArgInhib() == DIRECTEDARC_DEFAULT)
		{
			status = false;
			break;
		}
		else if(value != 0 && (*it)->GetArgInhib() == DIRECTEDARC_INHIB)
		{
			status = false;
			break;
		}
	}
	if(status)
	{
		for(it=this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
		{
			data = (*it)->GetTarget()->GetData();
			unsigned int value = 0;
			unsigned int capacity = 0;
			if(data->mode != PLACE_CAP)
			{
				this->m_status = TRANSITION_BAD_DATA;
				return false;
			}
		//	int a = sizeof(unsigned int);
			memcpy(&value,data->data,sizeof(int));
			memcpy(&capacity,data->data + sizeof(int),sizeof(int));
			if(capacity < (*it)->GetArgWeight() + value)
			{
				status = false;
				break;
			}
		}
	}
	return status;
}
double SCTransition::GetExactTime()
{
	double time = 0;
	if(this->m_time == 0)
	{
		return 0;
	}
	switch(this->m_timeType)
	{
	case TIME_ABS:
		time = g_time + this->m_time;
		break;
	case TIME_EXP:
		time = g_time + SCGen::GenExp(this->m_time);
		break;
	case TIME_POIS:
		time = g_time + SCGen::GenPoisson(this->m_time);
		break;
	case TIME_NORM:
		time = g_time + SCGen::GenGaus(this->m_time,this->m_timeEnd);
		break;
	}
	return time;
}
int SCTransition::Run()
{
	if(this->m_directedArcsTo.size() == 0)
	{
		this->m_status = TRANSITION_SIM_END;
	}
	else if(IsReadyToRun())
	{
		if(this->m_status == TRANSITION_OK)
		{
			vector<SCDirectedArc*>::iterator it;
			for(it = this->m_directedArcsFrom.begin();it<this->m_directedArcsFrom.end();it++)
			{
				if((*it)->GetStart()->Action(ACTION_TAKE,(*it)->GetArgWeight()) != PLACE_TAKEN)
				{
					this->m_status = TRANSITION_ACTION_FAIL;
					return this->m_status;
				}
				this->m_totalIn++;
				if( g_print == true )
					cout << " po provedeni prechodu '" << this->m_name << "'" << " hranou: '" << (*it)->GetName() << "'." << endl;
			}
			for(it=this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
			{
				if((*it)->GetTarget()->Action(ACTION_RETURN,(*it)->GetArgWeight()) != PLACE_RETURNED)
				{
					this->m_status = TRANSITION_ACTION_FAIL;
					return this->m_status;
				}
				this->m_totalOut++;
				if( g_print == true )
					cout << " po provedeni prechodu '" << this->m_name << "'" << " hranou: '" << (*it)->GetName() << "'." << endl;
				(*it)->GetTarget()->Run();
			}
			if(this->m_directedArcsFrom.empty() && this->m_time != 0)
			{
				g_eventCal.Insert(this,this->GetExactTime());
			}
		}
	}
	else
	{
		return TRANSITION_NOT_RUN;
	}
	return this->m_status;
}
SSBaseData* SCTransition::GetData()
{
	this->m_data.mode = BASE_DEFAULT;
	if(this->m_status == TRANSITION_OK)
	{

		if(this->m_time != 0)
		{
			this->m_data.mode = TRANSITION_WAIT;
			memcpy(this->m_data.data,&this->m_time,sizeof(double));
		}
		else if(this->m_priority != 0)
		{
			this->m_data.mode = TRANSITION_PRIO;
			memcpy(this->m_data.data,&this->m_priority,sizeof(int));
		}
		else if(this->m_probability != 0)
		{
			this->m_data.mode = TRANSITION_PROBAB;
			memcpy(this->m_data.data,&this->m_probability,sizeof(double));
		}
		else if(this->m_probability == 0 && this->m_priority == 0 && this->m_time == 0)
		{
			this->m_data.mode = TRANSITION_NOPARAM;
		}
	}
	return &this->m_data;
}

