#include "base.h"
SSBaseData SCBase::GetData()
{
	SSBaseData data;
	data.mode = BASE_DEFAULT;
	return data;
}
int SCBase::GetStatus()
{
	return this->m_status;
}
int SCBase::AddDirectedArcFrom(SCDirectedArc *directedArc)
{
	if(directedArc != NULL)
	{
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
		this->m_directedArcsTo.push_back(directedArc);
	}
	else
	{
		this->m_status = BASE_NULL_ARG;
	}
	return this->m_status;
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
	this->m_status = BASE_OK;
}
SCBase::~SCBase()
{
}