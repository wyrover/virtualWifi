#include "stdafx.h"

VirtualWifiConfig::VirtualWifiConfig()
{
	m_configinfo=ParseConfig();
}
void VirtualWifiConfig::modify_config()
{
    ModifyConfig(*m_configinfo);
}