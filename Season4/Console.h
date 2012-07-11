
#ifndef CONSOLE_H
#define CONSOLE_H

class cConsole
{
public:
	void Init();
	void Tick();
	void SetUpBoxes();

	void ChangeTop();
	void ChangeBottom();

	void OutputMsg(const char* Title, const char* Format, ...);

	struct sOutput 
	{
		SMALL_RECT WriteBox;
		SMALL_RECT ReadBox;
		COORD BufCoord;
		COORD BufSize;
		HANDLE Handle;
	} Output;

	struct sLines : public sOutput
	{
		CHAR_INFO Buffer[160];		// [2][80];
	} Top, Bottom;

	struct sLeft : public sOutput
	{
		CHAR_INFO Buffer[2050];		// [75][27];
	} Left;

	struct sRight : public sOutput
	{
		CHAR_INFO Buffer[4000];		// [75][53];
	} Right;
};
extern cConsole Console;
#endif