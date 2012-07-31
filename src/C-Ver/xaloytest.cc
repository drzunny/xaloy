#include "xaloytest.h"
#include "xaloyprinter.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace xaloy;

// the private helper functions
template<typename T>
bool XaloyTester::_compare(int cmpType, xl_message *msg, const T &actual, const T &expect)	{
	bool result = false;
	switch(cmpType)
	{
		case XL_EQUAL:
			if(actual == expect)	{
				*msg = "The actual value is equal to your expect";
				return true;
			}
			*msg = "The actual value is not equal to your expect";
			return false;
		case XL_NOT_EQUAL:
			if(actual == expect)	{
				*msg = "The actual value is equal to your expect";
				return false;
			}
			*msg = "The actual value is not equal to your expect";
			return true;
		case XL_LESS:
			if(actual < expect)	{
				*msg = "The actual value is less than your expect";
				return true;
			}
			*msg = "The actual value is not less than your expect";
			return false;
		case XL_LESS_EQUAL:
			if(actual <= expect)	{
				*msg = "The actual value is less than or equal to your expect";
				return true;
			}
			*msg = "maybe your actual value is bigger than your expect";
			return false;
		case XL_GREATER:
			if(actual > expect)	{
				*msg = "The actual value is greater than your expect";
				return true;
			}
			*msg = "The actual value is not greater than your expect";
			return false;
		case XL_GREATER_EQUAL:
			if(actual >= expect)	{
				*msg = "The actual value is greater than or equal to your expect";
				return true;
			}
			*msg = "maybe your actual value is less than your expect";
			return false;
		default:
			*msg = "invalid comparision operators";
			return false;
	}
}
bool XaloyTester::_compare_str(int cmpType, xl_message *msg, const xl_message actual, const xl_message expect)	{
	int actStrlen, expStrlen, result;
	// pre-compare the actual value and expect
	actStrlen = strlen(actual);
	expStrlen = strlen(expect);
	if(actStrlen == expStrlen)
		result = 0;
	else result = actStrlen > expStrlen? 1 : -1;
	if(result == 0)	{
		for(int i = 0; i < actStrlen; i++)	{
			if(actual[i] != expect[i])	{
				result = actual[i] > expect[i]? 1 : -1;
				break;
			}				
		}
	}
	// return the true result by the pre-cmp result and compareType
	switch(cmpType)
	{
		case XL_EQUAL:			
		case XL_NOT_EQUAL:
			if(result == 0)
				*msg = "the acutal string is equal to your expect";
			else
				*msg = "two different string";
			return (result == 0 && cmpType == XL_EQUAL)||(result != 0 && cmpType == XL_NOT_EQUAL);
		default:
			*msg = "invalid string's comparision operators";
			return false;
	}
}
bool XaloyTester::_compare_str(int cmpType, xl_message *msg, const xl_umessage actual, const xl_umessage expect)	{
	int actStrlen, expStrlen, result;
	// pre-compare the actual value and expect	
	actStrlen = wcslen(actual);
	expStrlen = wcslen(expect);
	if(actStrlen == expStrlen)
		result = 0;
	else result = actStrlen > expStrlen? 1 : -1;
	if(result == 0)	{
		for(int i = 0; i < actStrlen; i++)	{
			if(actual[i] != expect[i])	{
				result = actual[i] > expect[i]? 1 : -1;
				break;
			}				
		}
	}
	// return the true result by the pre-cmp result and compareType
	switch(cmpType)
	{
		case XL_EQUAL:			
		case XL_NOT_EQUAL:
			if(result == 0)
				*msg = "the acutal string is equal to your expect";
			else
				*msg = "two different string";
			return (result == 0 && cmpType == XL_EQUAL)||(result != 0 && cmpType == XL_NOT_EQUAL);
		default:
			*msg = "invalid string's comparision operators";
			return false;
	}
}
bool XaloyTester::_compare_byte(int cmpType, char **msg, 
								const char *actual, size_t act_sz, 
								const char *expect, size_t exp_sz)	{
	bool isEqual = false;
	if(act_sz == exp_sz)	{
		for(int i = 0; i < act_sz; i++)	{
			isEqual = actual[i] == expect[i];
			if(!isEqual)
				break;
		}
	}		
	switch(cmpType)
	{
		case XL_EQUAL:
			if(!isEqual)
				*msg = "the bytes data are equal";
			else *msg = "the bytes are not equal";
			return isEqual;
		case XL_NOT_EQUAL:
			if(!isEqual)
				*msg = "the bytes data are equal";
			else *msg = "the bytes are not equal";
			return !isEqual;
		default:
			*msg = "invalid comparision operators";
			return false;
	}
}

// implement the template functions
void XaloyTester::Assert(int cmpType, const int &actual, const int &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	if(!result)
		exit(0);
}
bool XaloyTester::Expect(int cmpType, const int &actual, const int &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

void XaloyTester::Assert(int cmpType, const long &actual, const long &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	if(!result)
		exit(0);
}
bool XaloyTester::Expect(int cmpType, const long &actual, const long &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

void XaloyTester::Assert(int cmpType, const short &actual, const short &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	if(!result)
		exit(0);
}

bool XaloyTester::Expect(int cmpType, const short &actual, const short &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

void XaloyTester::Assert(int cmpType, const char &actual, const char &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	if(!result)
		exit(0);
}

bool XaloyTester::Expect(int cmpType, const char &actual, const char &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

void XaloyTester::Assert(int cmpType, const float &actual, const float &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	if(!result)
		exit(0);
}

bool XaloyTester::Expect(int cmpType, const float &actual, const float &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

void XaloyTester::Assert(int cmpType, const double &actual, const double &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	if(!result)
		exit(0);
}

bool XaloyTester::Expect(int cmpType, const double &actual, const double &expect)	{
	char *msg = NULL;
	bool result = _compare(cmpType, &msg, actual, expect);
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

// the implement of assert/expect string
void XaloyTester::Assert_str(int cmpType, const xl_message actual, const xl_message expect)	{
	char *msg = NULL;
	bool result = _compare_str(cmpType, &msg, actual, expect);
	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	if(!result)
		exit(0);
}

bool XaloyTester::Expect_str(int cmpType, const xl_message actual, const xl_message expect)	{
	char *msg = NULL;
	bool result = _compare_str(cmpType, &msg, actual, expect);
	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

void XaloyTester::Assert_str(int cmpType, const xl_umessage actual, const xl_umessage expect)	{
	char *msg = NULL;
	bool result = _compare_str(cmpType, &msg, actual, expect);
	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	if(!result)
		exit(0);
}

bool XaloyTester::Expect_str(int cmpType, const xl_umessage actual, const xl_umessage expect)	{
	char *msg = NULL;
	bool result = _compare_str(cmpType, &msg, actual, expect);	
	// print message
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

void XaloyTester::Assert_bytes(int cmpType, 
							   const char *actual, size_t act_sz, 
							   const char *expect, size_t exp_sz)	{
	char *msg = NULL;
	bool result = _compare_byte(cmpType, &msg, actual, act_sz, expect, exp_sz);
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	exit(0);
}

bool XaloyTester::Expect_bytes(int cmpType, 
							   const char *actual, size_t act_sz, 
							   const char *expect, size_t exp_sz)	{
	char *msg = NULL;
	bool result = _compare_byte(cmpType, &msg, actual, act_sz, expect, exp_sz);
	if(result)
		print_color_text(COLOR_GREEN, "[SUCCESS]");
	else
		print_color_text(COLOR_RED, "[FAIL]   ");
	printf("%s\n", msg);
	return result;
}

// performance test
void XaloyTester::Performance(xl_function f, int cycle, double millisecond)	{
	clock_t t1, t2;
	double waste_time;
	t1 = clock();
	for(int i = 0; i < cycle; i++)
		f();
	t2 = clock();
	waste_time = (double)(t2 - t1)*1000/CLOCKS_PER_SEC;
	if(waste_time < millisecond || millisecond <= 0)
	{
		print_color_text(COLOR_GREEN,"[SUCCESS]");
		printf("execution time of the test function: %f ms", waste_time);
		if(millisecond > 0)
			printf("(less than %f ms)\n", millisecond);
		else printf("\n");
	}
	else	{
		print_color_text(COLOR_RED, "[FAIL]   ");
		printf("execution time of the test function: %f ms(slower than %f ms)\n", waste_time, millisecond);		
	}
}