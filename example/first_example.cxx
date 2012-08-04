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
	XALOY_EXPECT(XL_EQUAL, 1, 0);
	XALOY_EXPECT(XL_LESS, 0, 2);	
	XALOY_EXPECT(XL_GREATER, 0, 2);	
	XALOY_EXPECT_STR(XL_EQUAL,"Hello world", "Hello world");
	XALOY_PERFORMANCE(sfunc, 10000, 2000);
}

int main(int argc, char **argv)
{		
	return GLOBAL_TEST->execute();
}
