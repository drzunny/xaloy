#ifndef XALOYTEST_H
#define XALOYTEST_H

enum	{
	XL_EQUAL			= 0,
	XL_NOT_EQUAL		= 1,
	XL_LESS				= 2,
	XL_GREATER			= 3,
	XL_LESS_EQUAL		= 4,
	XL_GREATER_EQUAL	= 5
} XALOYCMP_ENUM;

namespace xaloy	
{
	template<typename T>
	class XaloyTester
	{
	public:
		// assert and expect test
		static bool Assert(int cmpType, const T &actual, const T &expect) const;
		static bool Expect(int cmpType, const T &actual, const T &expect) const;
		
		// performance test
		static void Performance(xl_function f, int cycle, int &millisecond, int &space) const;
	};
}

#endif