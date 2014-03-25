#include "StdAfx.h"
#include "VirtualWifiBase.h"


const DWORD VirtualWifiBase::CLIENTVERSION_WIN7=2;
CONST_STR VirtualWifiBase::SZ_INTI_EEROR="初始化失败!";

VirtualWifiBase::VirtualWifiBase(void)
{
    m_pnetwork_status=new PWLAN_HOSTED_NETWORK_STATUS();
	init_handle();  
}
//初始化wlan句柄
void VirtualWifiBase::init_handle()
{
	DWORD dwNegotiatedVersion=0;
	DWORD ret=WlanOpenHandle(CLIENTVERSION_WIN7,NULL,&dwNegotiatedVersion,&m_clienthandle);
	if (ret!=ERROR_SUCCESS)
	{
		set_message(SZ_INTI_EEROR);
		throw_self();
	}
	m_binit=true;
}
void VirtualWifiBase::refresh_wifi()
{
	DWORD ret=WlanHostedNetworkRefreshSecuritySettings(m_clienthandle,&m_failreason,NULL);
	if (ret!=ERROR_SUCCESS)
	{
		set_message(SZ_INTI_EEROR);
		throw_self();
	}
}
void VirtualWifiBase::set_mode(bool bmode)
{
	BOOL b=bmode?TRUE:FALSE;
	WlanHostedNetworkSetProperty(m_clienthandle,wlan_hosted_network_opcode_enable,sizeof(BOOL),&b,&m_failreason,NULL);
}
void VirtualWifiBase::close_handle()
{
	WlanCloseHandle(m_clienthandle,NULL);
	m_binit=false;
}
bool VirtualWifiBase::is_support_wifi()
{
	BOOL is_support_wifi=TRUE;
	WLAN_OPCODE_VALUE_TYPE value_type;
	DWORD datasize=sizeof(BOOL);
	PVOID datatemp=(PVOID*)&is_support_wifi;
	PVOID* databuffer=&datatemp;
	WlanHostedNetworkQueryProperty(m_clienthandle,wlan_hosted_network_opcode_enable,&datasize,databuffer,
		&value_type,NULL);
	return (bool)is_support_wifi;
}

void VirtualWifiBase::set_netinfo(NetInfo& netinfo)
{

}
PWLAN_HOSTED_NETWORK_STATUS* VirtualWifiBase::query_status()
{
	WlanHostedNetworkQueryStatus(m_clienthandle,m_pnetwork_status,NULL);
    WLAN_HOSTED_NETWORK_PEER_STATE peer=(*m_pnetwork_status)->PeerList[(*m_pnetwork_status)->dwNumberOfPeers-1];
	return m_pnetwork_status;
}
VirtualWifiBase::~VirtualWifiBase(void)
{
}
