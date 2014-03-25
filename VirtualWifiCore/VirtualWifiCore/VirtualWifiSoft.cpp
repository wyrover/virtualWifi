#include "stdafx.h"


VirtualWifiSoft::VirtualWifiSoft()
{
	m_softinfo=ParseSoft();
	parse_title();
	parse_mainui_title();
	m_warninginfo=EMPTYSTRING;
}
void VirtualWifiSoft::get_title(char* sz_title,int& n_title_buffer_len)
{
	memset(sz_title,0,n_title_buffer_len);
	int n_title_len=strlen(m_softinfo->szTitle);
	memcpy(sz_title,m_softinfo->szTitle,n_title_len);
	int n_space_len=strlen(SPACE);
	memcpy(sz_title+n_title_len,SPACE,n_space_len);
	memcpy(sz_title+n_title_len+n_space_len,m_softinfo->szVersion,strlen(m_softinfo->szVersion));
}
void VirtualWifiSoft::parse_title()
{
	int n_title_len=strlen(m_softinfo->szTitle);
	int n_space_len=strlen(SPACE);
	int n_version_len=strlen(m_softinfo->szVersion);
	m_version_title=new char[n_title_len+n_space_len+n_version_len+1];
	strcpy(m_version_title,m_softinfo->szTitle);
	strcat(m_version_title,SPACE);
	strcat(m_version_title,m_softinfo->szVersion);
}
void VirtualWifiSoft::parse_mainui_title()
{
	int n_title_len=strlen(m_softinfo->szTitle);
	int n_space_len=strlen(SEPARATOR);
	int n_version_len=strlen(m_softinfo->szVersion);
	m_version_mainui_title=new char[n_title_len+n_space_len+n_version_len+1];
	sprintf(m_version_mainui_title,"%s%s%s",m_softinfo->szTitle,SEPARATOR,m_softinfo->szVersion);
}
char* VirtualWifiSoft::get_title() const
{
	return m_version_title;
}
char* VirtualWifiSoft::get_mainui_title() const 
{
	return m_version_mainui_title;
}
void VirtualWifiSoft::modify_soft()
{
	ModifySoft(*m_softinfo);
}
void VirtualWifiSoft::check_flowmonitor_pos()
{
	if (m_softinfo->nflowmonitor_x<0||m_softinfo->nflowmonitor_y<0)
	{
		int nxlen=GetSystemMetrics(SM_CXSCREEN);
		int nylen=GetSystemMetrics(SM_CYSCREEN);
		m_softinfo->nflowmonitor_x=nxlen-230;
		m_softinfo->nflowmonitor_y=nylen-65;
	}
}
VirtualWifiSoft::~VirtualWifiSoft()
{
	delete[] m_version_title;
	delete[] m_version_mainui_title;
}