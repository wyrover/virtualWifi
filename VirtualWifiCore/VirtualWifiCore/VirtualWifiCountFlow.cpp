#include "stdafx.h"


VirtualWifiCountFlow::VirtualWifiCountFlow():m_usize(0)
{
	m_dip=new VirtualWifiIp();
	m_sip=new VirtualWifiIp();
}

void VirtualWifiCountFlow::set_ip(ip_header* ih)
{
	m_sip->set_ip(ih->saddr);
	m_dip->set_ip(ih->daddr);
}

link_type VirtualWifiCountFlow::judage_link_type()
{
	IP_TYPE stype=m_sip->reset_ip_type();
	IP_TYPE dtype=m_dip->reset_ip_type();

	if (stype==IP_TYPE_EXTERNAL_NETWORK&&dtype==IP_TYPE_LOCAL_NETWORK)
	{
		m_sdip=m_sip;
		return down_link_type;
	}
	if (stype==IP_TYPE_LOCAL_NETWORK&&dtype==IP_TYPE_EXTERNAL_NETWORK)
	{
		m_sdip=m_dip;
		return up_link_type;
	}
	return unkown_link_type;
}

/************************************************************************/
/*判断叠加的流量是否超时设定值，设定值不能大于1（不包括1）
/************************************************************************/
bool VirtualWifiCountFlow::is_timeout(timeval& t)
{
	int dsec=t.tv_sec-m_oldtime.tv_sec;
	if (dsec==0)
	{
		m_dtime=t.tv_usec-m_oldtime.tv_usec;
		if (m_dtime<m_timeout)
		{
			return false;
		}
		m_oldtime=t;
		return true;
	}
	if (dsec==1)
	{
		m_dtime=MICROSECONDS-m_oldtime.tv_usec+t.tv_usec;
		if (m_dtime<m_timeout)
		{
			return false;
		}
		m_oldtime=t;
		return true;
	}
	if (dsec==2)
	{
		m_dtime=MICROSECONDS-m_oldtime.tv_usec+t.tv_usec+MICROSECONDS;
		m_oldtime=t;
		return true;
	}
	m_oldtime=t;
    return false;
}
void VirtualWifiCountFlow::handle_data(struct pcap_pkthdr *header,const u_char *pkt_data)
{
	mac_header* mh=(mac_header*)pkt_data;
	char sz_mac[24];
	sprintf(sz_mac,"%02X%02X%02X%02X%02X%02X",mh->sadd[0],mh->sadd[1],mh->sadd[2],mh->sadd[3],mh->sadd[4],mh->sadd[5]);
	ip_header* ih=(ip_header*)(pkt_data+14);
	set_ip(ih);

}


void VirtualWifiCountFlow::handle_data_timeout(struct pcap_pkthdr *header)
{

}