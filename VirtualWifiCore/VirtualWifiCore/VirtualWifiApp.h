#pragma once
#include "stdafx.h"

//无线网络的状态
enum WIFI_STATUS
{
	WIFI_STATUS_STARTED,
	WIFI_STATUS_UNSTART,
	WIFI_STATUS_START_FAIL,
	WIFI_STATUS_STOP_FAIL
};

enum MAINUI_STATES
{
   MAINUI_STATES_STARTED,
   MAINUI_STATES_UNSTART
};

//管理主界面的类
class VirtualWifiApp:virtual public VirtualWifiSoft
{
protected:
	WIFI_STATUS m_wifi_states;
    MAINUI_STATES m_mainui_states;
	CONST_STR m_tip_info;
protected:
	bool m_flowgui_open;
protected:
	bool start_mainui();
	bool start_flowmonitor();
public:
	void set_wifi_status(WIFI_STATUS wifi_status);
	VirtualWifiApp(void);
	~VirtualWifiApp(void);
};

