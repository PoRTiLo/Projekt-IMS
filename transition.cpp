#include "transition.h"

SCTransition::SCTransition()
{
	this->m_priority = 0;
	this->m_probability = 0;
	this->m_time = 0;
	this->m_status = TRANSITION_OK;
}
SCTransition::~SCTransition()
{
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
	if(this->m_priority == 0 && this->m_time == 0)
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
int SCTransition::SetArgTime(double time)
{
	if(this->m_priority == 0 && this->m_probability == 0)
	{
		this->m_time = time;
		this->m_status = TRANSITION_OK;
	}
	else
	{
		this->m_status = TRANSITION_BAD_ARGS;
	}
	return this->m_status;
}
int SCTransition::Run()
{
	if(this->m_directedArcsTo.size() > 1)
	{
		this->m_status = TRANSITION_UNCLEAR_PATH;
	}
	else if(this->m_directedArcsTo.size() == 0)
	{
		this->m_status = TRANSITION_SIM_END;
	}
	if(this->m_status == TRANSITION_OK)
	{
		if(this->m_time != 0)
		{
			//wait m_time
		}
		vector<SCDirectedArc*>::iterator it;
		for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
		{
			//prevedie sa iba raz
			(*it)->GetTarget()->Run();
		}
	}
	return this->m_status;
}
SSBaseData SCTransition::GetData()
{
	SSBaseData data;
	data.mode = BASE_DEFAULT;
	if(this->m_status == TRANSITION_OK)
	{

		if(this->m_time != 0)
		{
			data.mode = TRANSITION_WAIT;
		}
		else if(this->m_priority != 0)
		{
			data.mode = TRANSITION_PRIO;
			memcpy(&data.data,&this->m_priority,sizeof(int));
		}
		else if(this->m_probability != 0)
		{
			data.mode = TRANSITION_PROBAB;
			memcpy(&data.data,&this->m_probability,sizeof(double));
		}
		else if(this->m_probability == 0 && this->m_priority == 0 && this->m_time == 0)
		{
			data.mode = TRANSITION_NOPARAM;
		}
	}
	return data;
}