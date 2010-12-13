/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     place.cpp
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#include "place.h"
#include "calendar.h"
#include <set>

SCPlace::SCPlace()
{
	g_allPlaces.push_back(this);
	this->m_startVal = 0;
	this->m_capacity = UINT_MAX;
	this->m_value = 0;
	this->m_status = PLACE_OK;
	this->m_lastCommited = NULL;
	this->m_id = g_placeIndex++;
	char buff[25];
	sprintf(buff,"Place %d",this->m_id);
	this->m_name = string(buff);
}
SCPlace::~SCPlace()
{
}
int SCPlace::SetArgCapacity(unsigned int capacity)
{
	this->m_capacity = capacity;
	return this->m_status;
}
int SCPlace::SetArgStartVal(unsigned int startValue)
{
	this->m_startVal = startValue;
	this->m_value = startValue;
	g_eventCal.Insert(this,g_time);
	return this->m_status;
}
int SCPlace::Run()
{
	if(this->m_directedArcsTo.size() == 0)
	{
		return PLACE_SIM_END;
	}
	if(this->m_value <= 0)
	{
		return PLACE_EMPTY;
	}
	int ret = PLACE_SUCC;
	int currentMode = TRANSITION_DEFAULT;
	if(this->m_status == PLACE_OK)
	{
		vector<SCDirectedArc*>::iterator it;
		for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
		{
			SSBaseData *data = (*it)->GetTarget()->GetData();
			if(data->mode != TRANSITION_NOPARAM)
			{	
				if(currentMode != data->mode && (currentMode != TRANSITION_DEFAULT || currentMode != TRANSITION_NOPARAM || currentMode != TRANSITION_PRIO))
				{
					this->m_status = RUNTIME_TRANSITION_CRASH;
					ret = PLACE_FAIL;
					break;
				}
				currentMode = data->mode;
			}
			else if(data->mode == TRANSITION_NOPARAM && currentMode == TRANSITION_DEFAULT)  
			{
				currentMode = data->mode;
			}
		}
		if(this->m_status != RUNTIME_TRANSITION_CRASH)
		{
			//todo specifikovat pre paramtery sipky
			switch(currentMode)
			{
			case TRANSITION_WAIT:
				{
					double genNonDetNum = SCGen::GenNomInterval();
					vector<SCDirectedArc*>::iterator it;
					bool done = false;
					vector<SCBase*> nullTimeVec;
					//najde nulovy cas
					for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
					{
						SSBaseData *data;
						data = (*it)->GetTarget()->GetData();
						double time = 0;
						if(data->mode != TRANSITION_WAIT)
						{
							this->m_status = TRANSITION_BAD_DATA;
							ret = PLACE_FAIL;
							break;
						}
						else
						{
							memcpy(&time,data->data,sizeof(double));
							if(time == 0)
							{
								nullTimeVec.push_back((*it)->GetTarget());
							}
						}
					}
					vector<SCBase*>::iterator itN;
					int arraySize = nullTimeVec.size();
					int val = 1/arraySize;
					//nulovy cas non determin
					for(itN = nullTimeVec.begin();itN<nullTimeVec.end();itN++)
					{
						if(val > genNonDetNum)
						{
							if((*itN)->Run() == TRANSITION_OK)
							{
								done = true;
								break;
							}
						}
						val += 1/this->m_directedArcsTo.size();
					}
					//nulovy cas skusa
					if(!done)
					{
						for(itN = nullTimeVec.begin();itN<nullTimeVec.end();itN++)
						{
							if((*itN)->Run() == TRANSITION_OK)
							{
								done = true;
								break;
							}
						}
					}
					//vsetky non determin
					arraySize = this->m_directedArcsTo.size();
					val = 1/arraySize;
					if(!done)
					{
						for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
						{
							if(val > genNonDetNum)
							{
								if((*it)->GetTarget()->IsReadyToRun())
								{
									g_eventCal.Insert((*it)->GetTarget(),(*it)->GetTarget()->GetExactTime());
									done = true;
									break;
								}
							}
							val += 1/this->m_directedArcsTo.size();
						}
					}
					//vsetky skusa
					if(!done)
					{
						for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
						{
							if((*it)->GetTarget()->IsReadyToRun())
							{
								g_eventCal.Insert((*it)->GetTarget(),(*it)->GetTarget()->GetExactTime());
								done = true;
								break;
							}
						}
					}
				}
				break;
			case TRANSITION_PROBAB:
				{
					vector<SCDirectedArc*>::iterator it;
					double genNonDetNum = SCGen::GenNomInterval();
					double probability = 0;
					bool ok = true;
					for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
					{
						double currentProb = 0;
						SSBaseData *data = (*it)->GetTarget()->GetData();
						memcpy(&currentProb,data->data,sizeof(double));
						probability += currentProb;
						if(probability > 100)
						{
							this->m_status = RUNTIME_PLACE_CRASH_PROBAB;
							ok = false;
							break;
						}

					}
					probability = 0;
					if(ok)
					{
						bool done = false;
						for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
						{
							double currentProb = 0;
							SSBaseData *data = (*it)->GetTarget()->GetData();
							memcpy(&currentProb,data->data,sizeof(double));
							probability += currentProb;
							if(genNonDetNum < probability/100)
							{
								if((*it)->GetTarget()->Run() == TRANSITION_OK)
								{
									done = true;
									break;
								}
							}
						}
						if(!done)
						{
							for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
							{
								if((*it)->GetTarget()->Run() == TRANSITION_OK)
								{
									break;
								}
							}
						}
					}
				}
				break;
			case TRANSITION_PRIO:
				{
					vector<SCDirectedArc*>::iterator it;
					vector<SSPrioData>prioVector;
					//nacitam vsetky sipky k danemu miestu
					for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
					{
						SSBaseData *data = (*it)->GetTarget()->GetData();
						unsigned int prio;
						memcpy(&prio,data->data,sizeof(int));
						SSPrioData ref;
						ref.prio = prio;
						ref.target = (*it)->GetTarget();
						prioVector.push_back(ref);
					}
					vector<SSPrioData>::iterator itInt;
					vector<SSPrioData>::iterator data;
					unsigned int highestPrio = 0;
					bool sent = false;
					while(!sent)
					{
						//zistim prechod s najvacsou prioritou
						for(itInt = prioVector.begin();itInt<prioVector.end();itInt++)
						{
							if((*itInt).prio > highestPrio)
							{
								highestPrio = (*itInt).prio;
								data = itInt;
							}
						}
						if(data->target->Run() == TRANSITION_OK)
						{
							sent = true;
						}
						else
						{
							prioVector.erase(data);
						}
					}
				}
				break;
			case TRANSITION_NOPARAM:
				{	
					this->CommitTransNoParam();
				}
				break;
			}
		}
	}
	return ret;
}
void SCPlace::CommitTransNoParam()
{

	double arraySize = this->m_directedArcsTo.size();
	double val = 1/arraySize;
	set<SCBase*> failedRun;
	while(1)
	{
		bool done = false;
		double genNonDetNum = SCGen::GenNomInterval();
		vector<SCDirectedArc*>::iterator it;
		for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
		{
			if(val > genNonDetNum)
			{
				if((*it)->GetTarget()->Run() == TRANSITION_OK)
				{
					done = true;
					break;
				}
				else
				{
					if(failedRun.find((*it)->GetTarget()) == failedRun.end())
					{
						failedRun.insert((*it)->GetTarget());
					}
				}
			}
			val += 1/(double)this->m_directedArcsTo.size();
		}
		if(failedRun.size() == this->m_directedArcsTo.size())
		{
			break;
		}
		if(!done)
		{
			for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
			{
				if((*it)->GetTarget()->Run() == TRANSITION_OK)
				{
					break;
				}
				else
				{
					if(failedRun.find((*it)->GetTarget()) == failedRun.end())
					{
						failedRun.insert((*it)->GetTarget());
					}
				}
			}
		}
		if(failedRun.size() == this->m_directedArcsTo.size())
		{
			break;
		}
	}
}
SSBaseData* SCPlace::GetData()
{
	this->m_data.mode = PLACE_CAP;
	memcpy(m_data.data,&this->m_value,sizeof(int));
	memcpy(m_data.data + sizeof(int),&this->m_capacity,sizeof(int));
	return &this->m_data;
}
int SCPlace::Action(int code, int param)
{
	int ret = ACTION_DEFAULT;
	if(code == ACTION_TAKE)
	{
		if( g_print == true )
			cout << "<- Misto s nazvem '" << m_name << "' a kapacitou '"<<m_value << "'";
		if(m_value - param >= 0)
		{
			this->m_value -= param;
			ret = PLACE_TAKEN;
		}
		else
		{
			ret = PLACE_EMPTY;
		}
	}
	else if(code == ACTION_RETURN)
	{
		if( g_print == true )
			cout << "-> Misto s nazvem '" << m_name << "' a kapacitou '"<<m_value << "'";
		this->m_value += param;
		ret = PLACE_RETURNED;
	}
	if( g_print == true )
		cout << " zmenilo svou kapacitu na: '"<<m_value << "'";
	return ret;
}
unsigned int SCPlace::GetArgCapacity()
{
	return this->m_capacity;
}
unsigned int SCPlace::GetArgCurrentVal()
{
	return this->m_value;
}
unsigned int SCPlace::GetArgStartVal()
{
	return this->m_startVal;
}
int SCPlace::Compare(SCPlace *place)
{
	if(this->m_id != place->GetId())
		return COMPARE_ID;

	if(this->m_capacity != place->GetArgCapacity())
		return COMPARE_CAP;

	if(this->m_value != place->GetArgCurrentVal())
		return COMPARE_VALUE;

	return COMPARE_EQUAL;
}
SCDirectedArc* SCPlace::GetLastCommitedArc()
{
	return this->m_lastCommited;
}
void SCPlace::SetLastCommitedArc(SCDirectedArc* directedArc)
{
	this->m_lastCommited = directedArc;
}


