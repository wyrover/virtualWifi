#include "stdafx.h"



char* VirtualWifi::SZ_CLASSNAME="VirtualWifi";
char* VirtualWifi::SZ_WINDOWSNAME="VirtualWifi";


LRESULT CALLBACK VirtualWifi::WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	VirtualWifi* vww=(VirtualWifi*)GetWindowLong(hwnd,GWL_USERDATA);
     
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
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);   
	}
	return 0;
}