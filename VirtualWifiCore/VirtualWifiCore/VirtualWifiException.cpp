#include "StdAfx.h"
#include "VirtualWifiException.h"


VirtualWifiException::VirtualWifiException(void)
{
	clear_exception();
}

CONST_STR VirtualWifiException::get_error_message()
{
	return m_mes;
}
void VirtualWifiException::set_message(CONST_STR m_mes)
{
	this->m_mes=m_mes;
}
VirtualWifiException VirtualWifiException::throw_self()
{
	throw *this;
}
void VirtualWifiException::set_error_type(ERROR_TYPE error_type)
{
	m_error_type=error_type;
}
void VirtualWifiException::clear_exception()
{
	m_error_type=ERROR_TYPE_UNKOWN;
	m_mes=EMPTYSTRING;
}
VirtualWifiException::~VirtualWifiException(void)
{
}
