#include "xaloytools.h"
#include <stdio.h>
#include <time.h>

#ifdef __WIN32
#include <windows.h>
#endif

/*		macro declaration		*/
#define LOG_PATH "log/"
#define HTML_PATH "log/html/"

enum PRINT_COLOR{
	COLOR_GREEN = 10,
	COLOR_BLUE = 11,
	COLOR_RED = 12,
	COLOR_YELLOW = 14
};

/*		xaloytools helper		*/
static void 
print_color_text(int color, char *text)	{
#ifdef __WIN32
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
		printf("\033[33m%s\033[0m", text);
	case COLOR_GREEN:
		printf("\033[32m%s\033[0m", text);
	case COLOR_RED:
		printf("\033[31m%s\033[0m", text);
	case COLOR_YELLOW:
		printf("\033[34m%s\033[0m", text);
	default:
		return;
	}
#endif
}
/*		xaloytools' API		*/
void
message(char *msg)	{
	print_color_text(COLOR_BLUE, "[MESSAGE]  ");	
	printf("%s\n", msg);
}

void
debug(char *msg)	{
	print_color_text(COLOR_YELLOW, "[DEBUG]    ");
	printf("%s\n", msg);
}

void
error(char *msg)	{
	print_color_text(COLOR_RED, "[ERROR]    ");
	printf("%s\n", msg);
}

void
ok(char *msg)	{
	print_color_text(COLOR_GREEN, "[OK]       ");
	printf("%s\n", msg);
}

void
xprint(char *msg)	{
	printf(msg);
	printf("\n");
}