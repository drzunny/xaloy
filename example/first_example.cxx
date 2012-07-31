#include <stdio.h>
#include <xaloy.h>
using namespace xaloy;

DEFINE_XALOY_FUNCTION(sfunc)	{
	int cnt = 100;
	int summ = 0;
	for(int i = 0; i < cnt; i++)
		summ+=i+1;
}

XALOY_TEST_MODULE(simpletest)	{
	XaloyTester::Expect(XL_EQUAL, 1, 1);
	XaloyTester::Expect(XL_LESS, 0, 2);	
	XaloyTester::Expect_str(XL_EQUAL,"Hello world", "Hello world");
	XaloyTester::Performance(sfunc, 10000, 2000);
}

int main(int argc, char **argv)
{
	return GLOBAL_TEST.execute();
}
