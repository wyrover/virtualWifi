#include "stdafx.h"
#include <process.h>

char* VirtualWifiNotifyIcon::SZ_CLASSNAME="VirtualWifi";
char* VirtualWifiNotifyIcon::SZ_WINDOWSNAME="VirtualWifi";
int VirtualWifiNotifyIcon::INT_BALLON_TIMEOUT=5650;
int VirtualWifiNotifyIcon::INT_DYNAMIC_SHOW_TIME=250;
CONST_STR VirtualWifiNotifyIcon::SZ_STATUS="◊¥Ã¨:";

CONST_STR VirtualWifiNotifyIcon::SZ_STATUS_STARTED="%s\r\nSSID:%s\r\nKey:%s\r\n◊¥Ã¨:“—∆Ù∂Ø";
CONST_STR VirtualWifiNotifyIcon::SZ_STATUS_NOSTART="%s\r\n◊¥Ã¨:Œ¥∆Ù∂Ø";

VirtualWifiNotifyIcon::VirtualWifiNotifyIcon()
{
	notify_show();
	m_isshow=false;
}
bool VirtualWifiNotifyIcon::ShowBalloonTip(int nTimeout)
{
	if (!VirtualWifiNotifyIconBase::ShowBalloonTip(nTimeout))
	{
		return false;
	}
	m_isshow=true;
	//SetInfoIcon(LoadIcon(m_notifyiconinfo->StartPath));
	SetTimer(m_hwnd,1,nTimeout,NULL);
	return false;
}
void VirtualWifiNotifyIcon::set_notify_tip(NOTIFYSTATUS notify_status/* =NOSTART */,CONST_STR sz_ssid/* =EMPTYSTRING */,CONST_STR sz_key/* =EMPTYSTRING */)
{
	char sz_tip[1024]={0};
	switch(notify_status)
	{
	case NOSTART:
		{
			sprintf(sz_tip,SZ_STATUS_NOSTART,get_title());
			SetIcon(LoadIcon(m_notifyiconinfo->NoStartPath));
			break;
		}
	case STARTED:
		{
			start_dynamic_show();
			if (sz_ssid!=EMPTYSTRING&&sz_key!=EMPTYSTRING)
			{
				sprintf(sz_tip,SZ_STATUS_STARTED,get_title(),sz_ssid,sz_key);
			}
			SetIcon(LoadIcon(m_notifyiconinfo->StartPath));
			break;
		}
	}
	SetTip(sz_tip);
}
void VirtualWifiNotifyIcon::dynamic_show_icon_thread(LPVOID param)
{
	VirtualWifiNotifyIcon* VWN=(VirtualWifiNotifyIcon*)param;
	VWN->dynamic_show_icon();
}
void VirtualWifiNotifyIcon::start_dynamic_show()
{
	m_isdynamic_show=true;
	_beginthread(dynamic_show_icon_thread,0,this);
}
void VirtualWifiNotifyIcon::stop_dynamic_show()
{
	m_isdynamic_show=false;
}

//∂ØÃ¨œ‘ æÕº±Í
void VirtualWifiNotifyIcon::dynamic_show_icon()
{
	HICON* iconarray=new HICON[m_notifyiconinfo->DynamicNums];

	for (int i=0;i<m_notifyiconinfo->DynamicNums;++i)
	{
		iconarray[i]=LoadIcon(m_notifyiconinfo->DynamicShow[i]);
	}

	//CloseBallon();
	for (;;)   //À¿—≠ª∑
	{
		for (int i=0;i<m_notifyiconinfo->DynamicNums;)
		{
			PAUSE(INT_DYNAMIC_SHOW_TIME);
			if (!m_isdynamic_show)
			{
	            goto end;
			}
			if (!m_isshow)
			{
				SetIcon(iconarray[i]);
				++i;
			}	
		}
	}
	end:
	delete[] iconarray;
	SetIcon(LoadIcon(m_notifyiconinfo->NoStartPath));
}
void VirtualWifiNotifyIcon::show_balloon(CONST_STR sz_tip_title,CONST_STR sz_tip_content)
{
	v_log->write_log_come_to(":show_balloon(CONST_STR sz_tip_title,CONST_STR sz_tip_content)");
	this->SetContent(sz_tip_title,sz_tip_content); 
	this->ShowBalloonTip(INT_BALLON_TIMEOUT);
}
bool VirtualWifiNotifyIcon::Show()
{
	v_log->write_log_come_to("VirtualWifiNotifyIcon::Show()");
    InitIcon(m_hwnd);
	set_notify_tip();
	return VirtualWifiNotifyIconBase::Show();
}
HICON VirtualWifiNotifyIcon::LoadIcon(char* szpath)
{
	return (HICON)LoadImage(NULL,szpath,IMAGE_ICON,0,0,LR_LOADFROMFILE);
}

void VirtualWifiNotifyIcon::notify_show()
{
	v_log->write_log_come_to("notify_show");
	_beginthread(create_window,0,this);
}
void VirtualWifiNotifyIcon::on_lbutton_dowm_notify(POINT& cursorpos)
{
}
void VirtualWifiNotifyIcon::notify_hidden()
{
	Hidden();
}
void VirtualWifiNotifyIcon::set_hwnd(HWND hwnd)
{
	this->m_hwnd=hwnd;
}
void VirtualWifiNotifyIcon::create_window(LPVOID param)
{
	v_log->write_log_come_to(" create_window thread");
	VirtualWifiNotifyIcon* VWN=(VirtualWifiNotifyIcon*)param;

	HINSTANCE hinstance=GetModuleHandle(NULL);

	WNDCLASS wndcls;
	wndcls.style = CS_HREDRAW ; 
	wndcls.lpfnWndProc = WndProc;           
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hInstance = hinstance;
	wndcls.hIcon = ::LoadIcon(NULL,NULL);                  
	wndcls.hCursor = LoadCursor(NULL,IDC_ARROW);                  
	wndcls.hbrBackground = NULL;     
	wndcls.lpszMenuName = NULL;           
	wndcls.lpszClassName = SZ_CLASSNAME;

	RegisterClass(&wndcls);          

	v_log->write_log_run_to("create_window");
	HWND hwnd=CreateWindow(SZ_CLASSNAME,SZ_WINDOWSNAME,SW_SHOW,
		CW_USEDEFAULT,CW_USEDEFAULT,0,0, NULL, NULL,hinstance, NULL);

	if (hwnd==NULL)
	{
		return;
	}

	VWN->set_hwnd(hwnd);
	v_log->write_log_run_to("VWN->set_hwnd(hwnd)");

	SetWindowLong(hwnd,GWL_USERDATA,(LONG)VWN);

	VWN->Show();

	MSG msg;
	while (GetMessage(&msg,NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
void VirtualWifiNotifyIcon::show_balloon(bool is_success)
{
	
}
void VirtualWifiNotifyIcon::set_notify_title(CONST_STR sz_t)
{

}
void VirtualWifiNotifyIcon::on_mouse_move()
{
	CloseBallon();
}
void VirtualWifiNotifyIcon::CloseBallon()
{
	VirtualWifiNotifyIconBase::CloseBallon();
	m_isshow=false;
}
LRESULT CALLBACK VirtualWifiNotifyIcon::WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	VirtualWifiNotifyIcon* VWN=(VirtualWifiNotifyIcon*)GetWindowLong(hwnd,GWL_USERDATA);

	switch(uMsg)
	{
	case WM_CREATE:
		{
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	case WM_TIMER:
		{
			 VWN->CloseBallon();
             break;
		}
	case WM_NOTIFYMES:
		{
           switch(lParam)
		   {
		   case WM_LBUTTONDOWN:
			   {
				   POINT cursorpos;
				   GetCursorPos(&cursorpos);
				   v_log->write_log_come_to("ico click");
                   VWN->on_lbutton_dowm_notify(cursorpos);
				   break;
			   }
		   case WM_MOUSEMOVE:
			   {
				   VWN->on_mouse_move();
				   break;
			   }
		   }
			break;
		}
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);   
	}
	return 0;
}