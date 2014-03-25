#include "StdAfx.h"
#include "VirtualWifiJudage.h"


VirtualWifiJudage::VirtualWifiJudage(void)
{
}

bool VirtualWifiJudage::is_local(const char* szip)
{
	return !strcmp(szip,LOCAL_IP);
}
CLIENTTYPE VirtualWifiJudage::get_client_type(char* szrecv)
{
	if (!strcmp(MAIN_SOCKET_ID,szrecv))
	{
		return CLIENTTYPE_MAIN;
	}
	else if (!strcmp(CONFIG_SOCKET_ID,szrecv))
	{
		return CLIENTTYPE£ßCONFIG;
	}
	else if (!strcmp(FLOW_MONITOR_ID,szrecv))
	{
		return CLIENTYPE_FLOW;
	}
	return CLIENTTYPE_UNKOWN;
}

VirtualWifiJudage::~VirtualWifiJudage(void)
{
}
