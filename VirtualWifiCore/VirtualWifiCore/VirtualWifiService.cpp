#include "StdAfx.h"
#include "VirtualWifiService.h"


VirtualWifiService::VirtualWifiService(void)
{
	m_hSC = OpenSCManager( NULL,NULL, SC_MANAGER_ALL_ACCESS);
}

DWORD VirtualWifiService::CheckServiceStatus(CONST_STR pServiceName)
{
	if( m_hSC == NULL)
	{
		return GetLastError();
	}
	SC_HANDLE hSvc = OpenService( m_hSC, pServiceName,
		SERVICE_QUERY_STATUS );
	if( hSvc == NULL)
	{
		return GetLastError();
	}
	// 获得服务的状态
	SERVICE_STATUS status;
	if( QueryServiceStatus( hSvc, &status) == FALSE)
	{
		CloseServiceHandle( hSvc);
		return GetLastError();
	}
	CloseServiceHandle( hSvc);
	return status.dwCurrentState;
}
DWORD VirtualWifiService::StartService(CONST_STR pServiceName)
{

	if( m_hSC == NULL)
	{
		return GetLastError();
	}

	SC_HANDLE hSvc = OpenService( m_hSC, pServiceName,
		SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		return GetLastError();
	}
	ChangeServiceConfig(hSvc,SERVICE_NO_CHANGE,SERVICE_AUTO_START,SERVICE_NO_CHANGE,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
	BOOL bIsStart=::StartService(hSvc,0,NULL);
	if (!bIsStart)
	{
		CloseServiceHandle( hSvc);
		return GetLastError();
	}
	CloseServiceHandle( hSvc);
	return S_OK;
} 
DWORD VirtualWifiService::StopService(CONST_STR pServiceName)
{

	if( m_hSC == NULL)
	{
		return GetLastError();
	}
	SERVICE_STATUS status;
	SC_HANDLE hSvc = OpenService( m_hSC, pServiceName,
		SERVICE_ALL_ACCESS);
	if(ControlService(hSvc,SERVICE_CONTROL_STOP,&status))
	{
		return S_OK;
	}
	return GetLastError();
}
void VirtualWifiService::PrintAllService()
{
	VirtualWifiLog* log_file_started=new VirtualWifiLog("All Service Infomation with started.txt");
	VirtualWifiLog* log_file_nostart=new VirtualWifiLog("All Service Infomation with nostart.txt");
	v_log->write_log_come_to("PrintAllService");

	LPENUM_SERVICE_STATUS lpServices    = NULL;
	DWORD    nSize = 0;
	DWORD    n;
	DWORD    nResumeHandle = 0;

	lpServices = (LPENUM_SERVICE_STATUS) LocalAlloc(LPTR, 100 * 1024);      //注意分配足够的空间
	EnumServicesStatus(m_hSC,SERVICE_WIN32,
		SERVICE_STATE_ALL,
		(LPENUM_SERVICE_STATUS)lpServices,
		64 * 1024,
		&nSize,
		&n,
		&nResumeHandle);
	for ( DWORD i = 0; i < n; i++)
	{
		if ( lpServices[i].ServiceStatus.dwCurrentState!=SERVICE_STOPPED)
		{
			log_file_started->write_log_notime(lpServices[i].lpServiceName,lpServices[i].lpDisplayName,"已启动");
		}
		log_file_nostart->write_log_notime(lpServices[i].lpServiceName,lpServices[i].lpDisplayName,"未启动");
	}
	delete log_file_nostart;
	delete log_file_started;
}
VirtualWifiService::~VirtualWifiService(void)
{
	CloseServiceHandle( m_hSC);
}
