
#include "StdAfx.h"
#include "Console.h"

void MainTick()
{
	while (true)
	{
		Console.Tick();
		Sleep(100);
	}
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

		// Load Sonsole
		Console.Init();

		// Run main tick function that ticks every sec
		DWORD ThreadID;
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainTick, NULL, 0, &ThreadID);
	}
} 