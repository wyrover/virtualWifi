#include "stdafx.h"
#include "VirtualWifiPeer.h"
#include <iterator> 

VirtualWifiPeerList::VirtualWifiPeerList()
{
	InitializeCriticalSection(&m_lock);
}

void VirtualWifiPeerList::add_peer(DOT11_MAC_ADDRESS& dot11_mac_address,bool is_set_tim)
{
	VirtualWifiPeer* peer=new VirtualWifiPeer(dot11_mac_address);
	if (is_set_tim)
	{
		peer->set_time();
	}
	m_peer_lst.push_back(peer);
}
void VirtualWifiPeerList::add_peer(DOT11_MAC_ADDRESS& dot11_mac_address,VirtualWifiTime* time)
{
	VirtualWifiPeer* peer=new VirtualWifiPeer(dot11_mac_address);
	peer->set_time(time);
	m_peer_lst.push_back(peer);
}
void VirtualWifiPeerList::add_peer(VirtualWifiPeer& peer)
{
	m_peer_lst.push_back(new VirtualWifiPeer(peer));
}
void VirtualWifiPeerList::add_peer(VirtualWifiPeer* peer)
{
	m_peer_lst.push_back(peer);
}
void VirtualWifiPeerList::clear_all()
{
	list<VirtualWifiPeer*>::iterator it_peer_lst;
	for (it_peer_lst=m_peer_lst.begin();it_peer_lst!=m_peer_lst.end();++it_peer_lst)
	{
		delete *it_peer_lst;
	}
	m_peer_lst.clear();
}

VirtualWifiPeerList::VirtualWifiPeerList(WLAN_HOSTED_NETWORK_STATUS& network_status)
{
	add_peer_list(network_status);
}

void VirtualWifiPeerList::add_peer_list(WLAN_HOSTED_NETWORK_STATUS& network_status)
{
	if (network_status.dwNumberOfPeers<=0)
	{
		return;
	}
	int npeer_count=network_status.dwNumberOfPeers;
	for (int npeer_index=0;npeer_index<npeer_count;++npeer_index)
	{
		WLAN_HOSTED_NETWORK_PEER_STATE peer=network_status.PeerList[npeer_index];
		if (peer.PeerAuthState==wlan_hosted_network_peer_state_authenticated)
		{
			add_peer(peer.PeerMacAddress);
		}
	}
}

int VirtualWifiPeerList::get_size()
{
	return m_peer_lst.size();
}
VirtualWifiPeerList VirtualWifiPeerList::operator-(VirtualWifiPeerList& peerlist)
{
	VirtualWifiPeerList dpeerlist;
	return dpeerlist;
}
void VirtualWifiPeerList::remove(list<VirtualWifiPeer*>::iterator& it_peer_lst)
{
	VirtualWifiPeer* delete_peer=*it_peer_lst;
	m_peer_lst.erase(it_peer_lst);
	delete delete_peer;
}

void VirtualWifiPeerList::remove(list<VirtualWifiPeer*>& peer_lst)
{
	list<VirtualWifiPeer*>::iterator it_peer_lst;

	for (it_peer_lst=peer_lst.begin();it_peer_lst!=peer_lst.end();++it_peer_lst)
	{
		remove_if_exist(**it_peer_lst);
	}
}
void VirtualWifiPeerList::remove_if_exist(VirtualWifiPeer& peer)
{
	list<VirtualWifiPeer*>::iterator it_peer_lst;
	for (it_peer_lst=m_peer_lst.begin();it_peer_lst!=m_peer_lst.end();++it_peer_lst)
	{
		if (*peer.get_mac()==*((*it_peer_lst)->get_mac()))
		{
			it_peer_lst=m_peer_lst.erase(it_peer_lst);
			break;
		}
	}
}
bool VirtualWifiPeerList::is_exist(VirtualWifiPeer& peer)
{
	list<VirtualWifiPeer*>::iterator it_peer_lst;
	for (it_peer_lst=m_peer_lst.begin();it_peer_lst!=m_peer_lst.end();++it_peer_lst)
	{
		if (*peer.get_mac()==*((*it_peer_lst)->get_mac()))
		{
			return true;
		}
	}
	return false;
}
void VirtualWifiPeerList::remove(VirtualWifiPeerList& peer_list)
{
	list<VirtualWifiPeer*>::iterator it_peer_lst;
	list<VirtualWifiPeer*> temp_peer_list=peer_list.get_peer_list();

	for (it_peer_lst=temp_peer_list.begin();it_peer_lst!=temp_peer_list.end();++it_peer_lst)
	{
		if (is_exist(**it_peer_lst))
		{
			remove(it_peer_lst);
		}
	}
}
void VirtualWifiPeerList::add_peer_list(VirtualWifiPeerList& peer_list)
{
	list<VirtualWifiPeer*>::iterator it_peer_lst;
	list<VirtualWifiPeer*> temp_peer_list=peer_list.get_peer_list();

	for (it_peer_lst=temp_peer_list.begin();it_peer_lst!=temp_peer_list.end();++it_peer_lst)
	{
		add_peer(**it_peer_lst);
	}
}
list<VirtualWifiPeer*>&  VirtualWifiPeerList::get_peer_list()
{
	return m_peer_lst;
}
//返回是新增加的客户端.原PeerList中会减去参数中未存在的客户端
VirtualWifiPeerList VirtualWifiPeerList::operator -(WLAN_HOSTED_NETWORK_STATUS& network_status)
{
	//运行结束后,new_peer_list是新连接的客户端,peer_list是断开连接的客户端
	int npeer_count=network_status.dwNumberOfPeers;

	VirtualWifiPeerList new_peer_list;
	VirtualWifiTime time=VirtualWifiTime::get_now_time();
    list<VirtualWifiPeer*> peer_list;

	//peer_list.assign(m_peer_lst.begin(),m_peer_lst.end()); //将m_peer_list拷贝到peer_list
	std::copy(m_peer_lst.begin(), m_peer_lst.end(),std::back_inserter(peer_list)); 
	
	list<VirtualWifiPeer*>::iterator it_peer_lst;

	
	for (int npeer_index=0;npeer_index<npeer_count;++npeer_index)
	{
		WLAN_HOSTED_NETWORK_PEER_STATE peer=network_status.PeerList[npeer_index];
		if (peer.PeerAuthState==wlan_hosted_network_peer_state_authenticated)
		{
			bool is_find=false;
			for (it_peer_lst=peer_list.begin();it_peer_lst!=peer_list.end();++it_peer_lst)
			{
				VirtualWifiPeer* peer_client=*it_peer_lst;
               if (*peer_client==peer.PeerMacAddress)
               {
				    peer_list.erase(it_peer_lst++);
					is_find=true;
					break;
               }
			}
			if (!is_find)
			{
				new_peer_list.add_peer(peer.PeerMacAddress,&time);
			}
		}
	}
	
	if (peer_list.size()>0)   //删除不在线的客户端
	{
		remove(peer_list);
	}
	
	if (new_peer_list.get_peer_list().size()>0)    //添加新连接的客户端
	{
		add_peer_list(new_peer_list);
	}
	
	return new_peer_list;
}
VirtualWifiPeer* VirtualWifiPeerList::add_peer(CONST_STR sz_ip)
{
	EnterCriticalSection(&m_lock);
	VirtualWifiPeer* peer=new VirtualWifiPeer(sz_ip);
	m_peer_lst.push_back(peer);
	LeaveCriticalSection(&m_lock);
	return peer;
}

VirtualWifiPeer* VirtualWifiPeerList::find_peer(CONST_STR sz_ip)
{
	list<VirtualWifiPeer*>::iterator it_peer_lst;
	for (it_peer_lst=m_peer_lst.begin();it_peer_lst!=m_peer_lst.end();++it_peer_lst)
	{
		VirtualWifiPeer* peer=*it_peer_lst;
		if (!strcmp(peer->get_ip()->get_ip(),sz_ip))
		{
			return peer;
		}
	}
	return NULL;
}
VirtualWifiPeer* VirtualWifiPeerList::find_peer(VirtualWifiIp* vip)
{
	EnterCriticalSection(&m_lock);
	list<VirtualWifiPeer*>::iterator it_peer_lst;
	for (it_peer_lst=m_peer_lst.begin();it_peer_lst!=m_peer_lst.end();++it_peer_lst)
	{
		VirtualWifiPeer* peer=*it_peer_lst;
		if (*(peer->get_ip())==*vip)
		{
			LeaveCriticalSection(&m_lock);
			return peer;
		}
	}
	LeaveCriticalSection(&m_lock);
	return NULL;
}
VirtualWifiPeer* VirtualWifiPeerList::find_peer(u_char umac[6])
{
	list<VirtualWifiPeer*>::iterator it_peer_lst;
	for (it_peer_lst=m_peer_lst.begin();it_peer_lst!=m_peer_lst.end();++it_peer_lst)
	{
		VirtualWifiPeer* peer=*it_peer_lst;
		if (*peer==umac)
		{
			return peer;
		}
	}
	return NULL;
}
VirtualWifiPeerList::~VirtualWifiPeerList()
{

}