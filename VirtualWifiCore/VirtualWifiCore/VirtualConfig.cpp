#include "stdafx.h"

pModifyConfig ModifyConfig;
pParseConfig ParseConfig;
pParseNetInfo ParseNetInfo;
pParseSoft   ParseSoft;
pParseNotify ParseNotifyIcon;
pModifySoft ModifySoft;
pModifyNetInfo ModifyNetInfo;
pParsePeerHis ParsePeerHis;

static HMODULE hModule;


bool VirtualWifiConfig_Load()
{
    hModule=LoadLibraryA(CONFIG_DLL_NAME);
	if (hModule==NULL)
	{
		return false;
	}
	ParseConfig=(pParseConfig)GetProcAddress(hModule,PARSECONFIGFUNNAME);
	ParseSoft=(pParseSoft)GetProcAddress(hModule,PARSESOFTFUNNAME);
	ParsePeerHis=(pParsePeerHis)GetProcAddress(hModule,PARSEPEERHIS);
	ParseNotifyIcon=(pParseNotify)GetProcAddress(hModule,PARSENOTIFYICONFUNNAME);
    ModifyConfig=(pModifyConfig)GetProcAddress(hModule,MODIFYCONFIGFUNNAME);
	ModifySoft=(pModifySoft)GetProcAddress(hModule,MODIFYSOFTFUNNAME);
	ParseNetInfo=(pParseNetInfo)GetProcAddress(hModule,PARSENETINFOFUNNAME);
	ModifyNetInfo=(pModifyNetInfo)GetProcAddress(hModule,MODIFYNETINFOFUNNAME);
	return true;
}


void VirtualWifiConfig_Release()
{
	FreeLibrary(hModule);
}