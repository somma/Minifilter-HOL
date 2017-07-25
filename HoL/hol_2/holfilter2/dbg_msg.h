/**
 * @file    Kernel mode logging module.
 * @brief	
 * @ref     
 * @author  Yonhgwhan, Roh (fixbrain@gmail.com)
 * @date    2010/11/10 created.
 * @copyright All rights reserved by Yonghwan, Roh.
**/

#ifndef _DRV_DEBUG_H_
#define _DRV_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include <ntifs.h>
#include <ntstrsafe.h>
#include <ntintsafe.h>


#define NUMBER_DEBUG_BUFFERS    (sizeof(g_DebugBufferBusy)/sizeof(g_DebugBufferBusy[0]))

/*
#if DBG && defined(_X86_)
#undef ASSERT
#define ASSERT(e) if(!(e)){DbgPrint("Assertion failure in "__FILE__ ", line %d: " #e "\n", __LINE__);DebugBreak();}
#endif
*/

#if DBG
    VOID drv_debug_print(IN UINT32 Level, IN const char* Function,IN const char* Format, IN ...);
#else
    __inline void drv_debug_print(IN UINT32 level, IN const char* function,IN const char* format, IN ...)
    {
        UNREFERENCED_PARAMETER(level);
        UNREFERENCED_PARAMETER(function);
	    UNREFERENCED_PARAMETER(format);
    }
#endif	// DBG

//VOID drv_debug_print(IN UINT32 Level, IN const char* Function,IN const char* Format, IN ...);

#define log_err     drv_debug_print(DPFLTR_ERROR_LEVEL, __FUNCTION__, 
#define log_warn    drv_debug_print(DPFLTR_WARNING_LEVEL, __FUNCTION__, 
#define log_trace   drv_debug_print(DPFLTR_TRACE_LEVEL, __FUNCTION__, 
#define log_info    drv_debug_print(DPFLTR_INFO_LEVEL, __FUNCTION__,
#define log_end     );


BOOLEAN
SetProcessNameOffset(	
	);

const 
char* 
get_process_name(
	_In_ PEPROCESS eprocess,
	_Out_ char* NameCopy
	);

#ifdef __cplusplus
}
#endif 


#endif//_DRV_DEBUG_H_