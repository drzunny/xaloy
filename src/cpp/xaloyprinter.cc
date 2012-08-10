#include "xaloyprinter.h"
#include <stdio.h>
#ifdef OS_WIN32
#include <windows.h>
#endif

void 
print_color_text(int color, const char *text)	{
#ifdef OS_WIN32
	WORD colorOld;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(handle, (WORD)color);
	printf(text);
	SetConsoleTextAttribute(handle, colorOld);
#else
	switch(color)
	{
	case COLOR_BLUE:
		printf("\033[34m%s\033[0m", text);
		break;
	case COLOR_GREEN:
		printf("\033[32m%s\033[0m", text);
		break;
	case COLOR_RED:
		printf("\033[31m%s\033[0m", text);
		break;
	case COLOR_YELLOW:
		printf("\033[33m%s\033[0m", text);
		break;
	default:
		return;
	}
#endif
}