#pragma once
#include "stdafx.h"


enum CLIENTTYPE
{
	CLIENTTYPE_MAIN,
	CLIENTTYPE£ßCONFIG,
	CLIENTYPE_FLOW,
	CLIENTTYPE_UNKOWN
};
class VirtualWifiJudage:virtual protected VirtualWifiConst
{
protected:
	bool is_local(CONST_STR sz_ip);
	CLIENTTYPE get_client_type(char* szrecv);
public:
	VirtualWifiJudage(void);
	~VirtualWifiJudage(void);
};

