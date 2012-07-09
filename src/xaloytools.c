#include <stdio.h>
#include <time.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#ifdef OS_WIN32
#include <windows.h>
#define XTOOLS_API LUALIB_API __declspec(dllexport)
#else
#define XTOOLS_API
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
static int
message(lua_State *L)	{
	const char *msg = luaL_checkstring(L, 1);
	print_color_text(COLOR_BLUE, "[MESSAGE]  ");	
	printf("%s\n", msg);
	return 0;
}

static int 
debug(lua_State *L)	{
	const char *msg = luaL_checkstring(L, 1);
	print_color_text(COLOR_YELLOW, "[DEBUG]    ");
	printf("%s\n", msg);
	return 0;
}

static int
fail(lua_State *L)	{
	const char *msg = luaL_checkstring(L, 1);
	print_color_text(COLOR_RED, "[FAIL]     ");
	printf("%s\n", msg);
	return 0;
}

static int
ok(lua_State *L)	{
	const char *msg = luaL_checkstring(L, 1);
	print_color_text(COLOR_GREEN, "[OK]       ");
	printf("%s\n", msg);
	return 0;
}

static int
xprint(lua_State *L)	{
	const char *msg = luaL_checkstring(L, 1);
	printf(msg);
	printf("\n");
	return 0;
}

/*		register into lua		*/
static const 
struct luaL_Reg xtools[] = {
	{"message", message},
	{"ok", ok},
	{"fail", fail},
	{"debug", debug},
	{"xprint", xprint},
	{NULL, NULL}
};

XTOOLS_API int
luaopen_xtools(lua_State *L)	{
	lua_register(L, "message", message);
	lua_register(L, "ok", ok);
	lua_register(L, "fail", fail);
	lua_register(L, "debug", debug);
	lua_register(L, "xprint", xprint);
	
	return 1;
}