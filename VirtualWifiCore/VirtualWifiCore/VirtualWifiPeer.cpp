#include "StdAfx.h"
#include "VirtualWifiPeer.h"


CONST_STR VirtualWifiPeer::PERRSTR="%s&%s";

VirtualWifiPeer::VirtualWifiPeer(DOT11_MAC_ADDRESS& dot11_mac_address)
{
	m_mac_addr=new VirtualWifiMac(dot11_mac_address);
	m_flow=new VirtualWifiFlow();
	m_ip=new VirtualWifiIp();
	m_time=NULL;
}
VirtualWifiPeer::VirtualWifiPeer(CONST_STR sz_ip)
{
	m_mac_addr=new VirtualWifiMac();
	m_flow=new VirtualWifiFlow();
	m_ip=new VirtualWifiIp(sz_ip);
	m_time=NULL;
}
void VirtualWifiPeer::set_ip(CONST_STR sz_ip)
{
	m_ip->set_ip(sz_ip);
}
void VirtualWifiPeer::set_time(VirtualWifiTime* time/* =NULL */)
{
	if (time==NULL)
	{
		time=&VirtualWifiTime::get_now_time();
	}
	free_time();
	m_time=new VirtualWifiTime(*time);
}
VirtualWifiFlow* VirtualWifiPeer::get_flow()
{
	return m_flow;
}
VirtualWifiMac* VirtualWifiPeer::get_mac()
{
	return m_mac_addr;
}
void VirtualWifiPeer::free_time()
{
	if (m_time!=NULL)
	{
		delete m_time;
	}
}

//重载==运算符,验证mac地址是否相等
bool VirtualWifiPeer::operator==(u_char umac[6])
{
	DOT11_MAC_ADDRESS& temp_mac_address=m_mac_addr->get_mac();
	return temp_mac_address[0]==umac[0]&&
		temp_mac_address[1]==umac[1]&&
		temp_mac_address[2]==umac[2]&&
		temp_mac_address[3]==umac[3]&&
		temp_mac_address[4]==umac[4]&&
	    temp_mac_address[5]==umac[5];
//	return !strcmp((char*)&(this->m_mac_addr->get_mac()),(char*)&(dot11_mac_address));
}
VirtualWifiPeer::~VirtualWifiPeer(void)
{
	free_time();
	delete m_mac_addr;
}
VirtualWifiIp* VirtualWifiPeer::get_ip()
{
	return m_ip;
}
string VirtualWifiPeer::to_string()
{
	char sz_ret[PEERSTRLEN];
	sprintf(sz_ret,PERRSTR,m_mac_addr->string(),m_time->string());
	return string(sz_ret);
}