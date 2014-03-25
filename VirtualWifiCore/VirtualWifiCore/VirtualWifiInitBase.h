#pragma once
#include "stdafx.h"

class VirtualWifiInitBase
{
protected:
  struct  VirtualWifiInitStruct
	{
		CONST_STR sz_c;
		USHORT s_sz_c_len;
	};
private:
	list<VirtualWifiInitStruct> m_lstinitstruct;
	list<VirtualWifiInitStruct>::iterator m_it_lstinitstruct;
	bool m_bcheck_begin;
public:
	bool add_init_command(CONST_STR sz_c,int& ncommandlen); //传递的字节流,自己申请内存
	bool add_init_command(VirtualWifiInitStruct& virtualwifistruct);
	void remove_all_init_command();

	//获取数据的三个方法
	bool has_next();  //是否有下一个数据
	void reset_data(); //重置为list的起点
	VirtualWifiInitStruct& current_data(); //获取当前指向的数据

	VirtualWifiInitBase();
	~VirtualWifiInitBase();
};

