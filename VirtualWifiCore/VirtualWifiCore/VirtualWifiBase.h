#pragma once
#include "stdafx.h"
#include "VirtualWifiMac.h"
#include "VirtualWifiPeer.h"
#define __midl

class VirtualWifiBase:virtual public VirtualWifiException
{
private:
	static CONST_STR SZ_INTI_EEROR;
	static const DWORD CLIENTVERSION_WIN7;
	WLAN_HOSTED_NETWORK_STATUS m_network_status;
	PWLAN_HOSTED_NETWORK_STATUS* m_pnetwork_status;
protected:
	bool m_binit;
	bool m_bstart;
	HANDLE m_clienthandle;
	CONST_STR m_sz_fail_resason;
	WLAN_HOSTED_NETWORK_REASON m_failreason;
public:
	void set_mode(bool bmode);
	void set_netinfo(NetInfo& netinfo);
	void refresh_wifi();
	void init_handle();
	void close_handle();
	bool is_support_wifi();
	PWLAN_HOSTED_NETWORK_STATUS* query_status();
	VirtualWifiBase(void);
	~VirtualWifiBase(void);
};

