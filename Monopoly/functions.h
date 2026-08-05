#pragma once
#include<iostream>
#include"player.h"
#include"Property.h"

#ifdef _WIN32
#include<windows.h>
inline void windowSize()
{
	HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sizeOfBuff;
	sizeOfBuff.X = 1600;
	sizeOfBuff.Y = 900;
	SetConsoleScreenBufferSize(buff, sizeOfBuff);

	RECT r;
	//Find the Console Window
	HWND console = GetConsoleWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(console, &r);
	int width = 1600;
	int height = 900;
	MoveWindow(console, r.left, r.top, width, height, TRUE);

}
#else
inline void windowSize()
{
	//No-op: console window resizing is a Windows-only API
}
#endif

//Clears the console screen on any platform
inline void clearScreen()
{
#ifdef _WIN32
	system("CLS");
#else
	system("clear");
#endif
}

//Waits for a keypress before continuing, like Windows' "pause" command
inline void pauseConsole()
{
#ifdef _WIN32
	system("pause");
#else
	system("read -n 1 -s -p \"Press any key to continue . . .\"");
	std::cout << std::endl;
#endif
}







