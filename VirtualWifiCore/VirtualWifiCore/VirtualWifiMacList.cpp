#include "stdafx.h"
#include "VirtualWifiMac.h"


VirtualWifiMacList::VirtualWifiMacList()
{

}

void VirtualWifiMacList::add_mac_addr(DOT11_MAC_ADDRESS& dot11_mac_address)
{
	VirtualWifiMac* mac_temp=new VirtualWifiMac(dot11_mac_address);
	m_lst_mac_addr.push_back(mac_temp);
}
void VirtualWifiMacList::add_mac_addr(WLAN_HOSTED_NETWORK_STATUS& network_status)
{

}
bool VirtualWifiMacList::is_exist(VirtualWifiMac& mac)
{
	return false;
}

void VirtualWifiMacList::add_mac_addr(VirtualWifiMac& mac)
{
	
}