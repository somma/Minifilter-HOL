/**
 * @file    Kernel mode logging module.
 * @brief	Window Vista 이후 버전에서는 메세지 출력이 보이지 않음. 
 *			아래명령으로 메세지 필터링 마스크를 조정해야 보임
 * 
 *			kd> ed nt!Kd_IHVDRIVER_Mask 0xff 
 * @ref     
 * @author  Yonhgwhan, Roh (fixbrain@gmail.com)
 * @date    2010/11/10 created.
 * @copyright All rights reserved by Yonghwan, Roh.
**/
#include "dbg_msg.h"
#include "../inc/hol.h"


#define		NT_PROCNAMELEN		16
static ULONG _process_name_offset = 0x00000000;




#if DBG

// debug level and debug area mask
//
ULONG g_DebugLevel = /*DPFLTR_TRACE_LEVEL*/DPFLTR_INFO_LEVEL;

// Buffers for debug messages are allocated globally instead of 
// on a stack, therefore we need g_DebugBufferBusy flags to 
// protect access to them.
//
ULONG g_DebugBufferBusy[] = {0, 0, 0, 0, 0, 0, 0, 0};
CHAR  g_DebugBuffer[NUMBER_DEBUG_BUFFERS][1024];


/**	-----------------------------------------------------------------------
	\brief	debug message output routine

	\param	
		IN  level
				Debug level (DBG_ERR, DBG_INFO, etc..)
				
		IN  format
				Debug Message format

	\return			
		NONE
	\code	
	\endcode		
-------------------------------------------------------------------------*/
VOID drv_debug_print(IN UINT32 level, IN const char* function,IN const char* format, IN ...)
{
    ULONG i;
    va_list vaList;
    va_start(vaList, format);

	CHAR ProcName[NT_PROCNAMELEN] = { 0 };

    // check mask for debug area and debug level
	//
    if (level <= g_DebugLevel)
    {
        // find a free buffer
		//
        for (i = 0; i < NUMBER_DEBUG_BUFFERS; ++i)
        {
            if (InterlockedCompareExchange((LONG*)&g_DebugBufferBusy[i], 1, 0) == 0)
            {
                __try
				{
					if (TRUE != NT_SUCCESS( RtlStringCbVPrintfA(
										            g_DebugBuffer[i], 
										            sizeof(g_DebugBuffer[i]),
										            format,
										            vaList
										            )))
					{
						return;
					}
				}
				__except(EXCEPTION_EXECUTE_HANDLER)
				{
                    return;
				}

				// get process name 
				get_process_name(PsGetCurrentProcess(), ProcName);
								
                if (DPFLTR_ERROR_LEVEL == level)
                {
                    DbgPrintEx(
						DPFLTR_IHVDRIVER_ID, 
						DPFLTR_ERROR_LEVEL, 
						holFilter"(IRQL %2.2d): %-16s(%04u:%04u): [ERR ] %s(), %s\n",
                        KeGetCurrentIrql(), 
						ProcName, PsGetCurrentProcessId(), PsGetCurrentThreadId(),
						function, 
                        g_DebugBuffer[i]
                        ); 
                }
                else if (DPFLTR_WARNING_LEVEL == level)
                {
                    DbgPrintEx(
						DPFLTR_IHVDRIVER_ID, 
						DPFLTR_WARNING_LEVEL | DPFLTR_MASK,
						holFilter"(IRQL %2.2d): %-16s(%04u:%04u): [WARN] %s(), %s\n",
                        KeGetCurrentIrql(), 
						ProcName, PsGetCurrentProcessId(), PsGetCurrentThreadId(),
						function,                         
                        g_DebugBuffer[i]
                    );
                }
				else if (DPFLTR_TRACE_LEVEL == level)
				{
					DbgPrintEx(
						DPFLTR_IHVDRIVER_ID, 
						DPFLTR_TRACE_LEVEL | DPFLTR_MASK,
						holFilter"(IRQL %2.2d): %-16s(%04u:%04u): [TRCE] %s(), %s\n",
						KeGetCurrentIrql(), 
						ProcName, PsGetCurrentProcessId(), PsGetCurrentThreadId(),
						function,                         
						g_DebugBuffer[i]
					);					
				}
                else
                {
                    DbgPrintEx(
						DPFLTR_IHVDRIVER_ID, 
						DPFLTR_INFO_LEVEL |  DPFLTR_MASK, 
						holFilter"(IRQL %2.2d): %-16s(%04u:%04u): [INFO] %s(), %s\n",
                        KeGetCurrentIrql(), 
						ProcName, PsGetCurrentProcessId(), PsGetCurrentThreadId(),
						function,                         
                        g_DebugBuffer[i]
                        );
                }

                InterlockedExchange((LONG*)&g_DebugBufferBusy[i], 0);
                break;
            }
        }
    }

    va_end(vaList);
}

#endif	// DBG


/// @brief	현재 프로세스가 "System" 이라는 가정하에 EPROCESS::ImageFileName 필드의 offset 을 찾는다. 
///			반드시 DriverEntry 함수에서 호출되어야 함 (System process context 에서 실행)
BOOLEAN
SetProcessNameOffset(
	)
{	
	//
	// 현재 process가 SYSTEM process란 가정하에 SYSTEM이란 문자열을 찾는다.
	//

	PEPROCESS curproc = PsGetCurrentProcess();
	for (int i = 0; i < 3 * PAGE_SIZE; i++)
	{
		if (!_strnicmp("system", (PCHAR)curproc + i, strlen("system")))
		{
			_process_name_offset = i;
			return TRUE;
		}
	}

	//
	// Name not found - oh, well
	//
	return FALSE;
}

/// @brief	EPROCESS 에서 image name 을 찾아 리턴한다.
const 
char* 
get_process_name(
	_In_ PEPROCESS eprocess, 
	_Out_ char* NameCopy
	)
{
	PEPROCESS curproc = NULL;
	char *nameptr = NULL;

	//
	// We only try and get the name if we located the name offset
	//
	if (0 != _process_name_offset)
	{
		//
		// Get a pointer to the current process block
		//
		curproc = eprocess;

		//
		// Dig into it to extract the name. Make sure to leave enough room
		// in the buffer for the appended process ID.
		//
		nameptr = (PCHAR)curproc + _process_name_offset;
		strncpy(NameCopy, nameptr, NT_PROCNAMELEN - 1);
		NameCopy[NT_PROCNAMELEN - 1] = 0;
		///!    sprintf( name + strlen(name), ":%d", (ULONG) PsGetCurrentProcessId());
	}
	else
	{
		strncpy(NameCopy, "???", NT_PROCNAMELEN - 1);
	}

	return NameCopy;
}