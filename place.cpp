#include "place.h"

SCPlace::SCPlace()
{
	g_allPlaces.push_back(this);
	this->m_capacity = 0;
	this->m_value = 0;
	this->m_status = PLACE_OK;
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
	this->m_value = startValue;
	return this->m_status;
}
int SCPlace::Run()
{
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
			SSBaseData data = (*it)->GetTarget()->GetData();
			if(data.mode != TRANSITION_NOPARAM)
			{	
				if(currentMode != data.mode && (currentMode != TRANSITION_DEFAULT || currentMode != TRANSITION_NOPARAM || currentMode != TRANSITION_PRIO))
				{
					this->m_status = RUNTIME_TRANSITION_CRASH;
					ret = PLACE_FAIL;
					break;
				}
				currentMode = data.mode;
			}
			else if(data.mode == TRANSITION_NOPARAM && currentMode == TRANSITION_DEFAULT)  
			{
				currentMode = data.mode;
			}
		}
		if(this->m_status != RUNTIME_TRANSITION_CRASH)
		{
			//todo specifikovat pre paramtery sipky
			switch(currentMode)
			{
			case TRANSITION_WAIT:
				{
					int i = 0;
					vector<SCDirectedArc*>::iterator it;
					for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
					{
						i++;
						//prevedie sa raz za spravneho grafu
					}
					if(i!= 1)
					{
						(*this->m_directedArcsTo.begin())->GetTarget()->Run();
					}
					else
					{
						this->m_status = RUNTIME_PLACE_CRASH_WAIT;
						ret = PLACE_FAIL;
					}
				}
				break;
			case TRANSITION_PROBAB:
				{
					vector<SCDirectedArc*>::iterator it;
					for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
					{
						SSBaseData data = (*it)->GetTarget()->GetData();
						double probability;
						memcpy(&probability,&data.data,sizeof(double));
						//ziskam desatinne cislo na pravdepodobnost z generatora a porovnam
						//TODO:
						//if pravdepodobnost
						//run
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
						SSBaseData data = (*it)->GetTarget()->GetData();
						int prio;
						memcpy(&prio,&data.data,sizeof(int));
						SSPrioData ref;
						ref.prio = prio;
						ref.target = (*it)->GetTarget();
						prioVector.push_back(ref);
					}
					vector<SSPrioData>::iterator itInt;
					vector<SSPrioData>::iterator data;
					int highestPrio = 0;
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
						//ziskam sipky k prechodu
						vector<SCDirectedArc*> *targetDirectedArcsFrom = data->target->GetDirectedArcsFrom();
						bool right = true;
						//prehladam nody zo startu sipok a zistim ci su volne
						for(it = targetDirectedArcsFrom->begin();it<targetDirectedArcsFrom->end();it++)
						{
							SSBaseData data = (*it)->GetStart()->GetData();
							if( data.mode == PLACE_CAP)
							{
								unsigned int value;
								memcpy(&value,&data.data,sizeof(int));
								if(value - (*it)->GetArgWeight() < 0)
								{
									right = false;
								}
							}
							else
							{
								this->m_status = RUNTIME_PLACE_CRASH;
								 ret = PLACE_FAIL;
							}
						}
						if(right && this->m_status == PLACE_OK)
						{
							for(it = targetDirectedArcsFrom->begin();it<targetDirectedArcsFrom->end();it++)
							{
								if((*it)->GetStart()->Action(ACTION_TAKE, (*it)->GetArgWeight()) != PLACE_TAKEN)
								{
									this->m_status = PLACE_UNKNOWN_ERR;
									ret = PLACE_FAIL;
									break;
								}
							}
							sent = true;
							data->target->Run();
						}
						//ak nie je volny tak sa vymaze ten s najvyssou prioritou
						else if(!right)
						{
							prioVector.erase(data);
						}
						else
							break;
					}
				}
				break;
			case TRANSITION_NOPARAM:
				{
					vector<SCDirectedArc*>::iterator it;
					bool right = true;
					for(it=this->m_directedArcsFrom.begin();it<this->m_directedArcsFrom.end();it++)
					{
						SSBaseData data = (*it)->GetStart()->GetData();
						if( data.mode == PLACE_CAP)
						{
							unsigned int value;
							memcpy(&value,&data.data,sizeof(int));
							if(value - (*it)->GetArgWeight() < 0)
							{
								right = false;
							}
						}
						else
						{
							ret = PLACE_FAIL;
							this->m_status = RUNTIME_PLACE_CRASH;
						}
					}
					if(right && this->m_status == PLACE_OK)
					{
						for(it=this->m_directedArcsFrom.begin();it<this->m_directedArcsFrom.end();it++)
						{
							(*it)->GetStart()->Action(ACTION_TAKE,(*it)->GetArgWeight());
						}
						for(it=this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
						{
							(*it)->GetTarget()->Run();
						}
					}
				}
				break;
			}
		}
	}
	return ret;
}
SSBaseData SCPlace::GetData()
{
	SSBaseData data;
	data.mode = PLACE_CAP;
	memcpy(&data.data,&this->m_value,sizeof(int));
	return data;
}
int SCPlace::Action(int code, int param)
{
	int ret = ACTION_DEFAULT;
	if(code == ACTION_TAKE)
	{
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
		this->m_value += param;
		ret = PLACE_RETURNED;
	}
	return ret;
}