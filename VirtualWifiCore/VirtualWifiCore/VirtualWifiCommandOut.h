#include "stdafx.h"
#include "VirtualWifiCommandBase.h"



//组织成发送给主界面的字节流
//格式:第一位标识符,第二位表示编码,第三,四位是command的长度

class VirtualWifiCommandOut:virtual public VirtualWifiCommandBase //虚继承VirtualWifiCommandBase
{
private:
	int m_add_command_len;
public:
	void add_id(char c);
	void add_command(CONST_STR sz_c,CODING coding=ASCIICODING);
	void add_command(CONST_STR sz_c,int nLen,CODING coding=ASCIICODING);
	void add_command(CONST_WSTR sz_wc,CODING conding=UNICODECODING);
	void add_command_lst(list<CONST_STR>& sz_c_lst,CODING coding=ASCIICODING);
	void add_command_lst(list<string>& sz_str_lst,CODING coding=ASCIICODING);
	void add_command_lst(list<wstring>& sz_wstr_lst,CODING coding=UNICODECODING);
	char* get_command() const;
	int& get_add_command_len();
	 VirtualWifiCommandOut();
	 ~VirtualWifiCommandOut();
};