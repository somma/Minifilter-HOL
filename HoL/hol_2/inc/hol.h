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
//	holfilter
// 
#define		holFilter				"holfilter2.sys"
#define		holFilterw				L"holfilter2.sys"

#define		holFilterService		L"holfilter2"
#define		holFilterServiceDisplay	L"holfilter2 service"
#define		holFilterAltitude		L"0"
#define		holFilterFlag			0

#define		holFilterPort			L"\\holPort2"


//#pragma warning(pop)