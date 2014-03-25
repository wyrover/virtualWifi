#pragma once
#include "stdafx.h"
#include "VirtualWifiErrorMes.h"
#include "VirtualWifiBase.h"

class VirtualWifiAchieveBase:virtual public VirtualWifiConfig
	,virtual public VirtualWifiBase
	 ,virtual public VirtualWifiConst
	 ,public VirtualWifiManageAdapter
{
private:
	static CONST_STR SET_SUCCESS;
	static CONST_STR SET_SUCCESS_I;
	static CONST_STR START_SUCCESS;
	static CONST_STR STOP_SUCCESS;
	static CONST_STR DISALLOW_SUCCESS;
private:
	static const DWORD CLIENTVERSION_WIN7;
	static char* SZ_SET_SSID_KEY_CMD;
	static CONST_STR SZ_DISALLOW_WIFI;
	static CONST_STR SZ_ALLOW_WIFI;
	static CONST_STR SZ_START_WIFI; //启动无线承载网络命令
	static CONST_STR SZ_STOP_WIFI;
private:
	void analysis_fail_reason();
public:
	bool start_wifi_cmd();  //用cmd命令开启
	bool StartWifi();  //用api函数开启
	bool stop_wifi_cmd();
    bool StopWifi();
    bool SetSsidAndKey(char* szSsid,char* szKey);
	bool AutoRun(CONST_STR start_name);  //设置开机启动
	bool UnAutoRun(CONST_STR start_name);                    //删除开机启动项
	bool disallow_wifi_cmd();                       //删除虚拟网卡
	bool allow_wifi_cmd();
	bool set_adapter_info();   //设置ip.dns
	VirtualWifiAchieveBase();
	~VirtualWifiAchieveBase();
};

