#pragma once
#include "stdafx.h"

#define TRYEXCEPTION_BEGIN try{
#define TRYEXCEPTION_END   }
#define CATCH(x)           catch(x)
#define DEAL_BEGIN         {
#define DEAL_END           }


enum ERROR_TYPE
{
	ERROR_TYPE_IP,
	ERROR_TYPE_START_WIFI,
	ERROR_TYPE_STOP_WIFI,
	ERROR_TYPE_UNKOWN
};

//异常基类
class __declspec(dllimport) VirtualWifiException
{
private:
	CONST_STR m_mes;
protected:
	ERROR_TYPE m_error_type;
public:
	void set_error_type(ERROR_TYPE error_type);
	void clear_exception();
	CONST_STR get_error_message();
	void set_message(CONST_STR m_mes); //不要传递局部变量的指针
	virtual VirtualWifiException throw_self();
	VirtualWifiException(void);
	~VirtualWifiException(void);
};

