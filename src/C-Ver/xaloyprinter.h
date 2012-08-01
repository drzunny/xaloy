#ifndef XALOYPRINTER_H
#define XALOYPRINTER_H

enum PRINT_COLOR{
	COLOR_GREEN = 10,
	COLOR_BLUE = 11,
	COLOR_RED = 12,
	COLOR_YELLOW = 14
};

void print_color_text(int color, const char *text);

#endif