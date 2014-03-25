#pragma once
#include "stdafx.h"

CONST_STR VirtualWifiManageAdapter::VIRTUALADAPTERNAME="Microsoft Virtual WiFi Miniport Adapter";

VirtualWifiManageAdapter::VirtualWifiManageAdapter()
{
	m_adapterinfo=NULL;
}
IEnumVARIANT* VirtualWifiManageAdapter::get_adapterlist()
{
	return pAdapterList;
}
HRESULT VirtualWifiManageAdapter::InitNetSharingManger()
{
	v_log->write_log_come_to("VirtualWifiManageAdapter::InitNetSharingManger()");
	HRESULT hr=CoInitialize(NULL);
	if (hr!=S_OK)
	{
		error_deal(hr);
		v_log->write_log_error_code("CoInitialize ",hr);
	}
	hr=CoInitializeSecurity(NULL,-1,NULL,NULL,RPC_C_AUTHN_LEVEL_PKT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL, EOAC_NONE, NULL);
	if (hr!=S_OK)
	{
		v_log->write_log_error_code("CoInitializeSecurity ",hr);
		error_deal(hr);
	}
	return ::CoCreateInstance(__uuidof(NetSharingManager),
		NULL,CLSCTX_ALL,__uuidof(INetSharingManager),(void**)&pNSM);
}

void VirtualWifiManageAdapter::error_deal(HRESULT hr)
{
	switch (hr)
	{
	case E_ABORT:
		v_log->write_log("the hr error is ","E_ABORT");
		break;
	case E_FAIL:
		v_log->write_log("the hr error is ","E_FAIL");
		break;
	case E_INVALIDARG:
		v_log->write_log("the hr error is ","E_INVALIDARG");
		break;
	case E_NOINTERFACE:
		v_log->write_log("the hr error is ","E_NOINTERFACE");
		break;
	case E_NOTIMPL:
		v_log->write_log("the hr error is ","E_NOTIMPL");
		break;
	case E_OUTOFMEMORY:
		v_log->write_log("the hr error is ","E_OUTOFMEMORY");
		break;
	case E_POINTER:
		v_log->write_log("the hr error is ","E_POINTER");
		break;
	case E_UNEXPECTED:
		v_log->write_log("the hr error is ","E_UNEXPECTED");
		break;
	default:
		v_log->write_log("UnKown error");
	}
	
}
HRESULT VirtualWifiManageAdapter::InitAdapterList()
{
	v_log->write_log_come_to(" VirtualWifiManageAdapter::InitAdapterList()");
	HRESULT hr=InitNetSharingManger();	
	if (hr!=S_OK)
	{
		error_deal(hr);
		v_log->write_log("init NetSharingManager fail");
		return hr;
	}
	hr=E_ABORT;
	INetSharingEveryConnectionCollection* pNSECC = NULL;
	hr = pNSM->get_EnumEveryConnection (&pNSECC);
	if (pNSECC)
	{
		v_log->write_log_success("pNSM->get_EnumEveryConnection ");
		IUnknown * pUnk = NULL;
		hr=pNSECC->get__NewEnum(&pUnk);
		if (pUnk)
		{
			hr = pUnk->QueryInterface (__uuidof(IEnumVARIANT),
				(void**)&pAdapterList);
			
			pUnk->Release();
		}
	}
	else
	{
		error_deal(hr);
		v_log->write_log_error_code("get_EnumEveryConnection ",hr);
		v_log->write_log("pNSM->get_EnumEveryConnection fail");
	}
	return hr;
}

bool VirtualWifiManageAdapter::CheckAdapterIsConnected(CONST_STR sz_adapter_name)
{
    bool is_connected=false;
	if (InitAdapterList()==S_OK)
	{
		v_log->write_log_success("InitAdapterList ");
		INetConnection* pNC=NULL;
		INetSharingConfiguration * pNSC = NULL;
		VARIANT v;
		VariantInit (&v);
		NETCON_PROPERTIES* pVWifi = NULL;
		while (S_OK==pAdapterList->Next (1, &v, NULL))
		{
			if (V_VT(&v)==VT_UNKNOWN)
			{
				V_UNKNOWN (&v)->QueryInterface (__uuidof(INetConnection),(void**)&pNC);
				if (pNC)
				{
					NETCON_PROPERTIES* pNP = NULL;
					pNC->GetProperties(&pNP);
					setlocale(LC_ALL, "chs");

					wstring wstr_pszwName(pNP->pszwName);
					string str_pszwName=wsTos(wstr_pszwName);

					if (!strcmp(str_pszwName.c_str(),sz_adapter_name))
					{
						if (pNP->Status==NCS_CONNECTED)
						{
							is_connected=true;
						}
						break;
					}
				}
			}
		}
	}
	ReleaseNetSharingManger();
	return is_connected;
}
string VirtualWifiManageAdapter::ptchar_to_string(const wchar_t* sz_w)
{

	if (sz_w==NULL)
	{
		return string(EMPTYSTRING);
	}
	wstring wstr_pszwName(sz_w);
	return wsTos(wstr_pszwName);
}

string VirtualWifiManageAdapter::wsTos(wstring& ws)
{
	string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
ADAPTERRET VirtualWifiManageAdapter::UnSharingAdapter(CONST_STR sz_adapter_name)
{
	v_log->write_log("the adapter name is ",sz_adapter_name);
	v_log->write_log_come_to("VirtualWifiManageAdapter::UnSharingAdapter(CONST_STR sz_ada");
	HRESULT hr;
	hr=InitAdapterList();
	if (hr!=S_OK)
	{
		return INITFAIL;
	}
	v_log->write_log_success("InitAdapterList ");
	bool bFindNetAdapter=false;
	INetConnection* pNC=NULL;
	INetSharingConfiguration * pNSC = NULL;
	VARIANT v;
	VariantInit (&v);
	NETCON_PROPERTIES* pVWifi = NULL;
	while (S_OK==pAdapterList->Next (1, &v, NULL))
	{
		if (V_VT(&v)==VT_UNKNOWN)
		{
			V_UNKNOWN (&v)->QueryInterface (__uuidof(INetConnection),(void**)&pNC);
			if (pNC)
			{
				NETCON_PROPERTIES* pNP = NULL;
				pNC->GetProperties(&pNP);
				setlocale(LC_ALL, "chs");

				v_log->write_log_run_to("adapter while");
				if (pNP!=NULL&&pNP->pszwName!=NULL)
				{
					string str_pszwName=ptchar_to_string(pNP->pszwName);

					CONST_STR pszwName=str_pszwName.c_str();
					v_log->write_log("come in while the name is",pszwName);

					if (!strcmp(pszwName,sz_adapter_name)&&!bFindNetAdapter)
					{
						v_log->write_log_run_to("share the adapter");
						bFindNetAdapter=true;
						INetSharingConfiguration * pVWifiNSC = NULL;
						hr=pNSM->get_INetSharingConfigurationForINetConnection(pNC,&pVWifiNSC);
						if (hr!=S_OK)
						{
							v_log->write_log_error_code("get_INetSharingConfigurationForINetConnection",hr);
							return BINDNETFAIL;
						}
						hr=pVWifiNSC->DisableSharing();
						if (hr!=S_OK)
						{
							return BINDNETFAIL;
						}
					}
				}

			}
		}
	}
	ReleaseNetSharingManger();
	if (!bFindNetAdapter)
	{
		return NOTFINDNET;
	}
	return SUCCESS;
}
ADAPTERRET VirtualWifiManageAdapter::SetSharingAdapter(CONST_STR sz_adapter_name,const char* strVirtualAdpater/* =m_virtualadaptername */)
{
	v_log->write_log("the adapter name is ",sz_adapter_name);
	v_log->write_log_come_to("VirtualWifiManageAdapter::SetSharingAdapter(CONST_STR sz_ada");
	HRESULT hr;
	hr=InitAdapterList();
	if (hr!=S_OK)
	{
		return INITFAIL;
	}
	v_log->write_log_success("InitAdapterList ");
	bool bFindNetAdapter=false;
	bool bFindVirtualAdapter=false;
	INetConnection* pNC=NULL;
	INetSharingConfiguration * pNSC = NULL;
	VARIANT v;
	VariantInit (&v);
	NETCON_PROPERTIES* pVWifi = NULL;
	while (S_OK==pAdapterList->Next (1, &v, NULL))
	{
		if (V_VT(&v)==VT_UNKNOWN)
		{
			V_UNKNOWN (&v)->QueryInterface (__uuidof(INetConnection),(void**)&pNC);
			if (pNC)
			{
				NETCON_PROPERTIES* pNP = NULL;
				pNC->GetProperties(&pNP);
				setlocale(LC_ALL, "chs");

				v_log->write_log_run_to("adapter while");
				if (pNP!=NULL&&pNP->pszwName!=NULL)
				{
					//转换字符串
					wstring wstr_pszwName(pNP->pszwName);
					string str_pszwName=wsTos(wstr_pszwName);

					CONST_STR pszwName=str_pszwName.c_str();
					v_log->write_log("come in while the name is ",pszwName);

					if (!strcmp(pszwName,sz_adapter_name)&&!bFindNetAdapter)//指定分享的适配器
					{
						v_log->write_log_run_to("share the adapter");
						bFindNetAdapter=true;
						INetSharingConfiguration * pVWifiNSC = NULL;
						hr=pNSM->get_INetSharingConfigurationForINetConnection(pNC,&pVWifiNSC);
						if (hr!=S_OK)
						{
							v_log->write_log_error_code("get_INetSharingConfigurationForINetConnection",hr);
							return BINDNETFAIL;
						}
						hr=pVWifiNSC->EnableSharing(ICSSHARINGTYPE_PUBLIC);
						if (hr!=S_OK)
						{
							v_log->write_log_error_code("ICSSHARINGTYPE_PUBLIC",hr);
							return BINDNETFAIL;
						}
					}
				}
		       
				if (pNP!=NULL&&pNP->pszwDeviceName!=NULL)
				{
					wstring wstr_devicename(pNP->pszwDeviceName);
					string str_devicename=wsTos(wstr_devicename);
					CONST_STR pszwDeviceName=str_devicename.c_str();
					v_log->write_log("come in while the device name is",pszwDeviceName);

					if(pszwDeviceName!=NULL&&str_devicename.find(strVirtualAdpater)!=string::npos&&!bFindVirtualAdapter) //根据设备名,找到虚拟网卡
					{
						bFindVirtualAdapter=true;
						INetSharingConfiguration * pVWifiNSC = NULL;
						hr=pNSM->get_INetSharingConfigurationForINetConnection(pNC,&pVWifiNSC);
						if (hr!=S_OK)
						{
							v_log->write_log_error_code("get_INetSharingConfigurationForINetConnection",hr);
							return BINDVIRTUALFAIL;
						}
						hr=pVWifiNSC->EnableSharing(ICSSHARINGTYPE_PRIVATE);
						if (hr!=S_OK)
						{
							v_log->write_log_error_code("ICSSHARINGTYPE_PRIVATE",hr);
							error_deal(hr);
							return BINDVIRTUALFAIL;
						}
					}
				}
			
			}
		}
	}
	ReleaseNetSharingManger();
	if (!bFindNetAdapter)
	{
		return NOTFINDNET;
	}
	if (!bFindVirtualAdapter)
	{
		return NOTFINVIRTUAL;
	}
	return SUCCESS;
}
void VirtualWifiManageAdapter::ReleaseNetSharingManger()
{
	pNSM->Release();
	pAdapterList->Release();
	CoUninitialize();
}

void VirtualWifiManageAdapter::free_adapterinfo()
{
	if (m_adapterinfo!=NULL)
	{
		delete[] m_adapterinfo;
		m_adapterinfo=NULL;
	}
}
void VirtualWifiManageAdapter::GetAllAdapterInfo()
{
	IP_ADAPTER_INFO Interface[32];
	PIP_ADAPTER_INFO NetInterface = NULL;
	DWORD Result = 0;
	unsigned long Length = sizeof(Interface);
	Result = GetAdaptersInfo(Interface, &Length);
	if (Result != NO_ERROR)
	{
		v_log->write_log_error_code("the adapter code is ",(int)Result);
		set_message(GET_ADAPTER_INFO_ERROR);
		throw_self();
	}
		NetInterface = Interface;
	    int nadaptertotal=0;
		while (NetInterface)
		{
			NetInterface = NetInterface->Next;
			nadaptertotal++;
		}
	free_adapterinfo();
	m_adapterinfo=new IP_ADAPTER_INFO[nadaptertotal];
	unsigned long Size=sizeof(IP_ADAPTER_INFO)*nadaptertotal;
	memcpy(m_adapterinfo,Interface,Size);
}

string VirtualWifiManageAdapter::GetVirtualAdapterGuid()
{
	v_log->write_log_come_to("GetVirtualAdapterGuid");
	GetAllAdapterInfo();
	PIP_ADAPTER_INFO NetInterface = m_adapterinfo;
	while (NetInterface)
	{
		v_log->write_log(NetInterface->Description);
		string strDescription(NetInterface->Description);
		if (strDescription.find(VIRTUALADAPTERNAME)!=string::npos)
		{
			return string(NetInterface->AdapterName);
			
		}
		NetInterface = NetInterface->Next;
	}
	v_log->write_log("Not find adapter");
	return NULL;
}

VirtualWifiManageAdapter::~VirtualWifiManageAdapter()
{
	delete[] m_adapterinfo;
}