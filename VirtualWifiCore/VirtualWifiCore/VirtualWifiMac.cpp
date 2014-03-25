#include "StdAfx.h"
#include "VirtualWifiMac.h"

#define MAC_ADDR_LEN 32


VirtualWifiMac::VirtualWifiMac(u_char mac[6])
{
	set_mac(mac);
}

VirtualWifiMac::VirtualWifiMac()
{
	u_char mac[6];
	memset(mac,0,6);
	set_mac(mac);
}

void VirtualWifiMac::set_mac(u_char mac[6])
{
	memcpy(m_mac_address,mac,sizeof(m_mac_address));
	sprintf(m_sz_mac,"%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2]
	,mac[3],mac[4],mac[5]);
}
bool VirtualWifiMac::operator ==(VirtualWifiMac& mac)
{
	return this->get_mac()==mac.get_mac();
}
CONST_STR VirtualWifiMac::string()
{
	return m_sz_mac;
}
DOT11_MAC_ADDRESS& VirtualWifiMac::get_mac()
{
	return m_mac_address;
}
VirtualWifiMac::~VirtualWifiMac(void)
{

}
