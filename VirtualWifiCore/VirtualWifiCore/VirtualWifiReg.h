#pragma once
#include "stdafx.h"
#include "VirtualWifiRegBase.h"

class VirtualWifiReg:public VirtualWifiRegBase
{
private: 
	static CONST_STR SZ_REG_PATH_VIRTUALWIFI; //虚拟网卡的注册表路径
	static char* SZ_REG_VALUE_IP;
	static CONST_STR SZ_REG_KEYNAME_IPADDRESS;  //ip键名
	static CONST_STR SZ_REG_KEYNAME_NAMESERVER; //dns键名
	static CONST_STR SZ_REG_KEYNAME_SUBNETMASK; //子网掩码键名
	static CONST_STR SZ_REG_VALUE_SUBNETMASK; //子网掩码
	static CONST_STR SZ_REG_VALUE_DNS;   //dns地址 

public:
	bool open_virtual_adapter_key(CONST_STR key_name);
	bool set_subnetmask();
	bool set_dns();
	VirtualWifiReg(void);
	~VirtualWifiReg(void);
};

