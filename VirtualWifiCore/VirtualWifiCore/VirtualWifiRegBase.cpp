#include "StdAfx.h"
#include "VirtualWifiRegBase.h"

VirtualWifiRegBase::VirtualWifiRegBase(void)
{
	// RegOpenKeyEx(HKEY_CURRENT_USER, strKeyPath, 0, KEY_WRITE|KEY_READ, &hSoftKey);
	m_open_key=NULL;
	m_p_child_lst=new list<CONST_STR>();
	m_value_buffer=NULL;
}

bool VirtualWifiRegBase::open_key(HKEY hKey,CONST_STR sz_sub_key)
{
	free_key();
	return RegOpenKeyEx(hKey,sz_sub_key,0,KEY_ALL_ACCESS,&m_open_key)==ERROR_SUCCESS;
}
void VirtualWifiRegBase::free_key()
{
	if (m_open_key!=NULL)
	{
		RegCloseKey(m_open_key);
		m_open_key=NULL;
	}
}
SHORT VirtualWifiRegBase::get_child()
{
	clear_child_list();
	if (m_open_key!=NULL)
	{
		char sz_key_name_buffer[MAX_PATH];
		DWORD i = 0;
		while (RegEnumKey(m_open_key,i,sz_key_name_buffer,sizeof(sz_key_name_buffer)) ==ERROR_SUCCESS)
		{
			char* sz_buffer=new char[strlen(sz_key_name_buffer)+1];
			strcpy(sz_buffer,sz_key_name_buffer);
			m_p_child_lst->push_back(sz_buffer);
			i++;
		}
	}
	return m_p_child_lst->size();
}

void VirtualWifiRegBase::clear_child_list()
{
	list<CONST_STR>::iterator it_child_lst;
	for (it_child_lst=m_p_child_lst->begin();it_child_lst!=m_p_child_lst->end();++it_child_lst)
	{
		delete[] *it_child_lst;
	}
	m_p_child_lst->clear();
}
CONST_STR VirtualWifiRegBase::get_value(CONST_STR value_name)
{
	char sz_value_buffer[MAX_PATH];
	DWORD d_buffer_len=sizeof(sz_value_buffer);
	DWORD dtype;
	if(RegQueryValueEx(m_open_key,value_name,NULL,&dtype,(LPBYTE)sz_value_buffer,&d_buffer_len)==ERROR_SUCCESS)
	{
		free_value_buffer();
		m_value_buffer=new char[strlen(sz_value_buffer)+1];
		strcpy(m_value_buffer,sz_value_buffer);
	}
	else
	{
		return EMPTYSTRING;
	}
	return m_value_buffer;
}
DWORD  VirtualWifiRegBase::create_key(CONST_STR key_name,HKEY& hnewkey)
{
	DWORD dw;
	RegCreateKeyEx(m_open_key,key_name,0,REG_NONE,
		REG_OPTION_NON_VOLATILE,KEY_WRITE|KEY_READ,NULL, 
		&hnewkey,&dw);
	return dw;
}
void VirtualWifiRegBase::init_value_buffer()
{
	m_value_buffer=NULL;
}
void VirtualWifiRegBase::free_value_buffer()
{
	if (m_value_buffer!=NULL)
	{
		delete[] m_value_buffer;
	}
}
bool VirtualWifiRegBase::set_value(CONST_STR value_name,CONST_STR value_data,DWORD d_data_len)
{
	d_data_len=d_data_len==0?strlen(value_data):d_data_len;
	if (d_data_len==0)
	{
		return false;
	}
	return RegSetValueEx(m_open_key,value_name, 0, REG_SZ, (LPBYTE)value_data,d_data_len)==ERROR_SUCCESS;
}
void VirtualWifiRegBase::set_key(HKEY hkey)
{
	if (m_open_key!=NULL)
	{
		RegCloseKey(m_open_key);
	}
	m_open_key=hkey;
}
bool VirtualWifiRegBase::delete_value(CONST_STR value_name)
{
	return RegDeleteValue(m_open_key,value_name)==ERROR_SUCCESS;
}
VirtualWifiRegBase::~VirtualWifiRegBase(void)
{
	free_value_buffer();
	free_key();
}
