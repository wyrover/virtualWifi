#pragma once
#include "stdafx.h"

class VirtualWifiSocketEx:protected VirtualWifiSocket
{
private:
     SOCKET m_mainsocket;
private:
	void InitSocket();
public:
	VirtualWifiMainSocket();
	~VirtualWifiMainSocket();
};
