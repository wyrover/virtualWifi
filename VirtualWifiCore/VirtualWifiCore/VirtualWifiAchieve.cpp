#include "stdafx.h"
#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

VirtualWifiAchieve::VirtualWifiAchieve()
{
	m_vmae=new VirtualWifiManageAdapterEx();
}
bool VirtualWifiAchieve::find_adapter()
{
	if (!strcmp(m_netinfoex->szAdapter,EMPTYSTRING))
	{
		string str_adpater=intelligent_net_adapters();
		strcpy(m_netinfoex->szAdapter,str_adpater.c_str());
		return true;
	}
	return false;
}
bool VirtualWifiAchieve::reset_start_wifi()
{
	stop_wifi();

	PAUSE(100);
	allow_wifi_cmd();
	
	ADAPTERRET adapter_ret=SetSharingAdapter(m_netinfoex->szAdapter);

	start_wifi_cmd();

	return check_bind_adapter(adapter_ret);
}

bool VirtualWifiAchieve::start_wifi(NetInfo& netinfoex)
{
	v_log->write_log_come_to("VirtualWifiAchieve::start_wifi(NetInfoEx& netinfoex)");

	refresh_wifi();
	//ÉèÖÃÕÊºÅ
	if (!SetSsidAndKey(netinfoex.szSsid,netinfoex.szKey))
	{
		//ÉèÖÃÕÊºÅÊ§°Ü
		set_message(m_sz_fail_resason);
		throw_self();
	}


	v_log->write_log_come_to("set_adapter_info");


	Sleep(500);

	ADAPTERRET adapter_ret=SetSharingAdapter(netinfoex.szAdapter);  //°ó¶¨ÍøÂç¹²Ïí

	v_log->write_log("start wifi fun");
	if (!StartWifi())
	{
		//set_message(ERROR_MES_START_WIFI_FAIL);
		set_message(EMPTYSTRING);
		throw_self();
	}
	return check_bind_adapter(adapter_ret);
}

bool VirtualWifiAchieve::stop_wifi()
{
	UnSharingAdapter(m_netinfoex->szAdapter);
	return StopWifi();
}
list<CONST_STR> VirtualWifiAchieve::get_connected_adapters()
{
	m_vmae->reset_integrate_adapter();
	VirtualWifiAdapter* va=m_vmae->get_adapters();
	int ntotal=m_vmae->get_adapter_total();
	list<CONST_STR> adapterslist;
	for (int i=0;i<ntotal;++i)
	{
		adapterslist.push_back(va[i].get_name());
	}
	return adapterslist;
}
string VirtualWifiAchieve::intelligent_net_adapters()
{

	VirtualWifiAdapter* va=m_vmae->get_external_ip_adapters();
	if (va!=NULL)
	{
		return string(va->get_name());
	}
	va=m_vmae->get_connected_ppp_adapters();
	if (va!=NULL)
	{
		return string(va->get_name());
	}
	va=m_vmae->get_local_ip_adapters();
	if (va!=NULL)
	{
		return string(va->get_name());
	}
	if (va==NULL)
	{
		set_message(NOT_FIND_NET_ADAPTER);
		throw_self();
	}
}
POINT VirtualWifiAchieve::parse_pos(CONST_STR sz_parse_c)
{
	POINT pos;
	vector<string> netinfo_lst;
	split(netinfo_lst,sz_parse_c,is_any_of(SEPARATOR));
	if (netinfo_lst.size()==2)
	{
	   pos.x=atoi(netinfo_lst[0].c_str());
	   pos.y=atoi(netinfo_lst[1].c_str());
	}
	return pos;
}
bool VirtualWifiAchieve::check_bind_adapter(ADAPTERRET& adapter_ret)
{
	switch (adapter_ret)
	{
	case SUCCESS:
		{
			return true;
		}
	case NOTFINDNET:
		{
			set_message(NOT_FIND_NET);
			throw_self();
			break;
		}
	case NOTFINVIRTUAL:
		{
			set_message(NOT_FIND_VIRTUALADAPTER);
			throw_self();
		}
	default:
		{
			set_message(SET_SHARE_ADAPTER_ERROR);
			throw_self();
		}
	}
	return false;
}