/**
 * @file    Minifilter driver dev HOL.
 * @author  somma (fixbrain@gmail.com)
 * @date    2017/01/25 created.
 * @copyright All rights reserved by somma.
**/
#include "stdafx.h"

#include "../inc/hol.h"
#include "scm_context.h"


int real_main()
{
	//
	//	scm_context 객체 생성
	// 
	std::wstringstream driver_path;
	driver_path
		<< get_current_module_dirEx()
		<< L"\\"
		<< holFilterw;

	scm_context scm(driver_path.str().c_str(),
					holFilterService,
					holFilterServiceDisplay,
					holFilterAltitude,
					holFilterFlag,
					false);

	//
	//	holFilter 서비스 설치 
	// 
	if (true != scm.install_service(false))
	{
		log_err "scm.install_service() failed." log_end;
		return -1;
	}
	log_info "%ws installed.", holFilterService log_end;

	//
	//	holFilter 서비스 시작
	// 
	if (true != scm.start_service())
	{
		log_err "scm.start_service() failed. " log_end;
		return -1;
	}
	log_info "%ws started.", holFilterService log_end;
	log_info "Press any key to stop..." log_end;
	_pause;

	//
	//	holFilter 서비스 종료
	// 
	if (true != scm.stop_service())
	{
		log_err "scm.stop_service() failed. " log_end;
		return -1;
	}
	log_info "%ws stopped.", holFilterService log_end;

	//
	//	holFilter 서비스 제거 
	// 
	if (true != scm.uninstall_service())
	{
		log_err "scm.uninstall_service() failed. " log_end;
		return -1;
	}
	log_info "%ws uninstalled.", holFilterService log_end;
	return 0;
}

/// @brief	Entry point
int main()
{
	initialize_log(log_mask_all, log_level_debug, log_to_all, L"c:\\dbg\\control-2.log");
	log_info
		"\n===============================================================================\n"\
		"Compiled at %s on %s \n"\
		"===============================================================================\n",
		__TIME__, __DATE__
		log_end;
	int ret = real_main();
	finalize_log();

	return ret;
}

