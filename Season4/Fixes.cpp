
#include "StdAfx.h"
#include "Utilits.h"
#include "Configs.h"

DWORD Exc;	// for exc option in Shop

// Hook to place where we receive OPT3
__declspec(naked) void ExcShop()
{
	Exc = 0;
	_asm
	{
		// We hook into place where receive OPT3 and it erased 
		// so we need to do it again, and insert into variable in GS
		//
		// GetToken - function that receive something to GetNumber
		// GetNumber - variable with number from file

		MOV EDI,GetNumber						// taking offset of GetNumber to EDI
			CALL EDI							// calling for variable on offset that in EDI
			MOV DWORD PTR SS:[EBP-0xBC],EAX		// copying it to shop structure, op3 variable
			LEA ECX,DWORD PTR SS:[EBP-0x9C]		// copying offset of some variable to ECX (dunno why)

		MOV EDI,GetToken						// taking offset of GetToken function to EDI
			CALL EDI							// calling for result of it
			MOV DWORD PTR SS:[EBP-0xA0],EAX		// copying it to Token (some temp variable)
			LEA ECX,DWORD PTR SS:[EBP-0x9C]		// copying offset of some variable to ECX

		MOV EDI,GetNumber						// taking offset of GetNumber to EDI
			CALL EDI							// again calling it, but for Exc option now
			MOV Exc,EAX							// copying it to our variable that would be used in Inserting Item

			MOV EDI,ShopExcellentMod_Exit1		// taking offset of next command
			JMP EDI								// quiting to it
	}
}

__declspec(naked) void ExcShopAdd()
{
	_asm
	{
		// This function hooks in sending arguments to function Convert in inserting item to shop
		// Hook erase 5 bytes of code, so after pushing exc option, we need to copy variable of opt3

		PUSH Exc								// pushing exc option insteed of 0
			MOV AL,BYTE PTR SS:[EBP+0x20]		// copying in AL opt3

		MOV EDI,ShopExcellentMod_Exit2			// copying offset of next command
			JMP EDI								// quiting to it
	}
}

// Fixes of GS
void Fixes()
{
	// GameServer fixes
#ifdef _GS
	// GameGuard off
	Utilits.SetNop(0x00573763,5);		// ggauth.dll Unload
	Utilits.SetByte(0x00573778,0xEB);	//

	// Reading exc option from shop.txt
	Utilits.HookThis((DWORD)&ExcShop, ShopExcellentMod_Hook1);
	Utilits.SetJmp(ShopExcellentMod_Hook1);

	// Insert item to shop after reading it
	Utilits.HookThis((DWORD)&ExcShopAdd, ShopExcellentMod_Hook2);
	Utilits.SetJmp(ShopExcellentMod_Hook2);

	// AiElement check fix
	Utilits.SetByte(0x005B7CDC,0xFF);

	// CheckSum
	if (Configs.Common.CheckSum)
		Utilits.SetByte(0x0043BA64, 0x74);// je 
	else
		Utilits.SetByte(0x0043BA64, 0xEB);// jmp
#endif

	// GameServerCS fixes
#ifdef _GS_CS
#endif
}
