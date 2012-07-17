
#ifndef CONFIGS_H
#define CONFIGS_H

class cConfigs
{
public:
	void Init();
	void LoadFixConfigs();

	long GetInt(long Min, long Max, long Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FileName);
	
	// Common configs
	struct sCommon
	{
		int CheckSum;
	} Common;
};
extern cConfigs Configs;

#endif