/*IMS - Modelovani a simulace
 *
 * Project:  Simulator cernobilych stochastickych Petriho siti
 * File:     directedArc.cpp
 * Author:   Dusan Kovacic, xkovac21, xkovac21@stud.fit.vutbr.cz
 *           Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *
 * Encoding: UTF-8
 *
 * Description:
 */

#include "directedArc.h"

SCDirectedArc::SCDirectedArc()
{
	g_allDirected.push_back(this);
	this->m_weight = 1;
	this->m_status = DIRECTEDARC_OK;
	this->m_target = NULL;
	this->m_start = NULL;
	this->m_inhib = DIRECTEDARC_DEFAULT;
	this->m_id = g_arcIndex++;
	char buff[32];
	sprintf(buff,"Directed arc %d",this->m_id);
	this->m_name = buff;
}
SCDirectedArc::~SCDirectedArc()
{
}
void SCDirectedArc::SetName(string name)
{
	this->m_name = name;
}
string SCDirectedArc::GetName()
{
	return this->m_name;
}
unsigned int SCDirectedArc::GetId()
{
	return this->m_id;
}
int SCDirectedArc::SetArgWeight(unsigned int weight)
{
	this->m_weight = weight;
	return this->m_status;
}
/*
int SCDirectedArc::SetArgInhib()
{
	if(m_weight != 1)
	{
		return RUNTIME_DIRECTEDARC_INHIB_COL;
	}
	this->m_inhib = DIRECTEDARC_INHIB;
	return this->m_status;
}
*/
unsigned int SCDirectedArc::GetArgWeight()
{
	return this->m_weight;
}
int SCDirectedArc::GetArgInhib()
{
	return this->m_inhib;
}
int SCDirectedArc::GetStatus()
{
	return this->m_status;
}
int SCDirectedArc::SetTarget(SCBase *target)
{
	if(target != NULL)
	{
		this->m_target = target;
	}
	else
	{
		this->m_status = DIRECTEDARC_NULL_ARG;
	}
	return this->m_status;
}
int SCDirectedArc::SetStart(SCBase *start)
{
	if(start != NULL)
	{
		this->m_start = start;
	}
	else
	{
		this->m_status = DIRECTEDARC_NULL_ARG;
	}
	return this->m_status;
}
SCBase* SCDirectedArc::GetTarget()
{
	return this->m_target;
}
SCBase* SCDirectedArc::GetStart()
{
	return this->m_start;
}
