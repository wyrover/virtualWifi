#include "stdafx.h"
#include "VirtualWifiCore.h"

VirtualWifiCore* VWC;
VirtualWifiLog* v_log=new VirtualWifiLog();

void VirtualWifiEntry(CONST_STR sz_parameters)
{

	FILE* fpDebugOut = NULL; 
    FILE* fpDebugIn   = NULL; 

	/*
    if(!AllocConsole()) MessageBox(NULL, _T("控制台生成失败。"), NULL, 0); 
    SetConsoleTitle(_T("Debug Window")); 
	_tfreopen_s(&fpDebugOut, _T("CONOUT$"),_T("w"), stdout); 
     _tfreopen_s(&fpDebugIn, _T("CONIN$"), _T("r"), stdin); 
    _tsetlocale(LC_ALL, _T("chs"));
	*/
	v_log->write_log_come_to("entry");
	v_log->write_log("parameters is ",sz_parameters);

	VirtualWifiConfig_Load();
	//VirtualPeerHis *peerhis=new VirtualPeerHis();
	v_log->write_log_success("Load Configdll ");
	VWC=new VirtualWifiCore();
	VWC->run_app(sz_parameters);
}