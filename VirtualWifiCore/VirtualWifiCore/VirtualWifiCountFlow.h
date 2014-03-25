#include "stdafx.h"



class VirtualWifiCountFlow:public VirtualWifiCountFlowBase
{
protected:
	u_int m_usize;
	mac_header* m_macheadr;
	u_int m_dtime;
	timeval m_oldtime;
protected:
	virtual void handle_data(struct pcap_pkthdr *header,const u_char *pkt_data);
	virtual void handle_data_timeout(struct pcap_pkthdr *header);

    VirtualWifiIp* m_sdip;/*操作IP*/
	VirtualWifiIp* m_sip;/*源IP*/
	VirtualWifiIp* m_dip;/*目地IP*/
	bool is_timeout(timeval& t);
protected:
	void set_ip(ip_header* ih);
	link_type judage_link_type();
public:
	VirtualWifiCountFlow();
};