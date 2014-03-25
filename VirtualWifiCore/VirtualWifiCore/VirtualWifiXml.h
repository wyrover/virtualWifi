#include "stdafx.h"

class VirtualWifiConfig
{
protected:
	ConfigInfo* m_configinfo;
public:
	VirtualWifiConfig();
	void modify_config();
};

class VirtualWifiSoft
{
private:
	char* m_version_mainui_title;     //带有版本信息的
	char* m_version_title;
	void parse_title();
	void parse_mainui_title();
protected:
	SoftInfo* m_softinfo;
	CONST_STR m_warninginfo; //附带运行时的警告信息
	void check_flowmonitor_pos(); /*流量监控悬浮框检测X,Y坐标*/
public:
	void get_title(char* sz_title,int& n_title_buffer_len);
	char* get_title() const;
	char* get_mainui_title() const;
	void modify_soft();
	VirtualWifiSoft();
	~VirtualWifiSoft();
};


class VirtualWifiNetInfo
{
protected:
	NetInfo* m_netinfoex;
public:
	void modify_netinfo();
	NetInfo* parse_netinfoex(CONST_STR sz_parse_c); //解析字符串返回NetInfo
	VirtualWifiNetInfo();
};
class VirtualPeerHis
{
protected:
	PeersInfo* m_peerHis;
public:
	VirtualPeerHis();
};
class VirtualWifiNotifyIconInfo
{
protected:
	NotifyIconInfo* m_notifyiconinfo;
public:
	
    VirtualWifiNotifyIconInfo();
};