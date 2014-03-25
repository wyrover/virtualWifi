#pragma once
#include "stdafx.h"
#include "VirtualWifiInit.h"
#include "VirtualWifiApp.h"
#include "VirtualWifiDriver.h"
#include "VirtualWifiFlow.h"

class VirtualWifiCore:public VirtualWifiCommunication
	,public VirtualWifiAnalysis
	,public VirtualWifiInit
	,public VirtualWifiTask
	,public VirtualWifiCountFlow
{
private:
	VirtualWifiPeerList* m_peer_list;
	VirtualWifiPeerList* m_peer_ip_list;
	
	int m_clientnum;
	VirtualWifiFlow* m_totalflow;
private: //程序开启检测
	bool start_check();
	bool get_reg_info();
	bool create_new_reg();
private:
	bool check_virtualadapter_ip();
protected:
	void task_check_start();
	void task_start_wifi();
	void task_query_status();
	void task_count_flow();
protected:
	virtual void handle_data(struct pcap_pkthdr *header,const u_char *pkt_data);
	virtual void handle_data_timeout(struct pcap_pkthdr *header);
protected:
	 void init_wifi(); //当主界面第一次连接,需要发送的信息
	 void init_wifi_account();   //获取当前的帐号
	 void init_wifi_adapter();
	 void init_wifi_selected_adapter();
	 void init_wifi_soft();    //发送软件信息
	 void init_wifi_config();
	 void init_wifi_select_adapter_has_share();
	 void auto_start_wif_no_ui();
protected:
	 void on_start_wifi();
	 void on_stop_wifi();
	 void on_config_autorun();
	 void on_config_auto_start_wifi();
	 void on_config_eventballoontip();
	 void on_config_provincememory();
	 void on_config_flow_monitor();
	 void on_get_client_list();
	 void on_closebutton_down();
	 void on_flow_reset_pos();
private:
	void exit();
private:
	bool auto_start_wifi();
private:
	void handle_downflow(VirtualWifiIp* vip,u_int usize);
	void handle_upflow(VirtualWifiIp* vip,u_int usize);
	static void add_peer_ip_thread(LPVOID param);
	void add_peer_ip(VirtualWifiIp* ip,u_char umac[6],u_long ulsize,link_type lt);
protected:
	void on_main_ui_connection();
	void on_main_ui_close();
	void on_main_ui_read(CONST_STR sz_c,int nlen);
	void on_refresh_share_net();
    void on_flow_connection();
    void on_flow_read(CONST_STR sz_c,int nlen);
	void on_flow_close();
public:
	void run_app(CONST_STR sz_p);
	void on_lbutton_dowm_notify(POINT& cursorpos);
	bool start_server();
	VirtualWifiCore();
	~VirtualWifiCore(void);
};

