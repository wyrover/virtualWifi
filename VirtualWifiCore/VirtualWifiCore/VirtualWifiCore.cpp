#include "StdAfx.h"
#include "VirtualWifiCore.h"
#include "VirtualWifiService.h"
#include "VirtualWifiRegBase.h"

VirtualWifiCore::VirtualWifiCore()
{
	m_peer_list=new VirtualWifiPeerList();
	m_peer_ip_list=new VirtualWifiPeerList();
}

//启动核心程序
void VirtualWifiCore::run_app(CONST_STR sz_p)
{
	allocation_tasks(TASK_TYPE_CHECK_START);

   	start_check();
	
	//判断是否为开机自启动的
	if(strcmp(AUTO_START_WIFI_PARAMETERS,sz_p))
	{
       
	}
	if(start_server())
	{
		auto_start_wifi();
		//do_with_show_event_ballon(ALREADY_STARTED);
	}
}

void VirtualWifiCore::exit()
{
     stop_wifi();   //关闭无线网络
	 notify_hidden(); //关闭托盘图标
	 modify_config(); //将修改过的配置写入文件
	 modify_soft();
	 ::exit(0);      //调用exit退出
}


bool VirtualWifiCore::start_server()
{
	v_log->write_log_come_to("start_server");
	return this->Start();
}

/////////////////////////////////////////////////////////////
// 如果为自动开启无线网络,则不会启动主界面程序.
///////////////////////////////////////////////////////////

bool VirtualWifiCore::auto_start_wifi()
{
	if (!m_configinfo->AutoStartWifi)  //假如自动启动无线网络,则不启动界面
	{
         start_mainui();
	}
	else
	{
		auto_start_wif_no_ui();
	}
	return false;
}
void VirtualWifiCore::on_lbutton_dowm_notify(POINT& cursorpos)
{
	if (m_mainui_states==MAINUI_STATES_STARTED)
	{
		send_main(ID_SHOW,EMPTYSTRING);
	}
	else 
	{
        start_mainui();// 启动界面程序exe
	}
}

void VirtualWifiCore::on_get_client_list()
{
	if (m_peer_list!=NULL)
	{
		do_with_send_client_list(m_peer_list->get_peer_list());
	}
	
}

#pragma region 处理流量
struct add_peer_ip_thread_param
{
	char sz_ip[IPLEN];
	u_char umac[6];
	u_long ulsize;
	VirtualWifiPeerList* peer_list;
	VirtualWifiPeerList* peer_ip_list;
	link_type lt;
};
void VirtualWifiCore::add_peer_ip_thread(LPVOID param)
{
	add_peer_ip_thread_param* apitp=(add_peer_ip_thread_param*)param;
	VirtualWifiPeerList* peer_list=apitp->peer_list;
	VirtualWifiPeerList* peer_ip_list=apitp->peer_ip_list;

	VirtualWifiPeer* peer=peer_list->find_peer(apitp->umac); //根据mac地址获取peer
	if (peer==NULL)  //流量截获的速度比peer链表获取速度快,可能当时未存在于链表中.
	{
		/*peer=peer_ip_list->find_peer(apitp->sz_ip);
		if (peer==NULL)
		{
			peer=peer_ip_list->add_peer(apitp->sz_ip);
		}
		VirtualWifiFlow* flow=peer->get_flow();
		flow->add_total_flow(apitp->ulsize,apitp->lt);*/
		return;
	}
	peer->set_ip(apitp->sz_ip);

}
void VirtualWifiCore::add_peer_ip(VirtualWifiIp* ip,u_char umac[6],u_long ulsize,link_type lt)
{
	add_peer_ip_thread_param* apitp=(add_peer_ip_thread_param*)malloc(sizeof(add_peer_ip_thread_param));
	strcpy(apitp->sz_ip,ip->get_ip());
	memcpy(apitp->umac,umac,6);
	apitp->peer_list=m_peer_list;
	apitp->peer_ip_list=m_peer_ip_list;
	apitp->lt=lt;
	apitp->ulsize=ulsize;

	_beginthread(add_peer_ip_thread,0,apitp);
}
void VirtualWifiCore::handle_downflow(VirtualWifiIp* vip,u_int usize)
{

}
void VirtualWifiCore::handle_upflow(VirtualWifiIp* vip,u_int usize)
{

}
void VirtualWifiCore::handle_data(struct pcap_pkthdr *header,const u_char *pkt_data)
{
	ip_header* ih=(ip_header*)(pkt_data+14);

	set_ip(ih);

	link_type lt=judage_link_type();

	if (lt==unkown_link_type)
	{
		return;
	}

	VirtualWifiIp* vip=lt==down_link_type?m_dip:m_sip;

	VirtualWifiPeer* peer=m_peer_list->find_peer(vip);

	int iplen=(ih->ver_ihl & 0xf)*4;
	u_int ulen=header->len-iplen;

	if (peer==NULL) //如果客户端链表中未发现
	{
		m_macheadr=(mac_header*)pkt_data;
		u_char* mac=lt==down_link_type?m_macheadr->dadd:m_macheadr->sadd;
		add_peer_ip(vip,mac,ulen,lt);
	}
	else
	{
		VirtualWifiFlow* flow=peer->get_flow();
		flow->add_total_flow(ulen,lt);
	}

	m_totalflow->add_flow(ulen,lt);

    if (is_timeout(header->ts))
    {
		if (m_configinfo->FlowMonitor&&m_flowgui_open)
		{
			float fdownspeed=m_totalflow->calculate_downspeed(m_dtime);
			float fupspeed=m_totalflow->calculate_upspeed(m_dtime);
			do_with_show_down_flow(fdownspeed);
			do_with_show_up_flow(fupspeed);
		}
		m_totalflow->clear_current();
    }
	
}

void VirtualWifiCore::handle_data_timeout(struct pcap_pkthdr *header)
{
	if (m_totalflow->get_currentdown()==0&&m_totalflow->get_currentup()==0)
	{
		do_with_show_down_flow(0);
		do_with_show_up_flow(0);
		return;
	}

	if (m_configinfo->FlowMonitor&&m_flowgui_open)
	{
		float fdownspeed=m_totalflow->calculate_downspeed(m_dtime);
		float fupspeed=m_totalflow->calculate_upspeed(m_dtime);
		do_with_show_down_flow(fdownspeed);
		do_with_show_up_flow(fupspeed);
	}
	m_totalflow->clear_current();
}

/************************************************************************/
/* 流量监控                                                              */
/************************************************************************/
void VirtualWifiCore::task_count_flow()
{
	if (m_configinfo->FlowMonitor&&!m_flowgui_open)
	{
		start_flowmonitor();
	}
	m_totalflow=new VirtualWifiFlow();

	m_vmae->reset_integrate_pcap_adapter();
	VirtualWifiAdapter* va=m_vmae->get_virtual_adapter();

	if (va==NULL)
	{
		return;
	}
	bool bret=init_pcap(va);
	if (!bret)
	{
		return;
	}
	start_capture_flow();
	delete m_totalflow;
}
#pragma endregion 处理流量
/////////////////////////////////////////////////////////////
// 检测有没有新连接
//////////////////////////////////////////////////////////////
void VirtualWifiCore::task_query_status()
{

	while (m_wifi_states==WIFI_STATUS_STARTED)
	{
		PAUSE(1000);

		PWLAN_HOSTED_NETWORK_STATUS* network_status=query_status();
		
		if ((*network_status)->HostedNetworkState==wlan_hosted_network_active)
		{
			if (m_clientnum!=(*network_status)->dwNumberOfPeers)
			{
				m_clientnum=(*network_status)->dwNumberOfPeers;
				do_with_set_client_num(m_clientnum);
			}

			VirtualWifiPeerList new_peer_list=*m_peer_list-**network_status;

			do_with_show_new_peer_ballon(new_peer_list.get_peer_list());

		}

	}

	m_peer_list->clear_all();
	

	m_clientnum=0;
}

//当主界面的socket连接时
void VirtualWifiCore::on_main_ui_connection()
{
	v_log->write_log_come_to("VirtualWifiCommunication::OnMainSocketConnection()");
	v_log->write_log("recv client frist link");

	m_mainui_states=MAINUI_STATES_STARTED;
	
	init_wifi();
}
void VirtualWifiCore::on_flow_connection()
{
	if (!m_configinfo->FlowMonitor)
	{
		do_with_close_flow_ui();
		return;
	}
	m_flowgui_open=true;
    check_flowmonitor_pos();
	do_with_reset_flow_ui_pos(m_softinfo->nflowmonitor_x,m_softinfo->nflowmonitor_y);
}
void VirtualWifiCore::on_flow_close()
{
	m_flowgui_open=false;
}
void VirtualWifiCore::on_flow_reset_pos()
{
	POINT pos=parse_pos(m_pcommand_struct->m_command);
	m_softinfo->nflowmonitor_x=pos.x;
	m_softinfo->nflowmonitor_y=pos.y;
}
void VirtualWifiCore::on_flow_read(CONST_STR sz_c,int nlen)
{
	analysis_flow(sz_c,nlen);
}
void VirtualWifiCore::on_main_ui_read(CONST_STR sz_c,int nlen)
{
	analysis(sz_c,nlen);
}
void VirtualWifiCore::on_main_ui_close()
{
	m_mainui_states=MAINUI_STATES_UNSTART;
}
void VirtualWifiCore::on_closebutton_down()
{
	exit();
}
void VirtualWifiCore::on_refresh_share_net()
{
	if (m_wifi_states!=WIFI_STATUS_STARTED)
	{
		TRYEXCEPTION_BEGIN
		init_wifi_adapter();
		init_wifi_selected_adapter();
		TRYEXCEPTION_END
			CATCH(VirtualWifiException& e)
			DEAL_BEGIN
			send_main(ID_TIPINFO,e.get_error_message());
		DEAL_END
	}
}


//当收到开启无线网络命令
void VirtualWifiCore::on_start_wifi()
{
	allocation_tasks(TASK_TYPE_START_WIFI);
}

void VirtualWifiCore::on_stop_wifi()
{
	v_log->write_log("recv stop wifi command");
	TRYEXCEPTION_BEGIN

	stop_wifi();

	set_notify_tip();

	set_wifi_status(WIFI_STATUS_UNSTART);

	do_with_stop_wifi_success();

	TRYEXCEPTION_END
		CATCH(VirtualWifiException& e)
		DEAL_BEGIN

	do_with_stop_wifi_fail(e.get_error_message());

	set_wifi_status(WIFI_STATUS_STOP_FAIL);

	v_log->write_log("stop wifi fail");
	//关闭无线网络失败
	DEAL_END

   stop_dynamic_show();
	
}
void VirtualWifiCore::on_config_flow_monitor()
{
	m_configinfo->FlowMonitor=get_config_bool_value(m_pcommand_struct->m_command);
	if (m_configinfo->FlowMonitor&&!m_flowgui_open&&m_wifi_states==WIFI_STATUS_STARTED)
	{
		start_flowmonitor();
	}
	else if (!m_configinfo->FlowMonitor&&m_flowgui_open)
	{
		do_with_close_flow_ui();
	}
}
void VirtualWifiCore::on_config_provincememory()
{
    m_configinfo->ProvinceMemory=get_config_bool_value(m_pcommand_struct->m_command);
}
void VirtualWifiCore::on_config_autorun()
{
	bool bvalue=get_config_bool_value(m_pcommand_struct->m_command);
	if (bvalue)
	{
		AutoRun(m_softinfo->szTitle);
	}
	else
	{
		UnAutoRun(m_softinfo->szTitle);
	}
	m_configinfo->AutoRun=bvalue;
}

void VirtualWifiCore::on_config_auto_start_wifi()
{
	m_configinfo->AutoStartWifi=get_config_bool_value(m_pcommand_struct->m_command);
	if (m_configinfo->AutoRun)
	{
		AutoRun(m_softinfo->szTitle);
	}
}
void VirtualWifiCore::on_config_eventballoontip()
{
	m_configinfo->EventBalloonTip=get_config_bool_value(m_pcommand_struct->m_command);
}


////////////////////////////////////////////////////////////////////////////
//   程序启动检测
//
/////////////////////////////////////////////////////////////////////////////
bool VirtualWifiCore::start_check()
{
	if (!init_check())
	{
		return false;
	}
	return true;
}


bool VirtualWifiCore::get_reg_info()
{
	CONST_STR sz_guid=m_reg.get_value(SZ_VIRTUALWIFIADAPTERGUID);
	if (sz_guid==EMPTYSTRING)
	{
	   create_new_reg();
       return false;
	}
	m_virtualwifiadapter_guid=new char[strlen(sz_guid)+1];
	strcpy(m_virtualwifiadapter_guid,sz_guid);
	v_log->write_log("get guid is ",m_virtualwifiadapter_guid);
	return true;
}


//假如不存在,则判定是否支持承载网络
bool VirtualWifiCore::create_new_reg()
{
	VirtualWifiDriver  driver;
	if(!driver.get_is_support_wifi())
	{
		MessageBox(NULL,IS_NOT_SUPPORT_WIFI,get_title(),MB_OK);
	    exit();
	    return false;
	}
	do_with_show_event_ballon(CONST_SZ_FRIST_START_APP);
	TRYEXCEPTION_BEGIN
		if(allow_wifi_cmd())
		{
			Sleep(1200);

			start_wifi_cmd();

			string str_guid=GetVirtualAdapterGuid();
			CONST_STR sz_guid=str_guid.c_str();

			m_virtualwifiadapter_guid=new char[strlen(sz_guid)+1];
			strcpy(m_virtualwifiadapter_guid,sz_guid);
			if(!m_reg.set_value(SZ_VIRTUALWIFIADAPTERGUID,sz_guid))
			{
				throw_self();
			}
			
		}
		TRYEXCEPTION_END
			CATCH(VirtualWifiException& e)
			DEAL_BEGIN
			MessageBox(NULL,e.get_error_message(),get_title(),NULL);
			return false;
			DEAL_END
	stop_wifi_cmd();
    return true;
}

//在不启动主界面的情况下,启动无线网络
void VirtualWifiCore::auto_start_wif_no_ui()
{
	TRYEXCEPTION_BEGIN

	find_adapter();

	start_wifi(*m_netinfoex);

	modify_netinfo();

	set_notify_tip(STARTED,m_netinfoex->szSsid,m_netinfoex->szKey);

	do_with_start_wifi_success(false);

	m_wifi_states=WIFI_STATUS_STARTED;

	TRYEXCEPTION_END
		CATCH(VirtualWifiException& e)
		DEAL_BEGIN
		v_log->write_log("start wifi fail");
	stop_wifi();

	do_with_show_fail_reason_ballon(e.get_error_message());

	m_wifi_states=WIFI_STATUS_START_FAIL;
	DEAL_END
}

//检测程序是否正常运行,检测无线网络是否正常
void VirtualWifiCore::task_check_start()
{
	long t1=GetTickCount();//程序段开始前取得系统运行时间(ms)

	long t2=GetTickCount();//程序段结束后取得系统运行时间(ms)

}

bool VirtualWifiCore::check_virtualadapter_ip()
{
	return false;
}
void VirtualWifiCore::task_start_wifi()
{
	v_log->write_log("recv start wifi command");

	TRYEXCEPTION_BEGIN

	start_wifi(*parse_netinfoex(m_pcommand_struct->m_command));

	//check_virtualadapter_ip();

	set_notify_tip(STARTED,m_netinfoex->szSsid,m_netinfoex->szKey);

	modify_netinfo();

	set_wifi_status(WIFI_STATUS_STARTED);

	allocation_tasks(TASK_TYPE_QUERY_STATUS);

	allocation_tasks(TASK_TYPE_COUNT_FLOW);

    do_with_start_wifi_success();

	TRYEXCEPTION_END
		CATCH(VirtualWifiException& e)
		DEAL_BEGIN
		v_log->write_log("start wifi fail");

	stop_wifi();
	set_wifi_status(WIFI_STATUS_START_FAIL);
	do_with_start_wifi_fail(e.get_error_message());
	DEAL_END
}

//初始化的一些信息
void VirtualWifiCore::init_wifi_account()
{
	v_log->write_log_come_to("VirtualWifiCommunication::init_wifi_account()");
	list<CONST_STR> lst_account;
	lst_account.push_back(m_netinfoex->szSsid);
	lst_account.push_back(m_netinfoex->szKey);
	v_log->write_log_run_to("init_wifi_account the data is ",m_netinfoex->szSsid);
	send_main(ID_WIFIACCOUNT,lst_account);
}
void VirtualWifiCore::init_wifi_adapter()
{
	v_log->write_log_come_to("void VirtualWifiCommunication::init_wifi_adapter()");
	do_with_clear_share_net();
	send_main(ID_ADAPTERINFO,get_connected_adapters());	
}
void VirtualWifiCore::init_wifi_selected_adapter()
{
	v_log->write_log_come_to("VirtualWifiCommunication::init_wifi_selected_adapter()");
	string str_adapter=intelligent_net_adapters();
	send_main(ID_SETSELECTEDADAPTER,str_adapter.c_str());
}
void VirtualWifiCore::init_wifi_select_adapter_has_share()
{
	send_main(ID_SETSELECTEDADAPTER,m_netinfoex->szAdapter);
}
void VirtualWifiCore::init_wifi_soft()
{
	v_log->write_log_come_to("VirtualWifiCommunication::init_wifi_soft()");
	//title信息
	CONST_STR sz_version_title=get_mainui_title();
	send_main(ID_SETTITLE,sz_version_title);
	//背景图片路径
	v_log->write_log("send back ground");
	send_main(ID_BACK,m_softinfo->szBack);
}

void VirtualWifiCore::init_wifi_config()
{
	//将设置界面的信息发送过去
	char sz_config[6];
	sz_config[0]=m_configinfo->AutoRun?'1':'0';
	sz_config[1]=m_configinfo->FlowMonitor?'1':'0';
	sz_config[2]=m_configinfo->AutoStartWifi?'1':'0';
	sz_config[3]=m_configinfo->HasNewClientBalloonTip?'1':'0';
	sz_config[4]=m_configinfo->ProvinceMemory?'1':'0';
	sz_config[5]=m_configinfo->EventBalloonTip?'1':'0';
	send_main(ID_CONFIG,sz_config);
}
void VirtualWifiCore::init_wifi()
{
	v_log->write_log_come_to("VirtualWifiCommunication::init_wifi()");

	TRYEXCEPTION_BEGIN
	init_wifi_adapter();

	if (m_wifi_states==WIFI_STATUS_STARTED)
	{
		init_wifi_select_adapter_has_share();
		do_with_mainui_started();
		do_with_set_client_num(m_clientnum);
	}
	else
	{
		init_wifi_selected_adapter();
	}

	TRYEXCEPTION_END
		CATCH(VirtualWifiException& e)
		DEAL_BEGIN
		send_main(ID_TIPINFO,e.get_error_message());
	DEAL_END

	init_wifi_config();
	init_wifi_soft();
	init_wifi_account();

	do_with_show_main();
}

VirtualWifiCore::~VirtualWifiCore(void)
{
}
