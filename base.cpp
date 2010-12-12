#include "base.h"
SSBaseData* SCBase::GetData()
{
	return this->m_data;
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
SCBase::SCBase()
{
	this->m_name = "Base default name, do not use this class!";
	this->m_id = 0;
	this->m_data = NULL;
	this->m_status = BASE_OK;
}
SCBase::~SCBase()
{
	if(this->m_data != NULL)
		//delete this->m_data;
		;
}
unsigned int SCBase::GetId()
{
	return this->m_id;
}
