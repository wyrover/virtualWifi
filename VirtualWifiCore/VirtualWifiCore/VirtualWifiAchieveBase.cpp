#include "StdAfx.h"
#include "VirtualWifiReg.h"

const DWORD VirtualWifiAchieveBase::CLIENTVERSION_WIN7=2;
char* VirtualWifiAchieveBase::SZ_SET_SSID_KEY_CMD="netsh wlan set hostednetwork ssid=%s key=%s mode=allow";
CONST_STR VirtualWifiAchieveBase::SZ_START_WIFI="netsh wlan start hostednetwork";
CONST_STR VirtualWifiAchieveBase::SZ_STOP_WIFI="netsh wlan stop hostednetwork";
CONST_STR VirtualWifiAchieveBase::SZ_DISALLOW_WIFI="netsh wlan set hostednetwork mode=disallow";
CONST_STR VirtualWifiAchieveBase::SZ_ALLOW_WIFI="netsh wlan set hostednetwork mode=allow";
CONST_STR VirtualWifiAchieveBase::SET_SUCCESS="承载网络模式已设置为允许";
CONST_STR VirtualWifiAchieveBase::SET_SUCCESS_I="已成功更改承载网络的 SSID";
CONST_STR VirtualWifiAchieveBase::START_SUCCESS="已启动承载网络";
CONST_STR VirtualWifiAchieveBase::STOP_SUCCESS="已停止承载网络";
CONST_STR VirtualWifiAchieveBase::DISALLOW_SUCCESS="承载网络模式已设置为禁止";

VirtualWifiAchieveBase::VirtualWifiAchieveBase()
{
	m_binit=false;
	m_bstart=false;
}
bool VirtualWifiAchieveBase::start_wifi_cmd()
{
	VirtualWifiExecuteCmd vwc;
	vwc.Execute((char*)SZ_START_WIFI);
	CONST_STR sz_reslut=vwc.GetReslut();
    string str_reslut(sz_reslut);
	if (str_reslut.find(START_SUCCESS)!=string::npos)
	{
		return true;
	}
	v_log->write_log(sz_reslut);
	set_message("启动网络失败!");	
	throw_self();
	return false;
}

bool VirtualWifiAchieveBase::StartWifi()
{
		DWORD ret =WlanHostedNetworkStartUsing(m_clienthandle,&m_failreason,NULL); 
		if (ret!=ERROR_SUCCESS)
		{
			analysis_fail_reason();
			char c[10];
			sprintf(c,"%d",ret);
			v_log->write_log("the error code is ",c);
			return false;
		}
		else 
		{
			return m_bstart=ret==ERROR_SUCCESS?true:false;
		}
    return false;
}
void VirtualWifiAchieveBase::analysis_fail_reason()
{
	switch (m_failreason)
	{
	case wlan_hosted_network_reason_unspecified:

		break;
	}
}
bool VirtualWifiAchieveBase::stop_wifi_cmd()
{
	VirtualWifiExecuteCmd vwc;
	vwc.Execute((char*)SZ_STOP_WIFI);
	CONST_STR sz_reslut=vwc.GetReslut();
	string str_reslut(sz_reslut);
	disallow_wifi_cmd();
	if (str_reslut.find(STOP_SUCCESS)!=string::npos)
	{
		return true;
	}
	return false;
}
bool VirtualWifiAchieveBase::StopWifi()
{
	DWORD ret=WlanHostedNetworkStopUsing (m_clienthandle,&m_failreason,NULL);
	set_mode(false);
	return m_bstart=ret==ERROR_SUCCESS?false:true;
}

#pragma warning(disable:4996)

bool VirtualWifiAchieveBase::SetSsidAndKey(char* szSsid,char* szKey)
{
	int nsz_ssid_key_cmd_len=strlen(SZ_SET_SSID_KEY_CMD);
	int nsz_ssid_len=strlen(szSsid);
	int nsz_key_len=strlen(szKey);
	char* sz_buffer=new char[nsz_ssid_key_cmd_len+nsz_key_len+nsz_ssid_len];
	sprintf(sz_buffer,SZ_SET_SSID_KEY_CMD,szSsid,szKey);
	

	//执行cmd,并检查结果
	VirtualWifiExecuteCmd vwc;
	vwc.Execute(sz_buffer);
	delete[] sz_buffer;
	CONST_STR sz_reslut=vwc.GetReslut();
	string str_reslut(sz_reslut);
    if (str_reslut.find(SET_SUCCESS)!=string::npos&&str_reslut.find(SET_SUCCESS_I)!=string::npos)
    {
		return true;
    }
	else
	{
		m_sz_fail_resason=ERROR_MES_STOP_WIFI_FAIL;
		set_message(m_sz_fail_resason);
		throw_self();
	}
	return false;
}
bool VirtualWifiAchieveBase::allow_wifi_cmd()
{
	VirtualWifiExecuteCmd vwc;
	vwc.Execute((char*)SZ_ALLOW_WIFI);
	return true;
}
bool VirtualWifiAchieveBase::disallow_wifi_cmd()
{
	VirtualWifiExecuteCmd vwc;
	vwc.Execute((char*)SZ_DISALLOW_WIFI);
	CONST_STR sz_reslut=vwc.GetReslut();
	string str_reslut(sz_reslut);
	if (str_reslut.find(DISALLOW_SUCCESS)!=string::npos)
	{
		return true;
	}
	return false;
}
bool VirtualWifiAchieveBase::AutoRun(CONST_STR start_name)
{
	HKEY hKey; 
	LPCTSTR lpRun = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0, KEY_WRITE, &hKey);

	if(lRet == ERROR_SUCCESS) 
	{ 
		char pFileName[MAX_LEN] = {0}; 
		GetModuleFileName(NULL,pFileName,MAX_LEN);
		(_tcsrchr(pFileName, '\\'))[0] = 0;
		(_tcsrchr(pFileName, '\\'))[1] = 0;  //找到上级目录

	    strcat(pFileName,m_configinfo->StartPath);

		if (m_configinfo->AutoStartWifi)
		{
			strcat(pFileName,SPACE);
			strcat(pFileName,AUTO_START_WIFI_PARAMETERS);
		}

		DWORD dwRet = strlen(pFileName);

		lRet = RegSetValueEx(hKey,start_name, 0, REG_SZ, (BYTE *)pFileName, dwRet);

		RegCloseKey(hKey); 
		if(lRet != ERROR_SUCCESS) 
		{ 
			return false;
		} 
	}
	return true;
}
bool VirtualWifiAchieveBase::UnAutoRun(CONST_STR start_name)
{
	HKEY hKey; 
	LPCTSTR lpRun = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0,KEY_ALL_ACCESS, &hKey);

	if(lRet == ERROR_SUCCESS) 
	{ 
		
		lRet=RegDeleteValue(hKey,start_name);
		RegCloseKey(hKey); 
		if(lRet != ERROR_SUCCESS) 
		{ 
			return false;
		} 
	}
	return true;
}
VirtualWifiAchieveBase::~VirtualWifiAchieveBase()
{
	if (m_binit)
	{
		
	}
}

