#pragma once
#include "stdafx.h"
#include "VirtualWifiCommandIn.h"

//对主界面发送过来的字符流进行分析
//接收缓冲区为m_szcommand
class VirtualWifiAnalysis     
{
private:
	typedef VirtualWifiCommandIn::p_command_struct p_command_struct;
protected:
	p_command_struct m_pcommandstruct;
	bool get_config_bool_value(CONST_STR sz_c);     //参数为Command结构中的数据部分          
public:
	void analysis();
	void analysis(CONST_STR sz_c,int nrecv);
	void analysis_flow(CONST_STR sz_c,int nrecv);

	virtual void on_start_wifi()=0; //当接收到开启无线网络的命令
	virtual void on_stop_wifi()=0; //当接收到关闭无线网络的命令
	virtual void on_config_autorun()=0;  //当接收到点击配置界面开机启动项
	virtual void on_refresh_share_net()=0;
	virtual void on_config_auto_start_wifi()=0;
	virtual void on_config_eventballoontip()=0;
	virtual void on_get_client_list()=0;
	virtual void on_closebutton_down()=0;
	virtual void on_config_provincememory()=0;
	virtual void on_config_flow_monitor()=0;
	virtual void on_flow_reset_pos()=0;
	VirtualWifiAnalysis(void);
	~VirtualWifiAnalysis(void);
};

