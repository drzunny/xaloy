#include <stdio.h>
#include <stddef.h>

/*	define the function for the testing	*/
static int
getFabb(int pos)	{
	return (1+pos)*pos/2;
}

static int
getsumm(const int *array, int sz)	{
	int summ = 0;
	for(int i = 0; i < sz; i++)
		summ+=array[i];
	return summ;
}

class XaloyTest	{
public:
	template<typename T>
	static bool Compare(const T&actual, const T&expect)	{
		return actual == expect;
	}	
};

int main()
{
	bool result = XaloyTest::Compare(getFabb(3), 6);
	const char *str = "Hello fucking u";
	result = XaloyTest::Compare(str, str);
	if(result)	
	{
		printf("Check it out\n");
	}
	else
	{
		printf("Fuck it all\n");
	}
	return 0;
}