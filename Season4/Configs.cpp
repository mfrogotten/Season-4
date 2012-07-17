
#include "StdAfx.h"
#include "Configs.h"

// Class of Configs
cConfigs Configs;	

// Function that taking all configs
void cConfigs::Init()
{

}

// Function that taking configs that used in Fixes
void cConfigs::LoadFixConfigs()
{
	// Yay!!! First config for CheckSum!
	Common.CheckSum = GetInt(0, 1, 1, "Common", "CheckSum", ConfigGS);
}

// Function that check numeric value from config
long cConfigs::GetInt(long Min, long Max, long Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FileName)
{
	// Value that we need to return
	long Result;

	// Checking for file, if not exist, setup default value
	WIN32_FIND_DATAA wfd;
	if (FindFirstFileA(FileName, &wfd) == INVALID_HANDLE_VALUE)
	{		
		// TODO: Message about failing loading file
		Result = Default;
	}
	// else taking config from file, if config not exist then taking value -100500 for message and default value 
	else
	{
		Result = GetPrivateProfileInt(BlockName, ConfigName, -100500, FileName);
	}

	// that's what i'm talking about in last comment
	if(Result == -100500)
	{	   
		// TODO: Message about failing loading config
		Result = Default;
	}

	// checking that config isn't out of range
	if(Result < Min || Result > Max)
	{
		// TODO: Message about config out of range
		Result = Default;
	} 
	return Result;
}