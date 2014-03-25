#include "stdafx.h"
#include "VirtualWifiCommandBase.h"

const int VirtualWifiCommandBase::N_MIN_LEN=5;
const int VirtualWifiCommandBase::N_LEN_START=2;
const int VirtualWifiCommandBase::N_COMMAND_START=4;

VirtualWifiCommandBase::VirtualWifiCommandBase(int ncommandlen/* =COMMANDLEN */)
{
	if (ncommandlen>N_MIN_LEN)
	{
		m_ncommandlen=ncommandlen;
		m_ncommandalllen=ncommandlen+N_COMMAND_START;
		m_szcommand=new char[m_ncommandalllen];
		m_virtualwificommandstruct=(VirtualWifiCommandStruct*)m_szcommand;
	//	m_virtualwificommandstruct->m_command=(char*)m_virtualwificommandstruct+sizeof(VirtualWifiCommandStruct)-sizeof(char*);
	}
}
char* VirtualWifiCommandBase::get_command_buffer()
{
	return m_szcommand;
}
VirtualWifiCommandBase::VirtualWifiCommandStruct* VirtualWifiCommandBase::get_command_struct()
{
	return m_virtualwificommandstruct;
}
int& VirtualWifiCommandBase::get_command_all_len()
{
	return m_ncommandalllen;
}
void VirtualWifiCommandBase::clear()
{
	memset(m_szcommand,0,m_ncommandalllen);
}
VirtualWifiCommandBase::~VirtualWifiCommandBase()
{
	delete[] m_szcommand;
}