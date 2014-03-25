#include "stdafx.h"

const char* VirtualWifiExecuteCmd::SZ_PREFIX="cmd.exe /c ";
const int VirtualWifiExecuteCmd::N_PREFIX_LEN=strlen(SZ_PREFIX);
#pragma warning(disable:4996)

VirtualWifiExecuteCmd::VirtualWifiExecuteCmd(char* szcommand/* =EMPTYSTRING */)
{
	strcpy(m_szcommand,SZ_PREFIX);
	m_isaddcommand=false;
	if (szcommand!=EMPTYSTRING)
	{
		AddCommand(szcommand);
		m_isaddcommand=true;
	}
}

void VirtualWifiExecuteCmd::AddCommand(char* szcommand)
{
   int nMaxCopy=sizeof(m_szcommand)-N_PREFIX_LEN;
   int nCommand=strlen(szcommand);
   if (nMaxCopy<nCommand)
   {
	   return;
   }
   strcat(m_szcommand,szcommand);
}


bool VirtualWifiExecuteCmd::Execute(char* szcommand/* =EMPTYSTRING */)
{
	if (!m_isaddcommand&&szcommand!=EMPTYSTRING)
	{
       AddCommand(szcommand);
	   m_isaddcommand=false;
	}

	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead,&hWrite,&sa,0)) {
		return false;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &pi, sizeof(PROCESS_INFORMATION) );
	ZeroMemory( &si, sizeof(STARTUPINFO) );
	si.cb = sizeof(STARTUPINFO);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


	if (!CreateProcess(NULL,m_szcommand,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) 
	{
		return false;
	}
    
	CloseHandle(hWrite);

	char buffer[256] = {0};

	DWORD bytesRead=0;
	m_reslut.clear();
	while (true)
	{
		ReadFile(hRead,buffer,sizeof(buffer),&bytesRead,NULL);
		if (bytesRead>0)
		{

			m_reslut.append(buffer);
		}
		else
		{
			break;
		}
	}
	CloseHandle(hRead);

	return true;
}

const char* VirtualWifiExecuteCmd::GetReslut()
{
	return m_reslut.c_str();
}