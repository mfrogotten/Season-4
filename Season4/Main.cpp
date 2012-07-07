
#include "StdAfx.h"
#include "Utilits.h"

// Fixes of GS
void Fixes()
{
	// GameServer fixes
#ifdef _GS
	// GameGuard off
	Utilits.SetNop(0x00573763,5);		// ggauth.dll Unload
	Utilits.SetByte(0x00573778,0xEB);	//
#endif

	// GameServerCS fixes
#ifdef _GS_CS
#endif
}

// Main Function thats load GS
extern "C" __declspec (dllexport) void __cdecl Main()
{
	DWORD OldProtect;

	// Makes GS writable
	if(VirtualProtect(LPVOID(0x401000), GSSIZE, PAGE_EXECUTE_READWRITE, &OldProtect))
	{	
		// Do Some Fixes
		Fixes();
	}
} 