#include "stdafx.h"
#include "VirtualWifiParse.h"
#include <vector>
using namespace std;
#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

VirtualWifiParse::VirtualWifiParse(void)
{
}

NetInfo VirtualWifiParse::ParseNetInfo(CONST_STR sz_c)  //利用boost的split函数分隔字符串,有时间重写
{
	NetInfo netinfo;
	netinfo.V_ERROR=V_WRONG;
	vector<string> netinfo_lst;
	split(netinfo_lst,sz_c,is_any_of(SEPARATOR));
	if (netinfo_lst.size()==3)
	{
		memcpy(netinfo.szSsid,netinfo_lst[0].c_str(),NETINFOLEN);
		memcpy(netinfo.szKey,netinfo_lst[1].c_str(),NETINFOLEN);
		memcpy(netinfo.szAdapter,netinfo_lst[2].c_str(),NETINFOLEN);
		netinfo.V_ERROR=V_OK;
	}
	return netinfo;
}

VirtualWifiParse::~VirtualWifiParse(void)
{
}
