/**
 * @file    Minifilter driver dev HOL.
 * @author  somma (fixbrain@gmail.com)
 * @date    2017/08/22 created.
 * @copyright All rights reserved by somma.
**/

#pragma once
#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>
#include "dbg_msg.h"



NTSTATUS StartProcessCallback();
void StopProcessCallback();


VOID
CreateProcessNotifyRoutineEx(
	_Inout_ PEPROCESS Process,
	_In_ HANDLE ProcessId,
	_Inout_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
	);
