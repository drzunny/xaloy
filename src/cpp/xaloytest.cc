#include "xaloytest.h"
#include "xaloyprinter.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifndef OS_WIN32
#include <wchar.h>
#endif

using namespace xaloy;

// print helper
static void 
helper_printmsg(bool result, bool isAssert)	{
	int color = result? COLOR_GREEN : COLOR_RED;
	if(isAssert)	{
		print_color_text(color, result? "[ASSERT SUCCESS] " : "[ASSERT FAIL]    ");
	} else	{
		print_color_text(color, result? "[    SUCCESS   ] " : "[    FAIL   ]    ");
	}
}

// static value
bool XaloyTester::cmp_result = false;

// allow error range
float XaloyTester::_allowprec = 0.0f; 

void XaloyTester::SetAllowPrec(float allowprec)	{
	_allowprec = allowprec;
}

// the private helper functions
template<typename T>
bool XaloyTester::_compare(int cmpType, const T &actual, const T &expect)	{
	bool result = false;
	float distance = (float)(actual - expect);
	switch(cmpType)
	{
		case XL_EQUAL:
			if(fabs(distance) <= _allowprec)	{
				return true;
			}
			return false;
		case XL_NOT_EQUAL:
			if(fabs(distance) <= _allowprec)	{
				return false;
			}
			return true;
		case XL_LESS:
			if(actual < expect && fabs(distance) > _allowprec)	{
				return true;
			}
			return false;
		case XL_LESS_EQUAL:
			if(actual <= expect)	{
				return true;
			}
			return false;
		case XL_GREATER:
			if(actual > expect && fabs(distance) > _allowprec)	{
				return true;
			}
			return false;
		case XL_GREATER_EQUAL:
			if(actual >= expect)	{
				return true;
			}
			return false;
		default:
			return false;
	}
}
bool XaloyTester::_compare_str(int cmpType, xl_message actual, xl_message expect)	{
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
			return (result == 0 && cmpType == XL_EQUAL)||(result != 0 && cmpType == XL_NOT_EQUAL);
		default:
			return false;
	}
}
bool XaloyTester::_compare_str(int cmpType, xl_umessage actual, xl_umessage expect)	{
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
			return (result == 0 && cmpType == XL_EQUAL)||(result != 0 && cmpType == XL_NOT_EQUAL);
		default:
			return false;
	}
}
bool XaloyTester::_compare_byte(int cmpType,
								const char *actual, size_t act_sz, 
								const char *expect, size_t exp_sz)	{
	bool isEqual = false;
	if(act_sz == exp_sz)	{
		for(size_t i = 0; i < act_sz; i++)	{
			isEqual = actual[i] == expect[i];
			if(!isEqual)
				break;
		}
	}		
	switch(cmpType)
	{
		case XL_EQUAL:			
			return isEqual;
		case XL_NOT_EQUAL:			
			return !isEqual;
		default:			
			return false;
	}
}

// implement the template functions
bool XaloyTester::Compare(int cmpType, const int &actual, const int &expect, bool isAssert)	{
	bool result = _compare(cmpType, actual, expect);
	// print message
	helper_printmsg(result, isAssert);
	return result;
}

bool XaloyTester::Compare(int cmpType, const long &actual, const long &expect, bool isAssert)	{
	bool result = _compare(cmpType, actual, expect);
	helper_printmsg(result, isAssert);
	return result;
}

bool XaloyTester::Compare(int cmpType, const short &actual, const short &expect, bool isAssert)	{
	bool result = _compare(cmpType, actual, expect);
	helper_printmsg(result, isAssert);
	return result;
}

bool XaloyTester::Compare(int cmpType, const char &actual, const char &expect, bool isAssert)	{
	bool result = _compare(cmpType, actual, expect);
	helper_printmsg(result, isAssert);
	return result;
}

bool XaloyTester::Compare(int cmpType, const float &actual, const float &expect, bool isAssert)	{
	bool result = _compare(cmpType, actual, expect);
	helper_printmsg(result, isAssert);
	return result;
}

bool XaloyTester::Compare(int cmpType, const double &actual, const double &expect, bool isAssert)	{
	bool result = _compare(cmpType, actual, expect);
	helper_printmsg(result, isAssert);
	return result;
}

// the implement of assert/expect string
bool XaloyTester::Compare_str(int cmpType, const xl_message actual, const xl_message expect, bool isAssert)	{
	bool result = _compare_str(cmpType, actual, expect);
	helper_printmsg(result, isAssert);
	return result;
}

bool XaloyTester::Compare_str(int cmpType, const xl_umessage actual, const xl_umessage expect, bool isAssert)	{
	bool result = _compare_str(cmpType, actual, expect);	
	helper_printmsg(result, isAssert);
	return result;
}

bool XaloyTester::Compare_bytes(int cmpType, 
							   const char *actual, size_t act_sz, 
							   const char *expect, size_t exp_sz, bool isAssert)	{
	bool result = _compare_byte(cmpType, actual, act_sz, expect, exp_sz);
	helper_printmsg(result, isAssert);
	return result;
}

// performance test
bool XaloyTester::Performance(xl_function f, int cycle, double millisecond)	{
	clock_t t1, t2;
	double waste_time;
	t1 = clock();
	for(int i = 0; i < cycle; i++)
		f();
	t2 = clock();
	waste_time = (double)(t2 - t1)*1000/CLOCKS_PER_SEC;	
	if(waste_time < millisecond || millisecond <= 0)
	{
		print_color_text(COLOR_GREEN,"[SUCCESS] ");
		printf("execution time: %f ms", waste_time);
		if(millisecond > 0)
			printf(", less than %f ms\n", millisecond);
		else printf("\n");
		return true;
	}
	else	{
		print_color_text(COLOR_RED, "[FAIL]    ");
		printf("execution time : %f ms, slower than %f ms\n", waste_time, millisecond);		
		return false;
	}
}

bool XaloyTester::Compare_null(int cmpType, const void* ptr, bool isAssert)	{
	bool result = false;
	switch(cmpType)
	{
	case XL_ISNULL:				
	case XL_NOTNULL:
		if((ptr == NULL && cmpType == XL_ISNULL) || (ptr != NULL && cmpType == XL_NOTNULL))	{
			helper_printmsg(true, isAssert);
			result = true;
		}
		else	{
			helper_printmsg(false, isAssert);
			result = false;
		}
		break;
	default:
		result = false;
		break;
	}
	return result;
}
