#include "StdAfx.h"
#include "VirtualWifiLog.h"
#include <ctime>

CONST_STR VirtualWifiLog::LOGSTR_RUN_TO="run to ";
CONST_STR VirtualWifiLog::LOGSTR_SUCCESS="success!";
CONST_STR VirtualWifiLog::LOGSTR_COME_TO="come to ";

VirtualWifiLog::VirtualWifiLog(void)
{
	generate_log_file_name();
	m_log_buffer=new char[1024];
	m_log_file=fopen(m_log_file_name,"wb");
	fclose(m_log_file);
}
VirtualWifiLog::VirtualWifiLog(CONST_STR sz_log_name)
{
	m_log_file_name=new char[strlen(sz_log_name)+strlen("log/")+1];
	strcpy(m_log_file_name,"log/");
	strcat(m_log_file_name,"Corelog");
	m_log_buffer=new char[1024*10];
	m_log_file=fopen(m_log_file_name,"wb");
	fclose(m_log_file);
}
void VirtualWifiLog::write_char_log(const char c)
{
	fputc(c,m_log_file);
}
int  VirtualWifiLog::write_str_log(CONST_STR sz_w)
{
	return fputs(sz_w,m_log_file);
}
char* VirtualWifiLog::get_format_current_time()
{
	time_t now;	
	struct tm *fmt;
	time(&now);
	fmt = localtime(&now);
	strftime(sz_time,TIMEMAXLEN,"%Y-%m-%d-%H-%M-%S: ",fmt);
	return sz_time;
}
void VirtualWifiLog::new_line()
{
	 fputc('\n',m_log_file);
}
void VirtualWifiLog::write_log_run_to(CONST_STR sz_log,CONST_STR sz_f)
{
	m_log_file=fopen(m_log_file_name,"a");
	strcpy(m_log_buffer,get_format_current_time());
	strcat(m_log_buffer,LOGSTR_RUN_TO);
	strcat(m_log_buffer,sz_log);
	strcat(m_log_buffer,sz_f);
	write_str_log(m_log_buffer);
	new_line();
	fclose(m_log_file);
}
void VirtualWifiLog::write_log_notime(CONST_STR sz_log,CONST_STR sz_f1/* =EMPTYSTRING */,CONST_STR sz_f2/* =EMPTYSTRING */)
{
	m_log_file=fopen(m_log_file_name,"a");
	strcpy(m_log_buffer,sz_log);
	strcat(m_log_buffer,sz_f1);
	strcat(m_log_buffer,sz_f2);
	write_str_log(m_log_buffer);
	new_line();
	fclose(m_log_file);
}
void VirtualWifiLog::write_log(CONST_STR sz_log,CONST_STR sz_f1/* =EMPTYSTRING */,CONST_STR sz_f2/* =EMPTYSTRING */)
{
	m_log_file=fopen(m_log_file_name,"a");
	strcpy(m_log_buffer,get_format_current_time());
	strcat(m_log_buffer,sz_log);
	strcat(m_log_buffer,sz_f1);
	strcat(m_log_buffer,sz_f2);
	write_str_log(m_log_buffer);
	new_line();
	fclose(m_log_file);
}
void VirtualWifiLog::write_log_success(CONST_STR sz_log)
{
	m_log_file=fopen(m_log_file_name,"a");
	strcpy(m_log_buffer,get_format_current_time());
	strcat(m_log_buffer,sz_log);
	strcat(m_log_buffer,LOGSTR_SUCCESS);
	write_str_log(m_log_buffer);
	new_line();
	fclose(m_log_file);
}
void VirtualWifiLog::write_log_come_to(CONST_STR sz_log)
{
	m_log_file=fopen(m_log_file_name,"a");
	strcpy(m_log_buffer,get_format_current_time());
	strcat(m_log_buffer,LOGSTR_COME_TO);
	strcat(m_log_buffer,sz_log);
	write_str_log(m_log_buffer);
	new_line();
	fclose(m_log_file);
}
void VirtualWifiLog::generate_log_file_name()
{
	m_log_file_name=new char[FILENAMEMAXLEN];
	time_t now;	
	struct tm *fmt;
	time(&now);
	fmt = localtime(&now);
	strftime(m_log_file_name,FILENAMEMAXLEN,"log/corelog.log",fmt);
}
void VirtualWifiLog::write_log_error_code(CONST_STR sz_c,int nerror_code)
{
	m_log_file=fopen(m_log_file_name,"a");
	strcpy(m_log_buffer,get_format_current_time());
	strcat(m_log_buffer,sz_c);
	strcat(m_log_buffer," the error code is ");
	char c[16];
	sprintf(c,"%d",nerror_code);
	strcat(m_log_buffer,c);
	write_str_log(m_log_buffer);
	new_line();
	fclose(m_log_file);
}
void VirtualWifiLog::write_log_error_code(CONST_STR sz_c,long nerror_code)
{
	m_log_file=fopen(m_log_file_name,"a");
	strcpy(m_log_buffer,get_format_current_time());
	strcat(m_log_buffer,sz_c);
	strcat(m_log_buffer," the error code is ");
	char c[16];
	sprintf(c,"%d",nerror_code);
	strcat(m_log_buffer,c);
	write_str_log(m_log_buffer);
	new_line();
	fclose(m_log_file);
}

VirtualWifiLog::~VirtualWifiLog(void)
{
	delete[] m_log_buffer;
	delete[] m_log_file_name;
}
