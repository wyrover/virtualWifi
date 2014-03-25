#include "stdafx.h"


#include <pcap.h>
#pragma comment(lib,"VirtualWifiInfo.lib")
#define VIPLEN 16


/* 4字节IP地址 */
typedef struct ip_address{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

//Mac帧头 占14个字节
typedef struct tag_mac_header
{
	u_char dadd[6];//6个字节 目标地址
	u_char sadd[6];//6个字节 源地址
	u_short mac_type;//2个字节 类型
}mac_header;

typedef struct ip_header{
	u_char  ver_ihl;   	// 4 bit的版本信息 + 4 bits的头长
	u_char  tos;        	// 服务类型
	u_short tlen;        	// 总长度
	u_short identification; 	// 标识序列
	u_short flags_fo;      	// Flags (3 bits) + Fragment offset (13 bits)
	u_char  ttl;          	// 生存期
	u_char  proto;      	// 协议
	u_short crc;         	// 校验头
	ip_address  saddr; 	// 源地址
	ip_address  daddr;   	// 目标地址
	u_int   op_pad;     	// Option + Padding
}ip_header;

typedef unsigned int u_int32_t;
//定义TCP头
typedef struct tag_tcp_header
{
	u_short sport;//源端口地址  16位
	u_short dport;//目的端口地址 16位
	u_int32_t sn;//序列号 32位
	u_int32_t an;//确认号 32位
	u_int16_t other;//16位 其中 头长度4位＋保留6位＋UPG1+ACK1+PSH1+RST1+SYN1+FIN1 
	u_int16_t window_size;//窗口大小 16位
	u_int16_t check_sum;//校验和 16位
	u_int16_t urgent_pointer;//紧急指针 16位
	u_int32_t option;//选项0或32位
}tcp_header;

//定义UDP头
typedef struct tag_udp_header
{
	u_short sport;//源端口  16位
	u_short dport;//目的端口 16位
	u_short len;//数据报长度 16位
	u_short crc;//校验和 16位

}udp_header;


enum IP_TYPE
{
	IP_TYPE_LOCAL_NETWORK,   //内网
	IP_TYPE_EXTERNAL_NETWORK, //外网
	IP_TYPE_INVALID_NETWORK,  /* 无效IP*/
	IP_TYPE_MULTICAST_NETWORK,/*组播地址*/
	IP_TYPE_UNKOWN
};

/************************************************************************/
/*  内网IP
    10.x.x.x
　　172.16.x.x至172.31.x.x
    192.168.x.x   
/*  无效IP
    169.254.x.x
/*  组播地址 
    224.0.0.0到239.255.255.255
/************************************************************************/
class __declspec(dllexport) VirtualWifiIp
{
private:
	static DWORD NETWORK_192_168;
	static DWORD NETWORK_10;
	static DWORD NETWORK_172;
	static DWORD NETWORK_169_254;
	static DWORD NETWORK_224;
	static DWORD NETWORK_239;
private:
	char m_ip[IPLEN];
	IP_TYPE m_ip_type;
public:
	IP_TYPE reset_ip_type();/*判断IP地址的类型*/

	void set_ip(CONST_STR sz_ip);
	void set_ip(ip_address& ia);
	CONST_STR get_ip();
	IP_TYPE get_ip_type();
	bool operator==(VirtualWifiIp& ip);
	VirtualWifiIp(ip_address& ia);
	VirtualWifiIp(CONST_STR sz_ip="0.0.0.0");
	~VirtualWifiIp(void);
};



#define GUIDLEN 64
class __declspec(dllimport) VirtualWifiAdapter
{
protected:
	char* m_sz_name;
	char* m_des;
	VirtualWifiIp* m_ip;
	char m_guid[GUIDLEN];
	bool m_is_init;
	UINT m_type;
	NETCON_STATUS m_status;
	u_int m_netmask;
public:
	VirtualWifiIp* get_v_ip();
	UINT get_type();
	NETCON_STATUS get_status();
	u_int get_netmask();
	CONST_STR get_des();
	CONST_STR get_guid();
	CONST_STR get_name();

	void set_adapter_info(PIP_ADAPTER_INFO adapter_info);
	void set_adapter_info(pcap_if_t* pcapinfo);
	void set_adapter_info(NETCON_PROPERTIES* netconinfo);
	void set_adapter_info(VirtualWifiAdapter* adapters,VirtualWifiAdapter* netconinfo);
	void set_adapter_info_(VirtualWifiAdapter* adapters,VirtualWifiAdapter* pcapadapter);
	void set_adapter_info(CONST_STR sz_name);

	void release();
	VirtualWifiAdapter();
	VirtualWifiAdapter(PIP_ADAPTER_INFO adapter_info);
	VirtualWifiAdapter(pcap_if_t* pcapinfo);
	VirtualWifiAdapter(NETCON_PROPERTIES* netconinfo);

	~VirtualWifiAdapter(void);
};


/************************************************************************/
/* 通过IPHlpApi获取的与NetShare获取的组合：依靠适配器的GUID。                                                                     */
/************************************************************************/
class __declspec(dllimport) VirtualWifiManageAdapterEx
{
protected:
	VirtualWifiAdapter* m_adapters;
	int m_adapter_total;
private:
	void release();
public:
	VirtualWifiManageAdapterEx();
	void reset_integrate_adapter();/*根据2种方法获取的适配器信息，进行整合*/
	VirtualWifiAdapter* get_adapters() const;
	VirtualWifiAdapter* get_external_ip_adapters() const;
	VirtualWifiAdapter* get_connected_ppp_adapters() const;
	VirtualWifiAdapter* get_local_ip_adapters() const;

	void reset_integrate_pcap_adapter();/*整合pcap，iphlpApi方法获取信息的整合*/

	VirtualWifiAdapter* get_virtual_adapter() const;
	int get_adapter_total() const;
};

#define TIMELEN  48

class __declspec(dllimport) VirtualWifiTime
{
private:
	char m_sz_time[TIMELEN];
protected:
	byte m_hour;
	byte m_min;
	byte m_sec;
	struct tm m_fmt;
protected:
	void set_time(byte m_hour=0,byte m_min=0,byte m_sec=0);
public:
	byte get_hour();
	byte get_min();
	byte get_sec();
public:
	static VirtualWifiTime get_now_time();
	CONST_STR string();
	VirtualWifiTime(byte m_hour=0,byte m_min=0,byte m_sec=0);
	int operator-(VirtualWifiTime& time);
	bool operator=(VirtualWifiTime& time);
	VirtualWifiTime(const time_t t);
	~VirtualWifiTime(void);
};



enum protocol
{
	TCP=6,
	UDP=17
};

#define NAMELEN 128
class _declspec(dllimport)  VirtualWifiCountFlowBase:virtual public VirtualWifiException
{
private:
	pcap_t * m_adhandle;
	string data_filter(CONST_STR sz_ip);
protected:
	int m_timeout;
	float m_timesec;/*单位为秒*/
	float m_dtimeout;
protected:
	virtual void handle_data(struct pcap_pkthdr *header,const u_char *pkt_data)=0;
	virtual void handle_data_timeout(struct pcap_pkthdr *header)=0;
public:
	bool init_pcap(VirtualWifiAdapter* adapter,int n_timeout=900);
	int start_capture_flow();
	VirtualWifiCountFlowBase(void);
	~VirtualWifiCountFlowBase(void);
};
