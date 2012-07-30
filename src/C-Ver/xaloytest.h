#ifndef XALOYTEST_H
#define XALOYTEST_H

#include <stddef.h>

#define	XL_EQUAL			0
#define	XL_NOT_EQUAL		1
#define	XL_LESS				2
#define	XL_GREATER			3
#define	XL_LESS_EQUAL		4
#define	XL_GREATER_EQUAL	5

typedef void (*xl_function)();

namespace xaloy	
{	
	class XaloyTester
	{
	public:
		// assert and expect test
		template<typename T>
		static bool Assert(int cmpType, const T &actual, const T &expect);		
		template<typename T>
		static bool Expect(int cmpType, const T &actual, const T &expect);
		static bool Assert(int cmpType, const char *actual, const char *expect);		
		static bool Expect(int cmpType, const char *actual, const char *expect);
		static bool Assert(int cmpType, const wchar_t *actual, const wchar_t *expect);		
		static bool Expect(int cmpType, const wchar_t *actual, const wchar_t *expect);	
		
		static bool Assert_bytes(int cmpType, const char *actual, size_t sz_1, const char *expect, size_t sz_2);		
		static bool Expect_bytes(int cmpType, const char *actual, size_t sz_1, const char *expect, size_t sz_2);
		
		// performance test
		static void Performance(xl_function f, int cycle, int &millisecond, int &space);
	};
}

#endif