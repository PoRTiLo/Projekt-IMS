#include "place.h"

SCPlace::SCPlace()
{
	g_allPlaces.push_back(this);
	this->m_capacity = UINT_MAX;
	this->m_value = 0;
	this->m_status = PLACE_OK;
}
SCPlace::~SCPlace()
{
	if(this->m_data != NULL)
		delete this->m_data;
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
					int genNonDetNum = 0; /*TODO: vygeneruj cislo od 0-1 a prirad*/
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
								if((*it)->GetTarget()->Run() == TRANSITION_OK)
								{
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
							if((*it)->GetTarget()->Run() == TRANSITION_OK)
							{
								break;
							}
						}
					}
				}
				break;
			case TRANSITION_PROBAB:
				{
					vector<SCDirectedArc*>::iterator it;
					int genNonDetNum = 0; /*TODO: vygeneruj cislo od 0-1 a prirad*/
					double probability = 0;
					bool ok = true;
					for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
					{
						double currentProb = 0;
						SSBaseData *data = (*it)->GetTarget()->GetData();
						memcpy(&currentProb,&data->data,sizeof(double));
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
							memcpy(&currentProb,&data->data,sizeof(double));
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
						int prio;
						memcpy(&prio,&data->data,sizeof(int));
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
					int genNonDetNum = 0; /*TODO: vygeneruj cislo od 0-1 a prirad*/
					int arraySize = this->m_directedArcsTo.size();
					int val = 1/arraySize;
					vector<SCDirectedArc*>::iterator it;
					bool done = false;
					for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
					{
						if(val > genNonDetNum)
						{
							if((*it)->GetTarget()->Run() == TRANSITION_OK)
							{
								done = true;
								break;
							}
						}
						val += 1/this->m_directedArcsTo.size();
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
				break;
			}
		}
	}
	return ret;
}
SSBaseData* SCPlace::GetData()
{
	this->m_data = new SSBaseData;
	m_data->mode = PLACE_CAP;
	memset(m_data->data,0,8);
	memcpy(&m_data->data,&this->m_value,sizeof(int));
	memcpy(&m_data->data + sizeof(int),&this->m_capacity,sizeof(int));
	return this->m_data;
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