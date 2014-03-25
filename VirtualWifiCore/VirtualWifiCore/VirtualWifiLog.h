#pragma once
#include "stdafx.h"

#define FILENAMEMAXLEN 48
#define TIMEMAXLEN 32

class VirtualWifiLog
{
private:
	static CONST_STR LOGSTR_RUN_TO;
	static CONST_STR LOGSTR_SUCCESS;
	static CONST_STR LOGSTR_COME_TO;
private:
	char* m_log_file_name;
	FILE* m_log_file;
	char* m_log_buffer;
	char sz_time[TIMEMAXLEN];
protected:
	int write_str_log(CONST_STR sz_w);
	void write_char_log(const char c);
	char* get_format_current_time();
	void new_line();
public:
	void generate_log_file_name();
	CONST_STR get_log_file_name();
	void write_log_run_to(CONST_STR sz_log,CONST_STR sz_f=EMPTYSTRING);   //写入文件会以run to形式写入
	void write_log_success(CONST_STR sz_log);
	void write_log_notime(CONST_STR sz_log,CONST_STR sz_f1=EMPTYSTRING,CONST_STR sz_f2=EMPTYSTRING);
	void write_log_come_to(CONST_STR sz_log);
	void write_log(CONST_STR sz_log,CONST_STR sz_f1=EMPTYSTRING,CONST_STR sz_f2=EMPTYSTRING);
	void VirtualWifiLog::write_log_error_code(CONST_STR sz_c,long nerror_code);
	void write_log_error_code(CONST_STR sz_c,int nerror_code);
	VirtualWifiLog(CONST_STR sz_log_name);
	VirtualWifiLog(void);
	~VirtualWifiLog(void);
};

