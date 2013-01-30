/*=============================================================================
#     FileName: printer.cc
#         Desc: the implement of printer
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-28 14:23:38
#      History:
=============================================================================*/

#include "printer.h"

#include <cstddef>
#include <cassert>
#include <cstdio>

#ifdef XALOY_PLATFORM_WINDOWS
#   include <windows.h>
#endif

using namespace xaloy;

void XaloyBasePrinter::print(const char *msg, int fColor, int bColor)   
{
#ifdef XALOY_PLATFORM_WINDOWS
    /*  color printing on windows */
    WORD colorOld;
    HANDLE handle;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    int realColor = 0;
    if( fColor == F_ORIGINAL && bColor == B_ORIGINAL )
        printf(msg);
    else    {
        /*   if one of the fColor and bColor is not ORIGIN, then fColor defaut is WHITE   */
        if(fColor == F_ORIGINAL)
            realColor = realColor | F_WHITE;
        else
            realColor = realColor | fColor;

        if(bColor != B_ORIGINAL)
            realColor = realColor | bColor;
    	handle = GetStdHandle(STD_OUTPUT_HANDLE);    	
    	GetConsoleScreenBufferInfo(handle, &csbi);
    	colorOld = csbi.wAttributes;
    	SetConsoleTextAttribute(handle, (WORD)realColor);
    	printf(msg);
	    SetConsoleTextAttribute(handle, colorOld);
    }
#else
    /*  color printing on linux  */
    int realColor = 0;
    assert(msg != NULL);
    if( fColor == F_ORIGINAL && bColor == B_ORIGINAL )
        printf(msg);
    else    {
        if(fColor != F_ORIGINAL && bColor != B_ORIGINAL)    {
            printf("\033[%d;%dm%s\033[0m", fColor, bColor, msg);
        }   else    {
            if(fColor != F_ORIGINAL)
                realColor = fColor;
            else
                realColor = bColor;
            printf("\033[%dm%s\033[0m", realColor, msg);
        }
    }
#endif
}
