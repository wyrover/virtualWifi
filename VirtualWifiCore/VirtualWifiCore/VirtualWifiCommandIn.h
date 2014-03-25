#pragma once
#include "stdafx.h"

class VirtualWifiCommandIn:virtual public VirtualWifiCommandBase
{
public:
	typedef VirtualWifiCommandBase::VirtualWifiCommandStruct command_struct;
	typedef command_struct* p_command_struct;
protected:
	p_command_struct& m_pcommand_struct;
public:
	VirtualWifiCommandIn(void);
	~VirtualWifiCommandIn(void);
};

