#include "stdafx.h"


class VirtualWifiIdentifier
{
public:
#pragma region 发送部分的标识符
	static const char ID_ADAPTERINFO;
	static const char ID_WIFIACCOUNT;
	static const char ID_TIPINFO;
	static const char ID_STARTWIFISUCCESS;
	static const char ID_STARTFAIL;
	static const char ID_STOPWIFISUCCESS;
	static const char ID_SETSELECTEDADAPTER;
	static const char IDENTIFIERS_WINDOWS;
	static const char ID_SOFTINFO;

	static const char ID_SETTITLE;
	static const char ID_CONFIG;
	static const char ID_SHOW;
    static const char ID_BACK;
	static const char ID_CLEAR_SHARE_NET;

	static const char ID_AUTORUN;
	static const char ID_SOUNDTIP;
	static const char ID_SOUNDPATH;
	static const char ID_AUTOSTARTWIFI;
	static const char ID_PROVINCEMEMORY;
	static const char ID_STARTSUCCESSBALLOONTIP;
	static const char ID_HASNEWCLIENTBALLOONTIP;
	static const char ID_SET_CLIENT_NUM;
	static const char ID_EXIT;
	static const char ID_RESETPOS;
	static const char ID_SEND_CLIENT_LIST;
#pragma endregion 


#define MAX_LEN  1024
#pragma region 接收部分的标识符
    #define  ID_START_WIFI 'A'
    #define  ID_STOP_WIFI  'B'
    #define  ID_REFRESH_SHARE_NET 'D'

    #define  ID_CONFIG_AUTORUN 4
    #define  ID_CONFIG_AUTOSTARTWIFI 5
    #define  ID_CONFIG_EVENTBALLOONTIP 6
	#define  ID_CONFIG_PROVINCEMEMORY 11
    #define  ID_FLOW_MONITOR  12
    #define  ID_GET_CLIENT_LIST  'E'
    #define  ID_ONCLOSEBUTTONDOWN 'F'

    #define  ID_FLOW_POS 'P'
#pragma endregion

   #define  SEPARATOR "&"
   #define  WSEPARATOR L"&" 
};