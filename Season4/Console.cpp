
#include "StdAfx.h"
#include "Console.h"

// Class of Console
cConsole Console;

int i;
// Tick of Console
void cConsole::Tick()
{
	// Change info of boxes
	ChangeTop();
	ChangeBottom();

	OutputMsg("Test", "MaximumTest %d", i++);
	// Display Console
	SetUpBoxes();
}

// Initialize of Console
void cConsole::Init()
{
	i=0;
	// Create console
	AllocConsole();

	// Getting Handle output of Console
	Output.Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Creating other handles for parts in Console
	Top.Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	Left.Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	Right.Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	Bottom.Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// Clear Cursor from Console
	//CONSOLE_CURSOR_INFO CursInfo;
	//CursInfo.bVisible = FALSE;
	//SetConsoleCursorInfo(Top.Handle, &CursInfo);
	//SetConsoleCursorInfo(Output.Handle, &CursInfo);
}

void cConsole::SetUpBoxes()
{
	// Taking information about console, especially size
	CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo2;
	if (GetConsoleScreenBufferInfo(Output.Handle, &lpConsoleScreenBufferInfo2))
	{
		// Calculating height of Console
		int Height = lpConsoleScreenBufferInfo2.srWindow.Bottom - lpConsoleScreenBufferInfo2.srWindow.Top + 1;

		// 2x80
		Top.WriteBox.Top = 0;
		Top.WriteBox.Left = 0;
		Top.WriteBox.Right = 79;
		Top.WriteBox.Bottom = 1;
		Top.ReadBox.Top = 0;
		Top.ReadBox.Left = 0;
		Top.ReadBox.Right = 79;
		Top.ReadBox.Bottom = 1;
		Top.BufSize.X = 80;
		Top.BufSize.Y = 2;
		Top.BufCoord.X = 0;
		Top.BufCoord.Y = 0;

		// ?-4x27
		Left.WriteBox.Top = 2;
		Left.WriteBox.Left = 0;
		Left.WriteBox.Right = 26;
		Left.WriteBox.Bottom = Height-3;
		Left.ReadBox.Top = 0;
		Left.ReadBox.Left = 0;
		Left.ReadBox.Right = 26;
		Left.ReadBox.Bottom = Height-5;
		Left.BufSize.X = 27;
		Left.BufSize.Y = Height-4;
		Left.BufCoord.X = 0;
		Left.BufCoord.Y = 0;
		SetConsoleScreenBufferSize(Left.Handle, Left.BufSize);
		SetConsoleWindowInfo(Left.Handle, TRUE, &Left.ReadBox);

		// ?-4x53
		Right.WriteBox.Top = 2;
		Right.WriteBox.Left = 27;
		Right.WriteBox.Right = 79;
		Right.WriteBox.Bottom = Height-3;
		Right.ReadBox.Top = 0;
		Right.ReadBox.Left = 0;
		Right.ReadBox.Right = 52;
		Right.ReadBox.Bottom = Height-5;
		Right.BufSize.X = 53;
		Right.BufSize.Y = Height-4;
		Right.BufCoord.X = 0;
		Right.BufCoord.Y = 0;
		SetConsoleScreenBufferSize(Right.Handle, Right.BufSize);
		SetConsoleWindowInfo(Right.Handle, TRUE, &Right.ReadBox);

		// 2x80
		Bottom.WriteBox.Top = Height-2;
		Bottom.WriteBox.Left = 0;
		Bottom.WriteBox.Right = 79;
		Bottom.WriteBox.Bottom = Height-1;
		Bottom.ReadBox.Top = 0;
		Bottom.ReadBox.Left = 0;
		Bottom.ReadBox.Right = 79;
		Bottom.ReadBox.Bottom = 1;
		Bottom.BufSize.X = 80;
		Bottom.BufSize.Y = 2;
		Bottom.BufCoord.X = 0;
		Bottom.BufCoord.Y = 0;
		
		// Reading from boxes
		ReadConsoleOutput(Top.Handle, Top.Buffer, Top.BufSize, Top.BufCoord, &Top.ReadBox);
		ReadConsoleOutput(Left.Handle, Left.Buffer, Left.BufSize, Left.BufCoord, &Left.ReadBox);
		ReadConsoleOutput(Right.Handle, Right.Buffer, Right.BufSize, Right.BufCoord, &Right.ReadBox);
		ReadConsoleOutput(Bottom.Handle, Bottom.Buffer, Bottom.BufSize, Bottom.BufCoord, &Bottom.ReadBox);

		// Writing in main Console
		WriteConsoleOutput(Output.Handle, Top.Buffer, Top.BufSize, Top.BufCoord, &Top.WriteBox);
		WriteConsoleOutput(Output.Handle, Left.Buffer, Left.BufSize, Left.BufCoord, &Left.WriteBox);
		WriteConsoleOutput(Output.Handle, Right.Buffer, Right.BufSize, Right.BufCoord, &Right.WriteBox);
		WriteConsoleOutput(Output.Handle, Bottom.Buffer, Bottom.BufSize, Bottom.BufCoord, &Bottom.WriteBox);
	}
}

void cConsole::ChangeTop()
{
	char outputmsg[100];
	DWORD dwBytesWritten;

	sprintf(outputmsg, "Online [%d/200]             Name of Server               some other good info\n",i++);
	COORD ConsolePos;
	ConsolePos.X = 0;
	ConsolePos.Y = 0;
	SetConsoleCursorPosition(Top.Handle, ConsolePos);
	WriteFile(Top.Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
	sprintf(outputmsg, "--------------------------------------------------------------------------------");
	WriteFile(Top.Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
}

void cConsole::ChangeBottom()
{
	char outputmsg[100];
	DWORD dwBytesWritten;

	COORD ConsolePos;
	ConsolePos.X = 0;
	ConsolePos.Y = 0;
	SetConsoleCursorPosition(Bottom.Handle, ConsolePos);
	sprintf(outputmsg, "--------------------------------------------------------------------------------");
	WriteFile(Bottom.Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
	sprintf(outputmsg, "/> : ");
	WriteFile(Bottom.Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
}

void cConsole::OutputMsg( const char* Title, const char* Format, ... )
{
	char outputLeft[50], outputRight[80], currdate[11], FormatedMessage[80];
	DWORD dwBytesWritten;

	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(FormatedMessage, Format, pArguments);
	//CheckProcent(Message); // "%" Bug Fix 
	va_end(pArguments);

	SYSTEMTIME t;
	GetLocalTime(&t);
	sprintf(currdate, " %02d:%02d:%02d ", t.wHour, t.wMinute, t.wSecond);
	sprintf(outputLeft,"%s | %s\n", currdate, Title);
	sprintf(outputRight,"| %s\n",FormatedMessage);

	WriteFile(Left.Handle, outputLeft, strlen(outputLeft), &dwBytesWritten, NULL);
	WriteFile(Right.Handle, outputRight, strlen(outputRight), &dwBytesWritten, NULL);
}
