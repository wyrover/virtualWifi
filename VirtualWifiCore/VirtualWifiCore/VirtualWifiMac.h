#pragma once
#include "stdafx.h"

#define MECLEN 32

class VirtualWifiMac
{
private:
	char m_sz_mac[MECLEN];
	u_char m_mac_address[6];
private:
	void set_mac(u_char mac[6]);
public:
	bool operator==(VirtualWifiMac& mac);  //ÖØÔØÔËËã·û
	CONST_STR string();
	DOT11_MAC_ADDRESS& get_mac();

	VirtualWifiMac(u_char mac[6]);
	VirtualWifiMac();
	~VirtualWifiMac(void);
};

class VirtualWifiMacList
{
private:
	list<VirtualWifiMac*> m_lst_mac_addr;
public:
	VirtualWifiMacList();
	bool is_exist(VirtualWifiMac& mac);
	void add_mac_addr(DOT11_MAC_ADDRESS& dot11_mac_address);
	void add_mac_addr(WLAN_HOSTED_NETWORK_STATUS& network_status);
	void add_mac_addr(VirtualWifiMac& mac);
};
