#include "stdafx.h"

class VirtualWifiSocketBase:virtual public VirtualWifiSoft
{
private:
	WSAEVENT m_eventArray[WSA_MAXIMUM_WAIT_EVENTS];
	SOCKET m_socketArrary[WSA_MAXIMUM_WAIT_EVENTS];
	int m_nClientTotal;
	SOCKET m_acceptSocket;
	sockaddr_in* m_sockaddr_in;
protected:
	const char* GetAcceptIp();//在OnAccept方法中调用,可获取正确的IP地址
	bool AddClient(SOCKET& socket);
protected:
	void CloseSocket(SOCKET& socket);
	static void VirtualWifiSocketBase::CreateSocket(LPVOID param);
public:
	virtual void OnAccept(SOCKET& socket);
	virtual void OnRead(SOCKET& socket);
	virtual void OnClose(SOCKET& socket,int nIndex);
public:
	WSAEVENT* GetEventArrary();
	SOCKET* GetSocketArrary();
	int& GetClientTotal();
	SOCKET& GetAcceptSocket();
	void SetSocketInfo(sockaddr_in& sa);
public:
	VirtualWifiSocketBase();
	bool Start();
	void Stop();
	~VirtualWifiSocketBase();
};