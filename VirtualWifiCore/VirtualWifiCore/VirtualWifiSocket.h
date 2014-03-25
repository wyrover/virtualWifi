#include "stdafx.h"
#include "VirtualWifiAnalysis.h"
#include "VirtualWifiApp.h"

class VirtualWifiSocket:public VirtualWifiSocketBase
	,public VirtualWifiJudage
	,virtual public VirtualWifiApp
{
private:
	static const int naccepttimeout;
	static const int nbufferlen;
private:
	VirtualWifiCommandOut* m_command_out;
	VirtualWifiCommandIn*  m_command_in;
	VirtualWifiCommandOut* m_flow_command_out;
protected:
	void OnAccept(SOCKET& socket);
	void OnRead(SOCKET& socket);
	void OnClose(SOCKET& socket,int nIndex);
	char* m_send;     //发送缓冲区
	int  m_send_len;
	char* m_buffer;   //接收缓冲区
	int m_buffer_len;
protected:
	SOCKET m_flowsocket;
	SOCKET m_mainsocket;
	SOCKET m_configsocket;
protected:
	int recv_data(SOCKET& socket);
	int recv_main_data();
	int send_main(char cid,char* mes,CODING coding=ASCIICODING);
	int send_main(char cid,CONST_STR mes,CODING coding=ASCIICODING);
	int send_main(char cid,list<CONST_STR> lst_mes,CODING coding=ASCIICODING);
	int send_main(char cid,wstring mes,CODING coding=UNICODECODING);
	int send_main(char cid,list<wstring> lst_mes,CODING coding=UNICODECODING);
protected:
	int send_flow(link_type lt,float fspeed,CODING coding=ASCIICODING);
	int send_flow(char cid,CONST_STR sz_c,CODING coding=ASCIICODING);
public:
	virtual void on_main_ui_connection()=0;
	virtual void on_flow_connection()=0;
	virtual void on_flow_read(CONST_STR sz_c,int nlen)=0;
	virtual void OnConfigSocketConnection();
	virtual void on_main_ui_read(CONST_STR sz_c,int nlen)=0;
	virtual void OnConfigSocketRead();
	virtual void on_main_ui_close()=0;
	virtual void on_flow_close()=0;
	virtual void OnConfigSocketClose();
	VirtualWifiSocket();
	~VirtualWifiSocket();
};