#include "StdAfx.h"
#include "VirtualWifiCommunication.h"
#include <process.h>


VirtualWifiCommunication::VirtualWifiCommunication(void)
{
	m_pcommand_struct=(p_command_struct)m_buffer;
}

VirtualWifiCommunication::~VirtualWifiCommunication(void)
{

}

void VirtualWifiCommunication::do_with_warning_info()
{
	if (m_warninginfo!=EMPTYSTRING)
	{
		do_with_tipinfo(m_warninginfo);
		m_warninginfo=EMPTYSTRING;
	}
}
void VirtualWifiCommunication::do_with_start_wifi_success(CONST_STR sz_ssid/* =EMPTYSTRING */,bool b_send)
{
	char sz_buffer[MAX_LEN];
	char* sz_tempssid=NULL;
	if (sz_ssid==EMPTYSTRING||sz_ssid==NULL)
	{
		sz_tempssid=m_netinfoex->szSsid;
	}
	sprintf(sz_buffer,CONST_SZ_START_WIFI_SUCCESS,sz_tempssid);
	if (b_send)
	{
	   send_main(ID_STARTWIFISUCCESS,sz_buffer);
	}
	
	do_with_show_event_ballon(sz_buffer);

	do_with_warning_info();
}
void VirtualWifiCommunication::do_with_mainui_started()
{
	char sz_buffer[MAX_LEN];

	sprintf(sz_buffer,CONST_SZ_START_WIFI_SUCCESS,m_netinfoex->szSsid);

	send_main(ID_STARTWIFISUCCESS,sz_buffer);
}
void VirtualWifiCommunication::do_with_start_wifi_fail(CONST_STR sz_e,bool b_send)
{
	char sz_buffer[MAX_LEN];
	sprintf(sz_buffer,ERROR_MES_START_WIFI_FAIL,m_netinfoex->szSsid);
	do_with_show_ballon(sz_buffer);
	if (b_send)
	{
		send_main(ID_STARTFAIL,EMPTYSTRING);
		if (sz_e!=ERROR_MES_START_WIFI_FAIL)
		{
			do_with_tipinfo(sz_e);
			return;
		}
		do_with_tipinfo(sz_buffer);
	}
	
}
void VirtualWifiCommunication::do_with_show_event_ballon(CONST_STR sz_c,bool b_send)
{
	if (m_configinfo->EventBalloonTip)
	{
		this->show_balloon(get_title(),sz_c);
	}
}
void VirtualWifiCommunication::do_with_show_main()
{
	send_main(ID_SHOW,EMPTYSTRING);//发送显示界面命令
}
void VirtualWifiCommunication::do_with_clear_share_net()
{
	send_main(ID_CLEAR_SHARE_NET,EMPTYSTRING);
}
void VirtualWifiCommunication::do_with_stop_wifi_success()
{
	char sz_buffer[MAX_LEN];
	sprintf(sz_buffer,CONST_SZ_STOP_WIFI_SUCCESS,m_netinfoex->szSsid);
	send_main(ID_STOPWIFISUCCESS,EMPTYSTRING);
	do_with_tipinfo(sz_buffer);
	do_with_set_client_num(0);
	do_with_show_event_ballon(sz_buffer);
	do_with_warning_info();
}
void VirtualWifiCommunication::do_with_stop_wifi_fail(CONST_STR sz_e,bool b_send)
{
	do_with_tipinfo(sz_e);
	send_main(ID_STOPWIFISUCCESS,EMPTYSTRING);
}
void VirtualWifiCommunication::do_with_show_new_peer_ballon(list<VirtualWifiPeer*>& peer_list)
{
	if (m_configinfo->HasNewClientBalloonTip)
	{
		list<VirtualWifiPeer*>::iterator it_peer_list;
		char sz_buffer[MAX_LEN];
		for (it_peer_list=peer_list.begin();it_peer_list!=peer_list.end();++it_peer_list)
		{
			sprintf(sz_buffer,HAS_NEW_CLIENT_LINK,(*it_peer_list)->get_mac()->string());
			this->show_balloon(get_title(),sz_buffer);
		}
	}
}
void VirtualWifiCommunication::do_with_show_fail_reason_ballon(CONST_STR sz_r)
{
	char sz_buffer[MAX_LEN];
	sprintf(sz_buffer,BALLON_SHOW_FAIL,m_netinfoex->szSsid);
	if (sz_r!=EMPTYSTRING)
	{
		strcat(sz_buffer,sz_r);
	}
	
	do_with_show_ballon(sz_buffer);
}
void VirtualWifiCommunication::do_with_show_ballon(CONST_STR sz_c)
{
	this->show_balloon(get_title(),sz_c);
}
void VirtualWifiCommunication::do_with_send_client_list(list<VirtualWifiPeer*>& peer_list)
{
	list<VirtualWifiPeer*>::iterator it_peer_list;
	char sz_buffer[MAX_LEN];
	int peercount=peer_list.size();
	for (it_peer_list=peer_list.begin();it_peer_list!=peer_list.end();++it_peer_list)
	{
		string str_peer=(*it_peer_list)->to_string();
		send_main(ID_SEND_CLIENT_LIST,str_peer.c_str());
		PAUSE(1000/peercount);
	}
}
void VirtualWifiCommunication::do_with_set_client_num(int n_num)
{
	char sz_buffer[GENERALLEN];
	sprintf(sz_buffer,"%d",n_num);
	send_main(ID_SET_CLIENT_NUM,sz_buffer);
}
void VirtualWifiCommunication::do_with_tipinfo(CONST_STR sz_t)
{
	send_main(ID_TIPINFO,sz_t);
}

void VirtualWifiCommunication::do_with_show_down_flow(float fspeed)
{
	send_flow(down_link_type,fspeed);
}
void VirtualWifiCommunication::do_with_close_flow_ui()
{
	send_flow(ID_EXIT,EMPTYSTRING);
}
void VirtualWifiCommunication::do_with_reset_flow_ui_pos(int x,int y)
{
	char sz_send[GENERALLEN];
	sprintf(sz_send,"%d%s%d",x,SEPARATOR,y);
	send_flow(ID_RESETPOS,sz_send);
}
void VirtualWifiCommunication::do_with_show_up_flow(float fspeed)
{
	send_flow(up_link_type,fspeed);
}