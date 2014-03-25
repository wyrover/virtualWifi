#include "StdAfx.h"
#include "VirtualWifiAnalysis.h"


VirtualWifiAnalysis::VirtualWifiAnalysis(void)
{
}

void VirtualWifiAnalysis::analysis()
{ 
}
bool VirtualWifiAnalysis::get_config_bool_value(CONST_STR sz_c)
{
	return sz_c[0]==1;
}
void VirtualWifiAnalysis::analysis(CONST_STR sz_c,int nrecv)
{
	p_command_struct pcommand_struct=(p_command_struct)sz_c;
	char c_id=pcommand_struct->m_id;
	switch(c_id)
	{
	case  ID_START_WIFI:
		{
			on_start_wifi();
			break;
		}
	case  ID_STOP_WIFI:
		{
			on_stop_wifi();
			break;
		}
	case ID_GET_CLIENT_LIST:
		{
			on_get_client_list();
			break;
		}
	case ID_REFRESH_SHARE_NET:
		{
			on_refresh_share_net();
			break;
		}
	case ID_CONFIG_AUTORUN:
		{
			on_config_autorun();
			break;
		}
	case ID_CONFIG_AUTOSTARTWIFI:
		{
			on_config_auto_start_wifi();
			break;
		}
	case ID_CONFIG_EVENTBALLOONTIP:
		{
			on_config_eventballoontip();
			break;
		}
	case ID_ONCLOSEBUTTONDOWN:
		{
			on_closebutton_down();
			break;
		}
	case ID_CONFIG_PROVINCEMEMORY:
		{
			on_config_provincememory();
           break;
		}
	case ID_FLOW_MONITOR:
		{
			on_config_flow_monitor();
			break;
		}
	}
}

void VirtualWifiAnalysis::analysis_flow(CONST_STR sz_c,int nrecv)
{
	p_command_struct pcommand_struct=(p_command_struct)sz_c;
	char c_id=pcommand_struct->m_id;
	switch(c_id)
	{
	case  ID_FLOW_POS:
		{
			on_flow_reset_pos();
			break;
		}
	}
}
VirtualWifiAnalysis::~VirtualWifiAnalysis(void)
{
	
}
