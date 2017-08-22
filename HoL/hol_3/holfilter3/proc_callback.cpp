/**
 * @file    Minifilter driver dev HOL.
 * @author  somma (fixbrain@gmail.com)
 * @date    2017/08/22 created.
 * @copyright All rights reserved by somma.
**/
#include "proc_callback.h"


/// @brief	Start process monitor
NTSTATUS 
StartProcessCallback(
	)
{
	PAGED_CODE();	
	
	//
	//	Register process creation callback.
	// 
	NTSTATUS status = PsSetCreateProcessNotifyRoutineEx(CreateProcessNotifyRoutineEx,
														FALSE);
	if (!NT_SUCCESS(status))
	{
		log_err "PsSetCreateProcessNotifyRoutineEx() failed. status=0x%08x",
			status
			log_end;
		return status;
	}

	log_info "Process callback registered." log_end;
	return status;
}


///	@brief	Stop process monitor
void 
StopProcessCallback(
	)
{
	PAGED_CODE();
	
	//
	//	Unregister process creation callback
	// 
	NTSTATUS status = PsSetCreateProcessNotifyRoutineEx(CreateProcessNotifyRoutineEx,
														TRUE);
	if (!NT_SUCCESS(status))
	{
		log_err "PsSetCreateProcessNotifyRoutineEx() failed. status=0x%08x",
			status
			log_end;			
	}
	else
	{
		log_info "Process callback unregistered." log_end;
	}
}

/// @brief	Process create or delete callback.
VOID
CreateProcessNotifyRoutineEx(
	_Inout_ PEPROCESS Process,
	_In_ HANDLE ProcessId,
	_Inout_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
	)
{
	PAGED_CODE();

	UNREFERENCED_PARAMETER(Process);

	if (NULL == CreateInfo)
	{
		// 
		//	Process is exiting.
		// 
		log_info "process exiting. pid=%u", ProcessId log_end;
	}
	else
	{	
		//
		//	hol-todo
		//
		//UNICODE_STRING calc;
		//RtlInitUnicodeString(&calc, L"notepad.exe");
		//if (true == equal_tail_unicode_string(const_cast<PUNICODE_STRING>(CreateInfo->ImageFileName),
		//									  &calc, true))
		//{
		//	// hol-todo
		//	//CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
		//	//CreateInfo->CreationStatus = STATUS_OBJECT_NAME_INVALID;
		//	log_info "block process creating. ppid=%u, creator=%u, pid=%u, image=%wZ",
		//		CreateInfo->ParentProcessId,
		//		CreateInfo->CreatingThreadId.UniqueProcess,
		//		ProcessId,
		//		CreateInfo->ImageFileName
		//		log_end;
		//}
		//else
		//{

		//	//
		//	//	Process is creating.
		//	// 
		//	log_info "process creating. ppid=%u, creator=%u, pid=%u, image=%wZ",
		//		CreateInfo->ParentProcessId,
		//		CreateInfo->CreatingThreadId.UniqueProcess,
		//		ProcessId,
		//		CreateInfo->ImageFileName
		//		log_end;
		//}
		log_info "process creating. ppid=%u, creator=%u, pid=%u, image=%wZ",
			CreateInfo->ParentProcessId,
			CreateInfo->CreatingThreadId.UniqueProcess,
			ProcessId,
			CreateInfo->ImageFileName
			log_end;

	}
}
