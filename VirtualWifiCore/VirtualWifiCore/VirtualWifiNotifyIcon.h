#include "stdafx.h"


//托盘状态
enum NOTIFYSTATUS
{
	NOSTART,
	STARTED,
};

class VirtualWifiNotifyIcon:public VirtualWifiNotifyIconBase
	,public VirtualWifiNotifyIconInfo
	,virtual public VirtualWifiSoft
{
private:
    static CONST_STR SZ_STATUS;
	static CONST_STR SZ_STATUS_STARTED;
	static CONST_STR SZ_STATUS_NOSTART;
	static int INT_BALLON_TIMEOUT;
	static int INT_DYNAMIC_SHOW_TIME;
private:
	static  char* SZ_WINDOWSNAME;
	static  char* SZ_CLASSNAME;
	static  LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	static  void create_window(LPVOID param);  //线程函数
	static  void dynamic_show_icon_thread(LPVOID param);
private:
	HWND m_hwnd;
	CONST_STR m_sztitle;
	bool m_isdynamic_show;
	bool m_isshow;
protected:
	HICON LoadIcon(char* szpath);
	void  set_notify_tip(NOTIFYSTATUS notify_status=NOSTART,CONST_STR sz_ssid=EMPTYSTRING,CONST_STR sz_key=EMPTYSTRING);
public:
	void CloseBallon();
	void show_balloon(bool is_success);
	void show_balloon(CONST_STR sz_tip_title,CONST_STR sz_tip_content);
	void set_notify_title(CONST_STR sz_t);
	virtual bool Show();
	void notify_hidden();
	virtual void on_lbutton_dowm_notify(POINT& cursorpos);//鼠标右键按下消息,参数为,鼠标当前位置
	virtual void on_mouse_move();
	VirtualWifiNotifyIcon();
	void notify_show();
	void set_hwnd(HWND hwnd);
	bool ShowBalloonTip(int nTimeout);
	virtual void dynamic_show_icon();
	void start_dynamic_show();
	void stop_dynamic_show();
};