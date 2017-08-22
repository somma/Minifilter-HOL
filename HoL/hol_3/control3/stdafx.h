/**
 * @file    Minifilter driver dev HOL.
 * @author  somma (fixbrain@gmail.com)
 * @date    2017/01/25 created.
 * @copyright All rights reserved by somma.
**/
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//
// std
//
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

// 
// boost
//
#define BOOST_LIB_DIAGNOSTIC
#include "boost/lexical_cast.hpp"
#include "boost/type_traits.hpp"		// boost::remove_pointer
#include "boost/noncopyable.hpp"
#include "boost/format.hpp"
#include "boost/thread.hpp"
#include "boost/shared_ptr.hpp"

//
// windows headers
//

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include <Windows.h>
#include <VersionHelpers.h>
#include <crtdbg.h>
#include <stdint.h>
#include <strsafe.h>
#include <winioctl.h>
#include <dontuse.h>

#include <conio.h>
#include <winioctl.h>
//#include <winnt.h>

#include <fltuser.h>
#pragma comment(lib, "FltLib.lib")


//
// _my_lib
// 
#include "log.h"
#include "Win32Utils.h"

#define STATUS_SUCCESS                   ((NTSTATUS)0x00000000L)    // ntsubauth
#define STATUS_UNSUCCESSFUL              ((NTSTATUS)0xC0000001L)


