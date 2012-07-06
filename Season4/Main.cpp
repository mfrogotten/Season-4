// ================================================== //
// #			GameServer 1.00.90					# //
// #			Imagination Arts					# //
// #			Julia Project 1.1.x					# //
// ================================================== //
// #	http://imaginationarts.net/forum/			# //
// #	http://auroraplay.ru/						# //
// ================================================== //

#include "StdAfx.h"

// Main Function thats load GS
extern "C" __declspec (dllexport) void __cdecl Main()
{
	DWORD OldProtect;

	// Makes GS writable
	if(VirtualProtect(LPVOID(0x401000), GSSIZE, PAGE_EXECUTE_READWRITE, &OldProtect))
	{	
		// Something Would be There soon...
	}
} 