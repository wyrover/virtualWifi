// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <objbase.h>
#include <netcon.h>
#include <stdio.h>
#include <NetCon.h>
#include <locale.h>
#include <wlanapi.h>
#include <WinNetWk.h>
#include <netlistmgr.h>
#include <ShObjIdl.h>
#pragma comment (lib, "wlanapi.lib")
#pragma comment (lib,"Mpr.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#define NAT_PROTOCOL_TCP 6
#define NAT_PROTOCOL_UDP 17


int _tmain(int argc, _TCHAR* argv[])
{
/*	HRESULT hr=CoInitialize (NULL);
hr=CoInitializeSecurity (NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_PKT,RPC_C_IMP_LEVEL_IMPERSONATE,NULL, EOAC_NONE, NULL);
INetSharingManager * pNSM = NULL;
 hr = ::CoCreateInstance (__uuidof(NetSharingManager),NULL,CLSCTX_ALL,__uuidof(INetSharingManager),(void**)&pNSM);
if (!pNSM)
wprintf (L"failed to create NetSharingManager object\r\n");

INetConnection * pNC = NULL; 
INetSharingEveryConnectionCollection * pNSECC = NULL;
 hr = pNSM->get_EnumEveryConnection (&pNSECC);*/
	HMODULE hModule=LoadLibraryA("VirtualWifiCore.dll");
	if (hModule==NULL)
	{
		printf("加载dll失败");
	}
	while (true)
	{
		Sleep(1000);
	}
	return 0;
}

