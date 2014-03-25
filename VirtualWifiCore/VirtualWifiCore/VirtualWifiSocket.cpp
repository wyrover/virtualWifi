#include "StdAfx.h"

const int VirtualWifiSocket::naccepttimeout=360;
const int VirtualWifiSocket::nbufferlen=1024;


VirtualWifiSocket::VirtualWifiSocket()
{
	m_command_out=new VirtualWifiCommandOut();
	m_command_in=new VirtualWifiCommandIn();
	m_flow_command_out=new VirtualWifiCommandOut();

	m_buffer=m_command_in->get_command_buffer();
	m_buffer_len=m_command_in->get_command_all_len();

	m_send=m_command_out->get_command_buffer();
	m_send_len=m_command_out->get_command_all_len();
}

void VirtualWifiSocket::OnAccept(SOCKET& socket)
{
	v_log->write_log_come_to("VirtualWifiSocket::OnAccept(SOCKET& socket)");
	if (is_local(GetAcceptIp()))
	{
		//分析连接来的socket
		//setsockopt(socket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&naccepttimeout,sizeof(int));
		//因为,socket是非阻塞模式产生的,所以recv好像也是非阻塞了
		Sleep(naccepttimeout);
		int nrecv=recv_data(socket);
		v_log->write_log_run_to("the receive data is",m_buffer);
		CLIENTTYPE clienttype=get_client_type(m_buffer);
		if (nrecv>0&&clienttype!=CLIENTTYPE_UNKOWN)
		{
			if (clienttype==CLIENTTYPE_MAIN)
			{
				v_log->write_log_success("check CLIENTTYPE_MAIN");
				m_mainsocket=socket;
				on_main_ui_connection();
			}
			else if (clienttype==CLIENTTYPE＿CONFIG)
			{
				m_configsocket=socket;
				OnConfigSocketConnection();
			}
			else if (!m_flowgui_open&&clienttype==CLIENTYPE_FLOW)
			{
				m_flowsocket=socket;
				on_flow_connection();
			}
			else
			{
				CloseSocket(socket);
				return;
			}
			VirtualWifiSocketBase::OnAccept(socket);
			return;
		}
	}
	CloseSocket(socket);
}

void VirtualWifiSocket::OnRead(SOCKET& socket)
{
	int nret=recv_data(socket);
	if (m_mainsocket==socket)
	{
		on_main_ui_read(m_buffer,nret);
	}
	else if (m_configsocket==socket)
	{
		OnConfigSocketRead();
	}
	else if(m_flowsocket==socket)
	{
		on_flow_read(m_buffer,nret);
	}
}
void VirtualWifiSocket::OnClose(SOCKET& socket,int nIndex)
{
	if (m_mainsocket==socket)
	{
		on_main_ui_close();
	}
	else if (m_configsocket==socket)
	{
		OnConfigSocketClose();
	}
	else if (m_flowsocket==socket)
	{
		on_flow_close();
	}
	VirtualWifiSocketBase::OnClose(socket,nIndex);
}
int VirtualWifiSocket::recv_data(SOCKET& socket)
{
	memset(m_buffer,0,nbufferlen);
	return recv(socket,m_buffer,nbufferlen,0);
}
int VirtualWifiSocket::recv_main_data()
{
	memset(m_buffer,0,nbufferlen);
	return recv(m_mainsocket,m_buffer,nbufferlen,0);
}


void VirtualWifiSocket::OnConfigSocketConnection()
{

}

void VirtualWifiSocket::OnConfigSocketRead()
{

}

void VirtualWifiSocket::OnConfigSocketClose()
{

}

VirtualWifiSocket::~VirtualWifiSocket()
{
	delete[] m_command_out;
}
int VirtualWifiSocket::send_main(char cid,CONST_STR mes,CODING coding/* =ASCIICODING */)
{
	m_command_out->add_id(cid);
	m_command_out->add_command(mes,coding);
	v_log->write_log_run_to("send_main(CONST_STR) the data is ",mes);
	return send(m_mainsocket,m_send,m_command_out->get_add_command_len(),0);
}
int VirtualWifiSocket::send_main(char cid,list<wstring> lst_mes,CODING coding/* =UNICODECODING */)
{
	m_command_out->add_id(cid);
	m_command_out->add_command_lst(lst_mes,coding);
	v_log->write_log_run_to("send_main(list<wstring>) the data is ",(char*)(*lst_mes.begin()).c_str());
	return send(m_mainsocket,m_send,m_command_out->get_add_command_len(),0);
}
int VirtualWifiSocket::send_main(char cid,list<CONST_STR> lst_mes,CODING coding/* =ASCIICODING */)
{
	m_command_out->add_id(cid);
	m_command_out->add_command_lst(lst_mes,coding);
	v_log->write_log_run_to("send_main(list<CONST_STR>) the data is ",*lst_mes.begin());
	return send(m_mainsocket,m_send,m_command_out->get_add_command_len(),0);
}
int VirtualWifiSocket::send_main(char cid,wstring mes,CODING coding/* =UNICODECODING */)
{
	m_command_out->add_id(cid);
	m_command_out->add_command(mes.c_str(),coding);
	return send(m_mainsocket,m_send,m_command_out->get_add_command_len(),0);
}
int VirtualWifiSocket::send_main(char cid,char* mes,CODING coding/* =ASCIICODING */)
{
	m_command_out->add_id(cid);
	m_command_out->add_command(mes,coding);
	return send(m_mainsocket,m_send,m_command_out->get_add_command_len(),0);
}

int VirtualWifiSocket::send_flow(link_type lt,float fspeed,CODING coding/*=ASCIICODING*/)
{
	char sz_speed[GENERALLEN];
	sprintf(sz_speed,"%.2f",fspeed);
	m_flow_command_out->add_id(lt);
	m_flow_command_out->add_command(sz_speed,coding);
	return send(m_flowsocket,m_flow_command_out->get_command(),m_flow_command_out->get_add_command_len(),0);
}

int VirtualWifiSocket::send_flow(char cid,CONST_STR sz_c,CODING coding/*=ASCIICODING*/)
{
	char sz_speed[GENERALLEN];
	m_flow_command_out->add_id(cid);
	m_flow_command_out->add_command(sz_c,coding);
	return send(m_flowsocket,m_flow_command_out->get_command(),m_flow_command_out->get_add_command_len(),0);
}