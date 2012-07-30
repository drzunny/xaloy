#include "xaloytest.h"
#include <string>
using namespace std;
using namespace xaloy;

// implement the template functions
template<typename T>
bool XaloyTester::Assert(int cmpType, const T &actual, const T &expect)	{
	return false;
}

template<typename T>
bool XaloyTester::Expect(int cmpType, const T &actual, const T &expect)	{
	return false;
}

bool XaloyTester::Assert_string(int cmpType, const char *actual, const char *expect)	{
	
}

bool XaloyTester::Expect_string(int cmpType, const char *actual, const char *expect)	{
	
}

bool XaloyTester::Assert_ustring(int cmpType, const wchar_t *actual, const wchar_t *expect)	{
	
}

bool XaloyTester::Expect_ustring(int cmpType, const wchar_t *actual, const wchar_t *expect)	{
	
}

bool XaloyTester::Assert_pointer(int cmpType, const void *actual, const void *expect)	{
	
}

bool XaloyTester::Expect_pointer(int cmpType, const void *actual, const void *expect)	{
	
}

bool XaloyTester::Assert_bytes(int cmpType, const char *actual, size_t sz_1, const char *expect, size_t sz_2)	{
	
}

bool XaloyTester::Expect_bytes(int cmpType, const char *actual, size_t sz_1, const char *expect, size_t sz_2)	{
	
}

// performance test
void XaloyTester::Performance(xl_function f, int cycle, int &millisecond, int &space)	{
	
}