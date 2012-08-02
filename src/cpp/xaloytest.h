#ifndef XALOYTEST_H
#define XALOYTEST_H

#include <stddef.h>

#define	XL_EQUAL			0
#define	XL_NOT_EQUAL		1
#define	XL_LESS				2
#define	XL_GREATER			3
#define	XL_LESS_EQUAL		4
#define	XL_GREATER_EQUAL	5

#define DEFINE_XALOY_FUNCTION(fname)	static void (fname)()

typedef void (*xl_function)();
typedef char* xl_message;
typedef wchar_t* xl_umessage;

namespace xaloy	
{	
	class XaloyTester
	{
	private:
		// helper functions for compare the values
		template<typename T>
		static bool _compare(int cmpType, xl_message *msg, const T &actual, const T &expect);
		static bool _compare_str(int cmpType, xl_message *msg, const xl_message actual, const xl_message expect);
		static bool _compare_str(int cmpType, xl_message *msg, const xl_umessage actual, const xl_umessage expect);
		static bool _compare_byte(int cmpType, char **msg, const char *actual, size_t act_sz, const char *expect, size_t exp_sz);
		
	public:
		// assert and expect test
		static void Assert(int cmpType, const int &actual, const int &expect);		
		static bool Expect(int cmpType, const int &actual, const int &expect);
		static void Assert(int cmpType, const long &actual, const long &expect);		
		static bool Expect(int cmpType, const long &actual, const long &expect);
		static void Assert(int cmpType, const short &actual, const short &expect);		
		static bool Expect(int cmpType, const short &actual, const short &expect);
		static void Assert(int cmpType, const char &actual, const char &expect);		
		static bool Expect(int cmpType, const char &actual, const char &expect);
		static void Assert(int cmpType, const float &actual, const float &expect);		
		static bool Expect(int cmpType, const float &actual, const float &expect);
		static void Assert(int cmpType, const double &actual, const double &expect);		
		static bool Expect(int cmpType, const double &actual, const double &expect);
		
		static void Assert_str(int cmpType, const xl_message actual, const xl_message expect);		
		static bool Expect_str(int cmpType, const xl_message actual, const xl_message expect);
		static void Assert_str(int cmpType, const xl_umessage actual, const xl_umessage expect);		
		static bool Expect_str(int cmpType, const xl_umessage actual, const xl_umessage expect);	
		
		static void Assert_bytes(int cmpType, const char *actual, size_t act_sz, const char *expect, size_t exp_sz);		
		static bool Expect_bytes(int cmpType, const char *actual, size_t act_sz, const char *expect, size_t exp_sz);
		
		// performance test
		static void Performance(xl_function f, int cycle, double millisecond);
	};
}

#endif