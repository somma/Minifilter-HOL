/**
 * @file    Minifilter driver dev HOL.
 * @author  somma (fixbrain@gmail.com)
 * @date    2017/01/25 created.
 * @copyright All rights reserved by somma.
**/
#pragma once

/// offsetof() macro
#include <stddef.h>	

//#pragma warning(push)
//#pragma warning(disable:4201)

//
//	holfilter 미니필터 관련 상수 정의 
// 
#define		holFilter				"holfilter.sys"
#define		holFilterw				L"holfilter.sys"

#define		holFilterService		L"holfilter"
#define		holFilterServiceDisplay	L"holfilter service"
#define		holFilterAltitude		L"0"
#define		holFilterFlag			0

#define		holFilterPort			L"\\holPort"


//#pragma warning(pop)