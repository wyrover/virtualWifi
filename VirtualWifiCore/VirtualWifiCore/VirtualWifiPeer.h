#pragma once
#include "stdafx.h"

#define PEERSTRLEN 1024
//记录客户端信息的类
class VirtualWifiPeer
{
private:
	static CONST_STR  PERRSTR;
private:
	VirtualWifiMac* m_mac_addr;
	VirtualWifiTime* m_time;
	VirtualWifiIp* m_ip;
	VirtualWifiFlow* m_flow;
private:
	void free_time();
public:
	VirtualWifiMac* get_mac();
	VirtualWifiPeer(DOT11_MAC_ADDRESS& dot11_mac_address);
	VirtualWifiPeer(CONST_STR sz_ip);
	void set_time(VirtualWifiTime* time=NULL);
	void set_ip(CONST_STR sz_ip);

	string to_string();//转化成主界面可识别的字符串
	bool operator==(u_char umac[6]);
	VirtualWifiIp* get_ip();
	VirtualWifiFlow* get_flow();
	~VirtualWifiPeer(void);
};


class VirtualWifiPeerList
{
private:
	CRITICAL_SECTION m_lock;
private:
	list<VirtualWifiPeer*> m_peer_lst;
public:
	list<VirtualWifiPeer*>& get_peer_list();
	int get_size();
	VirtualWifiPeerList operator-(VirtualWifiPeerList& peerlist);
	VirtualWifiPeerList operator-(WLAN_HOSTED_NETWORK_STATUS& network_status);
	void clear_all();  //记得调用 释放内存

	VirtualWifiPeerList();
	VirtualWifiPeerList(WLAN_HOSTED_NETWORK_STATUS& network_status);
	~VirtualWifiPeerList();

	bool is_exist(VirtualWifiPeer& peer);
	void remove(list<VirtualWifiPeer*>::iterator& it_peer_lst);
	void remove(VirtualWifiPeerList& peer_list);
	void remove(list<VirtualWifiPeer*>& peer_lst);
	void remove_if_exist(VirtualWifiPeer& peer);  //如果存在就删除

	void add_peer(VirtualWifiPeer& peer);
	void add_peer(VirtualWifiPeer* peer);
	VirtualWifiPeer* add_peer(CONST_STR sz_ip);
	void add_peer(DOT11_MAC_ADDRESS& dot11_mac_address,bool is_set_time=true);
	void add_peer(DOT11_MAC_ADDRESS& dot11_mac_address,VirtualWifiTime* time);
	void add_peer_list(WLAN_HOSTED_NETWORK_STATUS& network_status);
	void add_peer_list(VirtualWifiPeerList& peer_list);
public:
	VirtualWifiPeer* find_peer(VirtualWifiIp* vip);
	VirtualWifiPeer* find_peer(CONST_STR sz_ip);
	VirtualWifiPeer* find_peer(u_char umac[6]);
};
