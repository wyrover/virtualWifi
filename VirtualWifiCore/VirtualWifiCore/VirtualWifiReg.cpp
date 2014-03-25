#include "StdAfx.h"
#include "VirtualWifiReg.h"

CONST_STR VirtualWifiReg::SZ_REG_PATH_VIRTUALWIFI="SYSTEM\\CurrentControlSet\\services\\Tcpip\\Parameters\\Interfaces\\";
char* VirtualWifiReg::SZ_REG_VALUE_IP="192.168.2.1";
CONST_STR VirtualWifiReg::SZ_REG_KEYNAME_IPADDRESS="IPAddress";
CONST_STR VirtualWifiReg::SZ_REG_KEYNAME_NAMESERVER="NameServer";
CONST_STR VirtualWifiReg::SZ_REG_VALUE_DNS="8.8.8.8"; //googleµÄdnsµØÖ·
CONST_STR VirtualWifiReg::SZ_REG_VALUE_SUBNETMASK="255.255.255.0";
CONST_STR VirtualWifiReg::SZ_REG_KEYNAME_SUBNETMASK="SubnetMask";

VirtualWifiReg::VirtualWifiReg(void)
{

}


bool VirtualWifiReg::set_dns()
{
	v_log->write_log_come_to("set_dns");
	char sz_buffer[MAX_LEN];
	strcpy(sz_buffer,SZ_REG_VALUE_DNS);
	strcat(sz_buffer,",");
	strcat(sz_buffer,SZ_REG_VALUE_IP);
	return this->set_value(SZ_REG_KEYNAME_NAMESERVER,sz_buffer);
}
bool VirtualWifiReg::open_virtual_adapter_key(CONST_STR key_name)
{
	char sz_buffer[MAX_LEN];
	strcpy(sz_buffer,SZ_REG_PATH_VIRTUALWIFI);
	strcat(sz_buffer,key_name);
	return open_key(HKEY_LOCAL_MACHINE,sz_buffer);
}
bool VirtualWifiReg::set_subnetmask()
{
    return this->set_value(SZ_REG_KEYNAME_SUBNETMASK,SZ_REG_VALUE_SUBNETMASK);
}
VirtualWifiReg::~VirtualWifiReg(void)
{
}
