#include "StdAfx.h"
#include "VirtualWifiInit.h"
#include "VirtualWifiDriver.h"

CONST_STR VirtualWifiInit::SZ_WRITE_PATH="Software";
CONST_STR VirtualWifiInit::SZ_VIRTUALWIFIADAPTERGUID="VirtualWifiAdapterGuid";

VirtualWifiInit::VirtualWifiInit()
{
	if(!m_reg.open_key(HKEY_CURRENT_USER,SZ_WRITE_PATH))
	{
		throw_self();
	}
}

bool VirtualWifiInit::get_reg_info()
{
	CONST_STR sz_guid=m_reg.get_value(SZ_VIRTUALWIFIADAPTERGUID);
	m_virtualwifiadapter_guid=new char[strlen(sz_guid)+1];
	strcpy(m_virtualwifiadapter_guid,sz_guid);
	v_log->write_log("get guid is ",m_virtualwifiadapter_guid);
	return true;
}
bool VirtualWifiInit::init_check()
{
	HKEY hnewkey;
	DWORD ret=m_reg.create_key(get_title(),hnewkey);
	m_reg.set_key(hnewkey);
	if (ret==REG_OPENED_EXISTING_KEY)
	{
		return get_reg_info();
	}
	if (ret==REG_CREATED_NEW_KEY)
	{
		return create_new_reg();
	}
	return false;
}

//假如不存在,则判定是否支持承载网络
bool VirtualWifiInit::create_new_reg()
{
	VirtualWifiDriver  driver;
	if(!driver.get_is_support_wifi())
	{
		//MessageBox(NULL,IS_NOT_SUPPORT_WIFI,get_title(),MB_OK);
		//return false;
	}
	TRYEXCEPTION_BEGIN
		if(allow_wifi_cmd())
		{
			Sleep(1200);

			start_wifi_cmd();
			
			string str_guid=GetVirtualAdapterGuid();
			CONST_STR sz_guid=str_guid.c_str();
			m_virtualwifiadapter_guid=new char[strlen(sz_guid)+1];
			strcpy(m_virtualwifiadapter_guid,sz_guid);
			if(!m_reg.set_value(SZ_VIRTUALWIFIADAPTERGUID,sz_guid))
			{
				throw_self();
			}
			stop_wifi_cmd();
		}
	TRYEXCEPTION_END
		CATCH(VirtualWifiException& e)
		DEAL_BEGIN
	    MessageBox(NULL,e.get_error_message(),get_title(),NULL);
	DEAL_END

	return true;
}
VirtualWifiInit::~VirtualWifiInit(void)
{
	delete[] m_virtualwifiadapter_guid;
}
