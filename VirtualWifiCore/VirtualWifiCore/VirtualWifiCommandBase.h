#pragma once
#include "stdafx.h"

#define COMMANDLEN 1024

#pragma region 表示编码

typedef  char CODING;
#define ASCIICODING (CODING)0
#define UNICODECODING (CODING)1

#pragma endregion 


#pragma  warning(disable:4200)

class VirtualWifiCommandBase
{
public:
	struct VirtualWifiCommandStruct 
	{
		char m_id;
		CODING m_coding;
		USHORT m_commandlen;
		char  m_command[0];
	};
protected:
	static const int N_MIN_LEN; //命令缓冲区的最小长度
	static const int N_LEN_START;
	static const int N_COMMAND_START;
protected:
	VirtualWifiCommandStruct* m_virtualwificommandstruct;
	char* m_szcommand;
	int m_ncommandalllen;
	int m_ncommandlen;
public:
	int& get_command_all_len();
	char* get_command_buffer();
	VirtualWifiCommandStruct* get_command_struct();
	void clear();
	VirtualWifiCommandBase(int ncommandlen=COMMANDLEN);
	~VirtualWifiCommandBase(void);
};

