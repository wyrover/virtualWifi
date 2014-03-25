#include "StdAfx.h"
#include "VirtualWifiInitBase.h"


VirtualWifiInitBase::VirtualWifiInitBase(void)
{
}

bool VirtualWifiInitBase::add_init_command(CONST_STR sz_c,int& ncommandlen)
{
	if (ncommandlen>0)
	{
		VirtualWifiInitStruct vws;
		vws.sz_c=new char[ncommandlen];
		vws.s_sz_c_len=ncommandlen;
		memcpy((void*)vws.sz_c,sz_c,ncommandlen);
        m_lstinitstruct.push_back(vws);
		return true;
	}
	return false;
}
bool VirtualWifiInitBase::add_init_command(VirtualWifiInitStruct& virtualwifistruct)
{
	return add_init_command(virtualwifistruct.sz_c,(int&)virtualwifistruct.s_sz_c_len);
}
void VirtualWifiInitBase::reset_data()
{
	m_it_lstinitstruct=m_lstinitstruct.begin();
	m_bcheck_begin=false;
}
bool VirtualWifiInitBase::has_next()
{
	 if (!m_bcheck_begin&&m_it_lstinitstruct==m_lstinitstruct.begin())
	 {
		 m_bcheck_begin=true;
		 return true;
	 }
	  m_it_lstinitstruct++;
	 if(m_it_lstinitstruct==m_lstinitstruct.end())
	 {
		 return false;
	 }
	 return true;
}

VirtualWifiInitBase::VirtualWifiInitStruct& VirtualWifiInitBase::current_data()
{
	return *m_it_lstinitstruct;
}
void VirtualWifiInitBase::remove_all_init_command()
{
	for (m_it_lstinitstruct=m_lstinitstruct.begin();m_it_lstinitstruct!=m_lstinitstruct.end();++m_it_lstinitstruct)
	{
		delete[] m_it_lstinitstruct->sz_c;
	}
	m_lstinitstruct.clear();
}
VirtualWifiInitBase::~VirtualWifiInitBase(void)
{
	remove_all_init_command();
}
