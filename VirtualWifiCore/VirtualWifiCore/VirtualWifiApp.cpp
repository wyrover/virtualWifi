#include "StdAfx.h"
#include "VirtualWifiApp.h"


VirtualWifiApp::VirtualWifiApp(void)
{
	m_wifi_states=WIFI_STATUS_UNSTART;
	m_mainui_states=MAINUI_STATES_UNSTART;
	m_tip_info=EMPTYSTRING;
	m_flowgui_open=false;
}

bool VirtualWifiApp::start_mainui()
{
	char sz_port[MAX_LEN];
	sprintf(sz_port,"%d",m_softinfo->sPort);
	v_log->write_log("the port is ",sz_port);
	int ret=(int)ShellExecute(NULL,"open",m_softinfo->szMainUi,sz_port,NULL,0);
	bool is_start=ret>32;
	if(is_start)
	{
        m_mainui_states=MAINUI_STATES_STARTED;
	}
	return is_start;
}
bool VirtualWifiApp::start_flowmonitor()
{
	char sz_port[MAX_LEN];
	sprintf(sz_port,"%d",m_softinfo->sPort);
	v_log->write_log("start_flowmonitor the port is ",sz_port,m_softinfo->szFlowMonitorUi);
	int ret=(int)ShellExecute(NULL,"open",m_softinfo->szFlowMonitorUi,sz_port,NULL,0);
	bool is_start=ret>32;
	return is_start;
}
void VirtualWifiApp::set_wifi_status(WIFI_STATUS wifi_status)
{
	m_wifi_states=wifi_status;
}
VirtualWifiApp::~VirtualWifiApp(void)
{
}
