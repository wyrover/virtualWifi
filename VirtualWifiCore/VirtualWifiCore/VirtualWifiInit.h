#pragma once
#include "stdafx.h"
#include "VirtualWifiRegBase.h"

///////////////////////////////////////////////////////////////
//   判定是否支持承载网络
//   根据注册表,判断是否为第一次启动,并检测操作系统
//   如果第一次启动,则检测虚拟网卡的GUID,并写入注册表 
//   写入的注册表位置为 HKEY_CURRENT_USER\Software
///////////////////////////////////////////////////////////////

class VirtualWifiInit:virtual public VirtualWifiAchieve
	,virtual public VirtualWifiErrorMes
	,virtual public VirtualWifiSoft
	,virtual public VirtualWifiExecuteCmd
{
protected:
	char* m_virtualwifiadapter_guid;
protected:
    virtual void init_wifi()=0; //当主界面第一次连接,需要发送的信息
	virtual void init_wifi_account()=0;   //获取当前的帐号
	virtual void init_wifi_adapter()=0;
	virtual void init_wifi_selected_adapter()=0;
	virtual void init_wifi_soft()=0;    //发送软件信息
	virtual void init_wifi_config()=0;

	//启动时检测
	virtual bool start_check()=0;
protected:
	static CONST_STR SZ_WRITE_PATH;
	static CONST_STR SZ_VIRTUALWIFIADAPTERGUID;
protected:
	VirtualWifiRegBase m_reg;
	VirtualWifiAchieveBase m_achieve;
	CONST_STR m_key_name;
	virtual bool get_reg_info();
	virtual bool create_new_reg();
public:
	VirtualWifiInit();  
	virtual bool init_check();
	~VirtualWifiInit(void);
};

