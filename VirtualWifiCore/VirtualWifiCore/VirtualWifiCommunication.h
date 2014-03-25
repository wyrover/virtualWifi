#pragma once
#include "stdafx.h"
#include "VirtualWifiCommandIn.h"
#include "VirtualWifiAnalysis.h"
#include "VirtualWifiTask.h"

class VirtualWifiCommunication:public VirtualWifiSocket
	,virtual public VirtualWifiNotifyIcon
	,virtual protected VirtualWifiIdentifier
	,virtual public VirtualWifiConfig
	,virtual public VirtualWifiNetInfo
	,public VirtualWifiErrorMes
{
protected:
   typedef VirtualWifiCommandBase::VirtualWifiCommandStruct* p_command_struct;
   p_command_struct m_pcommand_struct;
 
private:
      void task_start_wifi();
protected:
	int send_tip(CONST_STR sz_t);
protected:
	//发送主界面信息的方法  b_send表示,是否发送到界面去
	void do_with_start_wifi_success(CONST_STR sz_ssid=EMPTYSTRING,bool b_send=true);
	void do_with_start_wifi_fail(CONST_STR sz_e,bool b_send=true);
	void do_with_tipinfo(CONST_STR sz_t);
	void do_with_show_event_ballon(CONST_STR sz_c,bool b_send=true);
    void do_with_stop_wifi_success();
	void do_with_stop_wifi_fail(CONST_STR sz_e,bool b_send=true);
	void do_with_warning_info(); //检测是否产生警告信息
	void do_with_clear_share_net();
	void do_with_set_client_num(int n_num);
	void do_with_show_new_peer_ballon(list<VirtualWifiPeer*>& peer_list);
	void do_with_send_client_list(list<VirtualWifiPeer*>& peer_list);
	void do_with_show_ballon(CONST_STR sz_c);     //不根据配置来决定 是否显示
	void do_with_show_fail_reason_ballon(CONST_STR sz_r);//以气泡原因显示失败原因
	void do_with_show_main();
	void do_with_mainui_started();
	void do_with_show_down_flow(float fspeed);
	void do_with_show_up_flow(float fspeed);
	void do_with_close_flow_ui();
	void do_with_reset_flow_ui_pos(int x,int y);
public:
	VirtualWifiCommunication(void);
	~VirtualWifiCommunication(void);
};

