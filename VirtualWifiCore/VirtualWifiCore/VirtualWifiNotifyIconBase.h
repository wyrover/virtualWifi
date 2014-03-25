#include "stdafx.h"
#include <ShellAPI.h>

#define  WM_NOTIFYMES WM_USER+256
class VirtualWifiNotifyIconBase
{
protected:
	HWND m_hwnd;
	NOTIFYICONDATA m_nd;
private:
	DWORD m_uid;
	bool m_bshow;
public:
	void SetInfoIcon(HICON icon);
	virtual void InitIcon(HWND hwnd);
	virtual void SetContent(const char* szTitle,const char* szContent);
	virtual bool ShowBalloonTip(int nTimeout);
	virtual void SetTip(const char* szTip);
	virtual void SetIcon(HICON hicon);
	VirtualWifiNotifyIconBase();
	void Shell_NotifyIcon(DWORD dwMessage);
	virtual void CloseBallon();
	virtual bool Show();
	void Clear_Ballon();
	void Hidden();
	bool Exit();
};

