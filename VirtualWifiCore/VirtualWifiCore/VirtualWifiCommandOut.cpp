#include "stdafx.h"


VirtualWifiCommandOut::VirtualWifiCommandOut()
{

}


VirtualWifiCommandOut::~VirtualWifiCommandOut()
{
	delete[] m_szcommand;
}

void VirtualWifiCommandOut::add_id(char c)
{
	m_virtualwificommandstruct->m_id=c;
}

void VirtualWifiCommandOut::add_command(CONST_WSTR sz_wc,CODING conding/* =UNICODECODING */)
{
	add_command((CONST_STR)sz_wc,wcslen(sz_wc)*2,conding);
}
void VirtualWifiCommandOut::add_command(CONST_STR sz_c,CODING coding/* =ASCIICODING */)
{
	add_command(sz_c,strlen(sz_c),coding);
}
void VirtualWifiCommandOut::add_command(CONST_STR sz_c,int nLen,CODING coding/* =ASCIICODING */)
{
	m_virtualwificommandstruct->m_coding=coding;
	int nCopy=nLen>m_ncommandlen?m_ncommandlen:nLen;
	memcpy(m_virtualwificommandstruct->m_command,sz_c,nCopy);
	m_virtualwificommandstruct->m_commandlen=(USHORT)nLen;
	m_add_command_len=nLen+N_COMMAND_START;
}
void VirtualWifiCommandOut::add_command_lst(list<wstring>& sz_wstr_lst,CODING coding/* =UNICODECODING */)
{
	list<wstring>::iterator it_sz_c_lst=sz_wstr_lst.begin();
	int nCopyStart=0;
	for (;;)
	{
		CONST_WSTR copy_str=it_sz_c_lst->c_str();
		int nCopyLen=wcslen(copy_str)*2;
		memcpy(nCopyStart+m_virtualwificommandstruct->m_command,(CONST_STR)copy_str,nCopyLen);
		nCopyStart+=nCopyLen;
		++it_sz_c_lst;
		if (it_sz_c_lst==sz_wstr_lst.end())
		{
			break;
		}
		memcpy(m_virtualwificommandstruct->m_command+nCopyStart,&WSEPARATOR,sizeof(WSEPARATOR));
		nCopyStart+=2;
	}
	m_virtualwificommandstruct->m_commandlen=(USHORT)nCopyStart;
	m_add_command_len=nCopyStart+N_COMMAND_START;
    m_virtualwificommandstruct->m_coding=coding;
}
void VirtualWifiCommandOut::add_command_lst(list<string>& sz_str_lst,CODING coding/* =ASCIICODING */)
{
	list<string>::iterator it_sz_c_lst=sz_str_lst.begin(); 
	int nCopyStart=0;
	for (;;)
	{
		CONST_STR copy_str=it_sz_c_lst->c_str();
		int nCopyLen=strlen(copy_str);
		memcpy(nCopyStart+m_virtualwificommandstruct->m_command,copy_str,nCopyLen);
		nCopyStart+=nCopyLen;
		++it_sz_c_lst;
		if (it_sz_c_lst==sz_str_lst.end())
		{
			break;
		}
		memcpy(m_virtualwificommandstruct->m_command+nCopyStart,&SEPARATOR,sizeof(SEPARATOR));
		nCopyStart++;
	}
	m_virtualwificommandstruct->m_commandlen=(USHORT)nCopyStart;
	m_add_command_len=nCopyStart+N_COMMAND_START;
	m_virtualwificommandstruct->m_coding=coding;
}
void VirtualWifiCommandOut::add_command_lst(list<CONST_STR>& sz_c_lst,CODING coding/* =ASCIICODING */)
{
	list<CONST_STR>::iterator it_sz_c_lst=sz_c_lst.begin();
	int nCopyStart=0;
	for (;;)
	{
       CONST_STR copy_str=*it_sz_c_lst;
	   int nCopyLen=strlen(copy_str);
	   memcpy(nCopyStart+m_virtualwificommandstruct->m_command,copy_str,nCopyLen);
	   nCopyStart+=nCopyLen;
	   ++it_sz_c_lst;
	   if (it_sz_c_lst==sz_c_lst.end())
	   {
		   break;
	   }
	   memcpy(m_virtualwificommandstruct->m_command+nCopyStart,&SEPARATOR,sizeof(SEPARATOR));
	   nCopyStart++;
	}
	m_virtualwificommandstruct->m_commandlen=(USHORT)nCopyStart;
	m_add_command_len=nCopyStart+N_COMMAND_START;
	m_virtualwificommandstruct->m_coding=coding;
}

int& VirtualWifiCommandOut::get_add_command_len()
{
	return m_add_command_len;
}
char* VirtualWifiCommandOut::get_command() const
{
	return m_szcommand;
}