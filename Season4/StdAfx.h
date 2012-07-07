
// for prevent of multiple definitions
#ifndef STDAFX_H
#define STDAFX_H

	// for faster compilation
	#define WIN32_LEAN_AND_MEAN

	// TEST:
	// for security which prevents buffer overruns
	// example: sprintf -> sprintf_s
	#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1


	// for some types of variables and other
	#include <Windows.h>
	//#include <WinDef.h>

	// for versions
	#include "Resource.h"

	// for GS and GSCS definitions
	#include "Prodef.h"


#endif