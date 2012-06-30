#include "xaloytools.h"

#ifdef __WIN32
#include <windows.h>
#endif

#define LOG_PATH "log/"
#define HTML_PATH "log/html/"

static void
message(char *msg)	{
	#ifdef __WIN32
	#else
	#endif
	printf("%s\n", msg);
}

static void
debug(char *msg)	{
	#ifdef __WIN32
	#else
	#endif
	printf("%s\n", msg);
}

static void
error(char *msg)	{
	#ifdef __WIN32
	#else
	#endif
	printf("%s\n", msg);
}

static void
ok(char *msg)	{
	#ifdef __WIN32
	#else
	#endif
	printf("%s\n", msg);
}

static void
print(char *msg)	{
	printf(msg);
}

static void
printline(char *msg)	{
	xprint(msg);
	printf("\n");
}

static int 
checkfile(char *path, char *name)	{
	return 1;
}