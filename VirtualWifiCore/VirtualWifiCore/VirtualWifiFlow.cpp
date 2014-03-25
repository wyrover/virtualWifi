#include "StdAfx.h"
#include "VirtualWifiFlow.h"



VirtualWifiFlow::VirtualWifiFlow(void):m_ldowntotal(0),m_luptoal(0),m_currentdown(0),m_currentup(0)
{

}

void VirtualWifiFlow::add_downflow(u_long ulszie)
{
	this->m_currentdown+=ulszie;
}
void VirtualWifiFlow::add_upflow(u_long ulszie)
{
	this->m_currentup+=ulszie;
}
void VirtualWifiFlow::add_flow(u_long ulszie,link_type lt)
{
	if (lt==down_link_type)
		add_downflow(ulszie);
	else
		add_upflow(ulszie);
}
llong VirtualWifiFlow::get_downtotal()
{
	return m_ldowntotal;
}
llong VirtualWifiFlow::get_uptotal()
{
	return m_luptoal;
}
u_long VirtualWifiFlow::get_currentdown()
{
	return m_currentdown;
}
u_long VirtualWifiFlow::get_currentup()
{
	return m_currentup;
}
void VirtualWifiFlow::clear_current()
{
	m_ldowntotal+=m_currentdown;
	m_luptoal+=m_currentup;
	m_currentup=0;
	m_currentdown=0;
}
void VirtualWifiFlow::add_total_flow(u_long ulszie,link_type lt)
{
	if (lt==down_link_type)
		m_ldowntotal+=ulszie;
	else
		m_luptoal+=ulszie;
}
float VirtualWifiFlow::calculate_downspeed(u_int utime)
{
	float f=(DOUBLE)utime/(DOUBLE)MICROSECONDS;
	float fspeed=(m_currentdown/f)/ONEK;
	return fspeed;
}
float VirtualWifiFlow::calculate_upspeed(u_int utime)
{
	float f=(DOUBLE)utime/(DOUBLE)MICROSECONDS;
	float fspeed=(m_currentup/f)/ONEK;
	return fspeed;
}
void VirtualWifiFlow::clear_total()
{
	m_luptoal=0;
	m_ldowntotal=0;
}
VirtualWifiFlow::~VirtualWifiFlow(void)
{
}
