
#include "StdAfx.h"
#include "Utilits.h"

// Class of "Utilits"
cUtilits Utilits;

// Function for Hooking functions
void cUtilits::HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset)
{
	*(DWORD*)(dwJmpOffset + 1) = dwMyFuncOffset-(dwJmpOffset+5);
}

// Function for setting Nopes
void cUtilits::SetNop(DWORD dwOffset, int Size)
{
	for(int n=0; n < Size; n++)
		*(BYTE*)(dwOffset+n) = 0x90;
}

// Function for setting Return
void cUtilits::SetRetn(DWORD dwOffset)
{
	*(BYTE*)(dwOffset) = 0xC3;
}

// Function for setting Rreturn
void cUtilits::SetRRetn(DWORD dwOffset)
{
	*(BYTE*)(dwOffset)=0xC3;
	*(BYTE*)(dwOffset+1)=0x90;
	*(BYTE*)(dwOffset+2)=0x90;
	*(BYTE*)(dwOffset+3)=0x90;
	*(BYTE*)(dwOffset+4)=0x90;
}

// Function for setting Bytes
void cUtilits::SetByte(DWORD dwOffset, BYTE btValue)
{
	*(BYTE*)(dwOffset) = btValue;
}

// Function for setting Jmp
void cUtilits::SetJmp(DWORD dwOffset)
{
	*(BYTE*)(dwOffset)=0xE9;
}
