#pragma once
#include "stdafx.h"


class VirtualWifiRegBase
{
private:
	list<CONST_STR>* m_p_child_lst;
	void clear_child_list();     //ÊÍ·Åm_p_child_lstµÄÄÚ´æ
	void clear_value();
	char* m_value_buffer;
	void  init_value_buffer();
	void  free_value_buffer();
	void free_key();
protected:
	HKEY m_open_key;
public:
	VirtualWifiRegBase(void);
	void set_key(HKEY hkey);
	bool open_key(HKEY hKey,CONST_STR sz_sub_key);
	SHORT get_child();
	CONST_STR get_value(CONST_STR value_name);
	bool set_value(CONST_STR value_name,CONST_STR value_data,DWORD d_data_len=0);
	bool delete_value(CONST_STR value_name);
	DWORD create_key(CONST_STR key_name,HKEY& hnewkey);
	~VirtualWifiRegBase(void);
};

