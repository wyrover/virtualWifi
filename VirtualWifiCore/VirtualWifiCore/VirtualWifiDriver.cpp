#include "StdAfx.h"
#include "VirtualWifiDriver.h"

CONST_STR VirtualWifiDriver::SZ_SUPPORT_WIFI="支持的承载网络";

CONST_STR VirtualWifiDriver::SZ_SHOW_DRIVER="netsh wlan show driver";

VirtualWifiDriver::VirtualWifiDriver(void)
{
    m_is_support_wifi=false;
   if(Execute((char*)SZ_SHOW_DRIVER))
   {
	   string str_reslut(GetReslut());
	   size_t ret=str_reslut.find(SZ_SUPPORT_WIFI);
	   if (ret!=string::npos)
	   {
		   ret=str_reslut.find("是",ret);
		   if (ret!=string::npos)
		   {
			   m_is_support_wifi=true;
		   }
	   }
           
   }
}
bool VirtualWifiDriver::get_is_support_wifi()
{
	return m_is_support_wifi;
}

VirtualWifiDriver::~VirtualWifiDriver(void)
{
}
