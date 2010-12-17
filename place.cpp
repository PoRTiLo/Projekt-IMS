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
	this->m_print = true;
	this->m_startVal = 0;
	this->m_capacity = UINT_MAX;
	this->m_value = 0;
	this->m_total = 0;
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
	this->m_total = startValue;
	this->m_value = startValue;
	g_eventCal.Insert(this,g_time);
	return this->m_status;
}
int SCPlace::Run()
{
	if(this->m_status != PLACE_OK)
	{
		return this->m_status;
	}
	else if(this->m_directedArcsTo.size() == 0)
	{
		return PLACE_SIM_END;
	}
	else if(this->m_value <= 0)
	{
		return PLACE_EMPTY;
	}
	int ret = PLACE_OK;
	int currentMode = TRANSITION_DEFAULT;
	if(this->m_status == PLACE_OK)
	{
		vector<SCDirectedArc*>::iterator it;
		for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
		{
			SSBaseData *data = (*it)->GetTarget()->GetData();
			if(data->mode != TRANSITION_NOPARAM)
			{	
				if(currentMode != data->mode)
				{
					if(currentMode != TRANSITION_DEFAULT && currentMode != TRANSITION_NOPARAM)
					{
						ret = this->m_status = RUNTIME_TRANSITION_CRASH;
						break;
					}
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
					ret = this->CommitTransTime();
				}
				break;
			case TRANSITION_PROBAB:
				{
					ret = this->CommitTransProbab();
				}
				break;
			case TRANSITION_PRIO:
				{
					ret = this->CommitTransPrio();
				}
				break;
			case TRANSITION_NOPARAM:
				{	
					ret = this->CommitTransNoParam();
				}
				break;
			}
		}
	}
	return ret;
}
int SCPlace::CommitTransTime()
{
	int ret = PLACE_OK;
	vector<SCDirectedArc*>::iterator it;
	vector<SCBase*> nullTimeVec;
	//najde nulovy cas
	for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
	{
		SSBaseData *data;
		data = (*it)->GetTarget()->GetData();
		double time = 0;
		memcpy(&time,data->data,sizeof(double));
		if(time == 0)
		{
			nullTimeVec.push_back((*it)->GetTarget());
		}
	}
	double arraySize = 0;
	double val = 0;
	if(!nullTimeVec.empty())
	{
		vector<SCBase*>::iterator itN;
		arraySize = nullTimeVec.size();
		val = 1/arraySize;
		set<SCBase*> failedRun;
		while(1)
		{
			double genNonDetNum = SCGen::GenNomInterval();
			//nulovy cas non determin
			bool done = false;
			for(itN = nullTimeVec.begin();itN<nullTimeVec.end();itN++)
			{
				if(val > genNonDetNum)
				{

					if((ret = (*itN)->Run()) == TRANSITION_OK)
					{
						done = true;
						break;
					}
					else
					{
						if(this->EvaluateErrorCode(ret,*itN) == BASE_FATAL)
						{
							return ret;
						}
						if(failedRun.find(*itN) == failedRun.end())
						{
							failedRun.insert(*itN);
						}
					}
				}
				val += 1/(double)this->m_directedArcsTo.size();
			}
			if(failedRun.size() == nullTimeVec.size())
			{
				break;
			}
			//nulovy cas prvy
			if(!done)
			{
				for(itN = nullTimeVec.begin();itN<nullTimeVec.end();itN++)
				{
					if((ret = (*itN)->Run()) == TRANSITION_OK)
					{
						done = true;
						break;
					}
					else
					{
						if(this->EvaluateErrorCode(ret,*itN) == BASE_FATAL)
						{
							return ret;
						}
						if(failedRun.find(*itN) == failedRun.end())
						{
							failedRun.insert(*itN);
						}
					}
				}
				if(failedRun.size() == nullTimeVec.size())
				{
					break;
				}
			}
		}
	}
	bool done = false;
	double genNonDetNum = SCGen::GenNomInterval();
	//vsetky non determin
	arraySize = this->m_directedArcsTo.size();
	val = 1/arraySize;
	for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
	{
		if(val > genNonDetNum)
		{
			if((*it)->GetTarget()->IsReadyToRun())
			{
				(*it)->GetTarget()->SetLastCommitedArc(*it);
				g_eventCal.Insert((*it)->GetTarget(),(*it)->GetTarget()->GetExactTime());
				done = true;
				break;
			}
		}
		val += 1/(double)this->m_directedArcsTo.size();
	}
	//vsetky skusa
	if(!done)
	{
		for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
		{
			if((*it)->GetTarget()->IsReadyToRun())
			{
				(*it)->GetTarget()->SetLastCommitedArc(*it);
				g_eventCal.Insert((*it)->GetTarget(),(*it)->GetTarget()->GetExactTime());
				done = true;
				break;
			}
		}
	}
	return ret;
}
int SCPlace::CommitTransPrio()
{
	int ret = PLACE_OK;
	double arraySize = this->m_directedArcsTo.size();
	double val = 1/arraySize;
	set<SCBase*> failedRun;
	vector<SCDirectedArc*>::iterator it;
	vector<SSPrioData>prioVector2;
	vector<SSPrioData>::iterator itInt;
	//nacitam vsetky sipky k danemu miestu
	for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
	{
		SSBaseData *data = (*it)->GetTarget()->GetData();
		unsigned int prio;
		memcpy(&prio,data->data,sizeof(int));
		SSPrioData ref;
		ref.prio = prio;
		ref.target = (*it)->GetTarget();
		prioVector2.push_back(ref);
	}
	vector<SSPrioData>prioVector;
	vector<SCBase*>samePrioVec;
	bool finish = false;
	while(!finish)
	{
		prioVector = prioVector2;
		bool sent = false;
		while(!sent)
		{
			unsigned int highestPrio = 0;
			samePrioVec.clear();
			//zistim prechod s najvacsou prioritou
			for(itInt = prioVector.begin();itInt<prioVector.end();itInt++)
			{
				if((*itInt).prio == highestPrio)
				{
					samePrioVec.push_back(itInt->target);
				}
				else if((*itInt).prio > highestPrio)
				{
					samePrioVec.clear();
					samePrioVec.push_back(itInt->target);
					highestPrio = (*itInt).prio;
				}
			}
			double rand = SCGen::GenNomInterval();
			vector<SCBase*>::iterator itB;
			double arraySize = samePrioVec.size();
			double val = 1/arraySize;
			//try rand
			for(itB = samePrioVec.begin(); itB < samePrioVec.end(); itB++)
			{
				if( val > rand)
				{
					if((ret = (*itB)->Run()) == TRANSITION_OK)
					{
						sent = true;
						break;
					}
					else
					{
						if(this->EvaluateErrorCode(ret,*itB) == BASE_FATAL)
						{
							return ret;
						}
						if(failedRun.find(*itB) == failedRun.end())
						{
							failedRun.insert(*itB);
						}
					}
				}
				val += 1/arraySize; 
			}
			if(failedRun.size() == this->m_directedArcsTo.size())
			{
				finish = true;
				break;
			}
			if(!sent)
			{
				for(itB = samePrioVec.begin(); itB < samePrioVec.end(); itB++)
				{
					if((ret = (*itB)->Run()) == TRANSITION_OK)
					{
						sent = true;
						break;
					}
					else
					{
						if(this->EvaluateErrorCode(ret,*itB) == BASE_FATAL)
						{
							return ret;
						}
						if(failedRun.find(*itB) == failedRun.end())
						{
							failedRun.insert(*itB);
						}
					}
				}
			}
			if(failedRun.size() == this->m_directedArcsTo.size())
			{
				finish = true;
				break;
			}
			//vymaz prvky s najvyssou prioritou zo zoznamu ak nie je preveditelny ani jeden
			for(itInt = prioVector.begin();itInt<prioVector.end();itInt++)
			{
				if(highestPrio == itInt->prio)
				{
					itInt = prioVector.erase(itInt);
				}
				if(itInt == prioVector.end())
				{
					break;
				}
			}
		}	
	}
	return ret;
}
int SCPlace::CommitTransNoParam()
{
	int ret = PLACE_OK;
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
				if((ret = (*it)->GetTarget()->Run()) == TRANSITION_OK)
				{
					done = true;
					break;
				}
				else
				{
					if(this->EvaluateErrorCode(ret,(*it)->GetTarget()) == BASE_FATAL)
					{
						return ret;
					}
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
				if((ret = (*it)->GetTarget()->Run()) == TRANSITION_OK)
				{
					break;
				}
				else
				{
					if(this->EvaluateErrorCode(ret,(*it)->GetTarget()) == BASE_FATAL)
					{
						return ret;
					}
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
	return ret;
}
int SCPlace::CommitTransProbab()
{
	int ret = PLACE_OK;
	double arraySize = this->m_directedArcsTo.size();
	double val = 1/arraySize;
	set<SCBase*> failedRun;
	vector<SCDirectedArc*>::iterator it;
	double probability = 0;
	bool ok = true;
	int zeroProbTrans = 0; //pocet prechodov bez parametra
	//skontrolujem sucet pravdepodobnosti a zistim prechody bez parametra
	for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
	{
		double currentProb = 0;
		SSBaseData *data = (*it)->GetTarget()->GetData();
		memcpy(&currentProb,data->data,sizeof(double));
		if(currentProb == 0)
		{
			zeroProbTrans++;
		}
		probability += currentProb;
	}
	if(probability > 100)
	{
		ret = this->m_status = RUNTIME_TRANS_PROB_LIMIT;
		ok = false;
	}
	else if(probability != 100 && zeroProbTrans == 0)
	{
		ret = this->m_status = RUNTIME_TRANS_PROB_LOW;
		ok = false;
	}
	//pravdepodobnost prechodov bez parametra
	double noParamTransProb = (100-probability)/(double)zeroProbTrans;
	while(ok)
	{
		double genNonDetNum = SCGen::GenNomInterval();
		probability = 0;
		bool done = false;
		for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
		{
			double currentProb = 0;
			SSBaseData *data = (*it)->GetTarget()->GetData();
			memcpy(&currentProb,data->data,sizeof(double));
			if(currentProb == 0)
			{
				currentProb = noParamTransProb;
			}
			probability += currentProb;
			if(genNonDetNum < probability/100)
			{
				if((ret = (*it)->GetTarget()->Run()) == TRANSITION_OK)
				{
					done = true;
					break;
				}
				else
				{
					if(this->EvaluateErrorCode(ret,(*it)->GetTarget()) == BASE_FATAL)
					{
						return ret;
					}
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
		if(!done)
		{
			for(it = this->m_directedArcsTo.begin();it<this->m_directedArcsTo.end();it++)
			{
				if((ret = (*it)->GetTarget()->Run()) == TRANSITION_OK)
				{
					break;
				}
				else
				{
					if(this->EvaluateErrorCode(ret, (*it)->GetTarget()) == BASE_FATAL)
					{
						return ret;
					}
					if(failedRun.find((*it)->GetTarget()) == failedRun.end())
					{
						failedRun.insert((*it)->GetTarget());
					}
				}
			}
			if(failedRun.size() == this->m_directedArcsTo.size())
			{
				break;
			}
		}		
	}
	return ret;
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
		if( g_print == true && this->m_print == true )
			cout << "time: '" << g_time << "' <-- " << this->m_name.c_str() << "(Act. value ['"<< this->m_value << "'";
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
		if( g_print == true && this->m_print == true )
			cout << "time: '" << g_time << "' --> " << this->m_name.c_str() << "(Act. value ['"<< this->m_value << "'";
		this->m_value += param;
		this->m_total++;
		ret = PLACE_RETURNED;
	}
	if( g_print == true && this->m_print == true )
	{
		cout << "-->'"<< this->m_value << "'])";
		g_printT = true;
	}
	else
		g_printT = false;

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
unsigned int SCPlace::GetArgTotal() {

	return this->m_total;
}
bool SCPlace::IsPrint() {

	return this->m_print;
}
void SCPlace::SetArgPrint( bool print ) {

	this->m_print = print;
}
bool SCPlace::CheckTransitions()
{
	bool ret = true;
	int currentTransition = TRANSITION_DEFAULT;
	vector<SCDirectedArc*>::iterator it;
	for(it = this->m_directedArcsTo.begin(); it < this->m_directedArcsTo.end(); it++)
	{
		if((*it)->GetTarget()->GetStatus() != TRANSITION_OK)
		{
			if(ret)
			{
				cout<<"failed!"<<endl<<endl;
			}
			cout<<"MODEL SEMANTIC ERROR: Transition: "<<(*it)->GetName().c_str()<<" contains bad arguments, Check model !!!"<<endl;
			ret = false;
		}
		if(currentTransition == TRANSITION_DEFAULT)
		{
			currentTransition =  (*it)->GetTarget()->GetData()->mode;
		}
		else
		{
			if(currentTransition == TRANSITION_NOPARAM)
			{
				currentTransition =  (*it)->GetTarget()->GetData()->mode;
			}
			else
			{
				if(currentTransition != (*it)->GetTarget()->GetData()->mode && (*it)->GetTarget()->GetData()->mode != TRANSITION_NOPARAM)
				{
					if(ret)
					{
						cout<<"failed!"<<endl<<endl;
					}
					cout<<"MODEL SEMANTIC ERROR: Place: "<<this->GetName().c_str()<<" has more types of transitions available, Check model !!!"<<endl;
					ret = false;
				}
			}
		}
	}
	if(currentTransition == TRANSITION_PROBAB)
	{
		unsigned int noParamCount = 0;
		double fullProbab = 0;
		for(it = this->m_directedArcsTo.begin(); it < this->m_directedArcsTo.end(); it++)
		{
			if((*it)->GetTarget()->GetData()->mode == TRANSITION_NOPARAM)
			{
				noParamCount++;
			}
			double probab = 0;
			memcpy(&probab,(*it)->GetTarget()->GetData()->data,sizeof(double));
			fullProbab += probab;
		}
		if(fullProbab > 100)
		{
			if(ret)
			{
				cout<<"failed!"<<endl<<endl;
			}
			cout<<"MODEL SEMANTIC ERROR: The sum of transition probabilities for place: "<<this->GetName().c_str()<<" is more then 100%, Check model !!!"<<endl;
			ret = false;
		}
		if(fullProbab < 100 && noParamCount == 0)
		{
			if(ret)
			{
				cout<<"failed!"<<endl<<endl;
			}
			cout<<"MODEL SEMANTIC ERROR: The sum of transition probabilities for place: "<<this->GetName().c_str()<<" is lower then 100%, Check model !!!"<<endl;
			ret = false;
		}
	}
	return ret;
}
