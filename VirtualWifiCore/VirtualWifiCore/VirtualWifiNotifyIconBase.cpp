#include "stdafx.h"


#define  UID 0x001F


VirtualWifiNotifyIconBase::VirtualWifiNotifyIconBase()
{
	m_uid=UID;
	m_bshow=false;
}
void VirtualWifiNotifyIconBase::InitIcon(HWND hwnd)
{
	m_hwnd=hwnd;
	memset(&m_nd,0,sizeof(NOTIFYICONDATA));
	m_nd.cbSize= sizeof(NOTIFYICONDATA);
	m_nd.hWnd	= hwnd;
	m_nd.uID	= m_uid;
	m_nd.uFlags	= NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
	m_nd.dwInfoFlags=NIIF_USER;
	m_nd.uCallbackMessage	= WM_NOTIFYMES;
}
void VirtualWifiNotifyIconBase::SetInfoIcon(HICON icon)
{
	m_nd.hBalloonIcon=icon;
}
void VirtualWifiNotifyIconBase::SetIcon(HICON hicon)
{
	m_nd.hIcon=hicon;
	if (m_bshow)
	{
		Shell_NotifyIcon(NIM_MODIFY);
	}
}
void VirtualWifiNotifyIconBase::SetTip(const char* szTip)
{
	int szTipLen=strlen(szTip);
	int nCopyLen=sizeof(m_nd.szTip)<szTipLen?sizeof(m_nd.szTip):szTipLen;
	memset(m_nd.szTip,0,sizeof(m_nd.szTip));
	memcpy(m_nd.szTip,szTip,nCopyLen);
	if (m_bshow)
	{
		Shell_NotifyIcon(NIM_MODIFY);
	}
}
void VirtualWifiNotifyIconBase::Clear_Ballon()
{
	memset(m_nd.szInfoTitle,0,sizeof(m_nd.szInfoTitle));
	memset(m_nd.szInfo,0,sizeof(m_nd.szInfo));
}

void VirtualWifiNotifyIconBase::CloseBallon()
{
	strcpy( m_nd.szInfo,EMPTYSTRING);//气泡内容 设置为空即可取消气泡提示  
	Shell_NotifyIcon(NIM_MODIFY);
}
bool VirtualWifiNotifyIconBase::Show()
{
	if (!m_bshow)
	{
		m_bshow=true;
		Shell_NotifyIcon(NIM_ADD);
	}
	return false;
}
void VirtualWifiNotifyIconBase::Shell_NotifyIcon(DWORD dwMessage)
{
	BOOL ISSUCCESS=::Shell_NotifyIcon(dwMessage,&m_nd);
	if (!ISSUCCESS)
	{
		v_log->write_log("Shell_NotifyIcon fail");
	}
}
void VirtualWifiNotifyIconBase::SetContent(const char* szTitle,const char* szContent)
{
	int szTitleLen=strlen(szTitle);
	int nCopyLen=sizeof(m_nd.szTip)<szTitleLen?sizeof(m_nd.szTip):szTitleLen;
	memcpy(m_nd.szInfoTitle,szTitle,nCopyLen);
	int szContentLen=strlen(szContent)*2;
	nCopyLen=sizeof(m_nd.szInfo)<szContentLen?sizeof(m_nd.szInfo):szContentLen;
	memcpy(m_nd.szInfo,szContent,nCopyLen);
}

bool VirtualWifiNotifyIconBase::ShowBalloonTip(int nTimeout)
{
	if (!m_bshow)
	{
		v_log->write_log("notify not show ");
		return false;
	}
	m_nd.uTimeout=nTimeout;
	Shell_NotifyIcon(NIM_MODIFY);
	return true;
}

void VirtualWifiNotifyIconBase::Hidden()
{
	Shell_NotifyIcon(NIM_DELETE);
	m_bshow=false;
}

bool VirtualWifiNotifyIconBase::Exit()
{
	if (m_bshow)
	{
		m_bshow=false;
		Shell_NotifyIcon(NIM_DELETE);
		return true;
	}
	return false;
}