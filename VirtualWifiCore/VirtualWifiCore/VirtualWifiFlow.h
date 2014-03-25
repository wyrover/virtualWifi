#pragma once
#include "stdafx.h"
enum link_type
{
	up_link_type=0,
	down_link_type=1,
	unkown_link_type
};

#define MICROSECONDS 1000000
#define ONEK           1024
#define  llong long long

class VirtualWifiFlow
{
private:
	llong m_ldowntotal;/*µ¥Î»×Ö½Ú*/
	llong m_luptoal;
private:
	u_long m_currentdown;
	u_long m_currentup;
public:
	void add_downflow(u_long ulszie);
	void add_upflow(u_long ulszie);
	void add_total_flow(u_long ulszie,link_type lt);
	void add_flow(u_long ulszie,link_type lt);

	llong get_downtotal();
	llong get_uptotal();

	u_long get_currentdown();
	u_long get_currentup();

	void clear_current();
	void clear_total();

	float calculate_upspeed(u_int utime);
	float calculate_downspeed(u_int utime);
	VirtualWifiFlow(void);
	~VirtualWifiFlow(void);
};

