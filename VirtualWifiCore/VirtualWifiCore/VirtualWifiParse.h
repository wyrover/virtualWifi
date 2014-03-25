#pragma once
#include "stdafx.h"

//对主界面发送过来的字符串进行解析
class VirtualWifiParse
{
protected:
	NetInfo ParseNetInfo(CONST_STR sz_c);
public:
	VirtualWifiParse(void);
	~VirtualWifiParse(void);
};

