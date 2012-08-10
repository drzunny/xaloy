#ifndef XALOYTEST_H
#define XALOYTEST_H

#include <stddef.h>
#include <stdio.h>

#define	XL_EQUAL			0
#define	XL_NOT_EQUAL		1
#define	XL_LESS				2
#define	XL_GREATER			3
#define	XL_LESS_EQUAL		4
#define	XL_GREATER_EQUAL	5
#define XL_ISNULL			6
#define XL_NOTNULL			7

#define CMP_RESULT XaloyTester::cmp_result
#define DEFINE_XALOY_FUNCTION(fname)	static void (fname)()

// The marco API for Assert and Expect

// Assert API
#define XALOY_ASSERT(cmptype, act, exp) \
	CMP_RESULT = XaloyTester::Compare((cmptype), (act), (exp), true);	\
	printf("%s test:(actual:%s, expect:%s)\n", #cmptype, #act, #exp); \
	if(!CMP_RESULT) {printf("Assert Error!\n");getchar();}	\
	if(!CMP_RESULT) exit(0)

#define XALOY_ASSERT_STR(cmptype, act, exp) \
	CMP_RESULT = XaloyTester::Compare_str((cmptype), (act), (exp), true); \
	printf("string %s test:(act:%s, exp:%s)\n", #cmptype, #act, #exp); \
	if(!CMP_RESULT) {printf("Assert Error!\n");getchar();}	\
	if(!CMP_RESULT) exit(0)
	
#define XALOY_ASSERT_BYTE(cmptype, act, asz, exp, esz) \
	CMP_RESULT = XaloyTester::Compare_bytes((cmptype),(act),(asz),(exp),(esz), true); \
	printf("bytes %s test:(act:%s, exp:%s)\n", #cmptype, #act, #exp); \
	if(!CMP_RESULT) {printf("Assert Error!\n");getchar();}	\
	if(!CMP_RESULT) exit(0)
	
#define XALOY_ASSERT_NULL(cmptype, act) \
	CMP_RESULT = XaloyTester::Compare_null((cmptype), (void*)act, true);\
	printf("pointer test:(act:%s, exp:%s)\n", #act, #cmptype); \
	if(!CMP_RESULT) {printf("Assert Error!\n");getchar();}	\
	if(!CMP_RESULT) exit(0)

// Expect API
#define XALOY_EXPECT(cmptype, act, exp) \
	this->_counter++; \
	CMP_RESULT = XaloyTester::Compare((cmptype), (act), (exp));	\
	printf("%s test:(actual:%s, expect:%s)\n", #cmptype, #act, #exp); \
	if(CMP_RESULT) this->_pass+=1
	
#define XALOY_EXPECT_STR(cmptype, act, exp) \
	this->_counter++; \
	CMP_RESULT = XaloyTester::Compare_str((cmptype), (act), (exp)); \
	printf("string %s compare test:(act:%s, exp:%s)\n", #cmptype, #act, #exp); \
	if(CMP_RESULT) this->_pass+=1
	
#define XALOY_EXPECT_BYTE(cmptype, act, asz, exp, esz)  \
	this->_counter++; \
	CMP_RESULT = XaloyTester::Compare_bytes((cmptype),(act),(asz),(exp),(esz)); \
	printf("bytes %s compare test:(act:%s, exp:%s)\n", #cmptype, #act, #exp); \
	if(CMP_RESULT) this->_pass+=1
	
#define XALOY_EXPECT_NULL(cmptype, act)  \
	this->_counter++; \
	CMP_RESULT = XaloyTester::Compare_null((cmptype), (void*)act);\
	printf("pointer test:(act:%s, exp:%s)\n", #act, #cmptype); \
	if(CMP_RESULT) this->_pass+=1

// performance API
#define XALOY_PERFORMANCE(f, c, ms)	\
	this->_counter++; \
	if(XaloyTester::Performance((f), (c), (ms))) this->_pass+=1
	
	
typedef void (*xl_function)();
typedef const char* xl_message;
typedef const wchar_t* xl_umessage;

namespace xaloy	
{	
	class XaloyTester
	{
	private:
		// helper functions for compare the values
		template<typename T>
		static bool _compare(int cmpType, const T &actual, const T &expect);
		static bool _compare_str(int cmpType, const xl_message actual, const xl_message expect);
		static bool _compare_str(int cmpType, const xl_umessage actual, const xl_umessage expect);
		static bool _compare_byte(int cmpType, const char *actual, size_t act_sz, const char *expect, size_t exp_sz);
		
		// allowed error range
		static float _allowprec;
		
	public:
		// assert and expect test
		static bool Compare(int cmpType, const int &actual, const int &expect, bool isAssert = false);
		static bool Compare(int cmpType, const long &actual, const long &expect, bool isAssert = false);
		static bool Compare(int cmpType, const short &actual, const short &expect, bool isAssert = false);
		static bool Compare(int cmpType, const char &actual, const char &expect, bool isAssert = false);
		static bool Compare(int cmpType, const float &actual, const float &expect, bool isAssert = false);
		static bool Compare(int cmpType, const double &actual, const double &expect, bool isAssert = false);
		
		static bool Compare_str(int cmpType, xl_message actual, xl_message expect, bool isAssert = false);
		static bool Compare_str(int cmpType, xl_umessage actual, xl_umessage expect, bool isAssert = false);	
		
		static bool Compare_bytes(int cmpType, const char *actual, size_t act_sz, const char *expect, size_t exp_sz, bool isAssert = false);
		
		static bool Compare_null(int cmpType, const void* ptr, bool isAssert = false);
		
		// performance test
		static bool Performance(xl_function f, int cycle, double millisecond);
		
		// static assert status
		static bool cmp_result;
		
		// set comparision's error precious
		static void SetAllowPrec(float allprec = 0.0f);
	};
}

#endif
