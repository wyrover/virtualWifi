#include "stdafx.h"
#include <vector>
using namespace std;
#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

VirtualWifiNetInfo::VirtualWifiNetInfo()
{
	m_netinfoex=ParseNetInfo();
}
NetInfo* VirtualWifiNetInfo::parse_netinfoex(CONST_STR sz_parse_c)
{
	v_log->write_log_come_to("VirtualWifiNetInfo::parse_netinfoex(CONST_STR sz_parse_c)");
	NetInfo& netinfo=*m_netinfoex;
	netinfo.V_ERROR=V_WRONG;
	vector<string> netinfo_lst;
	split(netinfo_lst,sz_parse_c,is_any_of(SEPARATOR));
	if (netinfo_lst.size()==3)
	{
		memcpy(netinfo.szSsid,netinfo_lst[0].c_str(),NETINFOLEN);
		memcpy(netinfo.szKey,netinfo_lst[1].c_str(),NETINFOLEN);
		memcpy(netinfo.szAdapter,netinfo_lst[2].c_str(),NETINFOLEN);

		v_log->write_log_success("copy netinfo");
		v_log->write_log("the adapter name is ",netinfo.szAdapter);
		netinfo.V_ERROR=V_OK;
	}
	return &netinfo;
}
void VirtualWifiNetInfo::modify_netinfo()
{
	ModifyNetInfo(*m_netinfoex);
}