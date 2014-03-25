#pragma once
#include "stdafx.h"

//开启所需要的服务
class VirtualWifiService
{
private:
	SC_HANDLE m_hSC;
public:
	DWORD CheckServiceStatus(CONST_STR pServiceName);
	DWORD StartService(CONST_STR pServiceName);
	DWORD StopService(CONST_STR pServiceName);
	void  PrintAllService();
	VirtualWifiService(void);
	~VirtualWifiService(void);
};

