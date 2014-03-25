#pragma once

#ifndef WINVER                          // 指定要求的最低平台是 Windows Vista。  
//#define WINVER 0x0600           // 将此值更改为相应的值，以适用于 Windows 的其他版本。  
#define WINVER 0x0501   
#endif  
#ifndef _WIN32_WINNT            // 指定要求的最低平台是 Windows Vista。  
//#define _WIN32_WINNT 0x0600     // 将此值更改为相应的值，以适用于 Windows 的其他版本。  
#define WINVER 0x0501   
#endif 
#include <SDKDDKVer.h>