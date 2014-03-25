#include "stdafx.h"
#include "VirtualWifiReg.h"
#include "VirtualWifiApp.h"

class VirtualWifiAchieve:public VirtualWifiAchieveBase
	,virtual public VirtualWifiNetInfo
	,virtual public VirtualWifiApp
	,virtual public VirtualWifiReg
{
protected:
	VirtualWifiManageAdapterEx* m_vmae;
protected:
//	virtual void deal_start_wifi_exception()=0;
	bool reset_start_wifi();
    virtual bool start_wifi(NetInfo& netinfo);
	bool stop_wifi();
	bool check_bind_adapter(ADAPTERRET& adapter_ret);
	bool find_adapter();

	string intelligent_net_adapters();//智能选择适配器
	list<CONST_STR> get_connected_adapters();
	POINT parse_pos(CONST_STR sz_parse_c);/*解析发送来的坐标信息*/
public:
	VirtualWifiAchieve();
};