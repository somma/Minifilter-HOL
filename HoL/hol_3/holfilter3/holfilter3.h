/**
 * @file    Minifilter driver dev HOL.
 * @author  somma (fixbrain@gmail.com)
 * @date    2017/01/25 created.
 * @copyright All rights reserved by somma.
**/
#pragma once

#include "pch.h"

typedef struct _GLOBAL_DATA
{
	///  The object that identifies this driver.
	PDRIVER_OBJECT DriverObject;

	///  The filter handle that results from a call to
	///  FltRegisterFilter.
	PFLT_FILTER Filter;

	
} GLOBAL_DATA, *PGLOBAL_DATA;

extern GLOBAL_DATA global;
