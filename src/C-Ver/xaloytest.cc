#include "xaloytest.h"
#include <string>
#include <assert.h>
using namespace std;
using namespace xaloy;

// implement the template functions
template<typename T>
bool XaloyTester::Assert(int cmpType, const T &actual, const T &expect)	{
	bool result = XaloyTester::Expect(cmpType, actual, expect);
	assert(result == true);
}

template<typename T>
bool XaloyTester::Expect(int cmpType, const T &actual, const T &expect)	{
	bool result = false;
	switch(cmpType)
	{
		case XL_EQUAL:
			result = actual == expect;
			break;
		case XL_NOT_EQUAL:
			result = actual != expect;
			break;
		case XL_LESS:
			result = actual < expect;
			break;
		case XL_LESS_EQUAL:
			result = actual <= expect;
			break;
		case XL_GREATER:
			result = actual > expect;
			break;
		case XL_GREATER_EQUAL:
			result = actual >= expect;
			break;
		default:
			break;
	}
	return result;
}

bool XaloyTester::Assert(int cmpType, const char *actual, const char *expect)	{
	bool result = XaloyTester::Expect(cmpType, actual, expect);
	assert(result == true);
}

bool XaloyTester::Expect(int cmpType, const char *actual, const char *expect)	{
	bool result = false;
	switch(cmpType)
	{
		case XL_EQUAL:
			result = actual == expect;
			break;
		case XL_NOT_EQUAL:
			result = actual != expect;
			break;
		case XL_LESS:
			result = actual < expect;
			break;
		case XL_LESS_EQUAL:
			result = actual <= expect;
			break;
		case XL_GREATER:
			result = actual > expect;
			break;
		case XL_GREATER_EQUAL:
			result = actual >= expect;
			break;
		default:
			break;
	}
	return result;
}

bool XaloyTester::Assert(int cmpType, const wchar_t *actual, const wchar_t *expect)	{
	
}

bool XaloyTester::Expect(int cmpType, const wchar_t *actual, const wchar_t *expect)	{
	
}

bool XaloyTester::Assert_bytes(int cmpType, const char *actual, size_t sz_1, const char *expect, size_t sz_2)	{
	
}

bool XaloyTester::Expect_bytes(int cmpType, const char *actual, size_t sz_1, const char *expect, size_t sz_2)	{
	
}

// performance test
void XaloyTester::Performance(xl_function f, int cycle, int &millisecond, int &space)	{
	
}