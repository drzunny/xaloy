# Xaloy Test Framework

Xaloy测试框架是为Quab而设的一款用于Lua或者C/C++类库的自动化测试工具。致力于简化Quab的测试流程。

希望Xaloy以后能够成为一款通用的测试工具～

Xaloy的将会使用到下面的开源库

+ lua 5.2
+ luajit 2.0 beta 10
+ swig

但是Xaloy **不会** 在这里的源码里面提供这些库

请自行下载并编译后，将头文件和库文件放进lib的文件夹里面～谢谢合作


# 如何测试C/C++的函数

将需要测试的模块或者接口，编译为Lua扩展的dll或者so。就能够使用Xaloy进行测试

如果对于不太复杂的函数，可以用swig直接进行包装成拓展库，编译后即可

一旦数据结构更比较复杂的情况下，建议还是手动编写binding

此外，xaloy支持使用luajit进行编译. 所以如果在使用luajit的情况下，使用ffi进行绑定是一个适合的做法

# HOW TO USE

xaloy的使用方法比较简单，在lua方面，你可以参考下面代码来创建一个测试：

```Lua
  -- import xaloy library
  require("xaloy")  
  function foo1(a,b)
    return a + b;
  end
  
  function foo2(a,b)
    return a*b;
  end
  
  -- create the test case object
  local case = {
    {name = "foo1_test", f = foo1, mode = "EQ", case = {{1,2},{3,4},{5,6}}, expect = {3,7,10}, cycle = 100},
    {name = "foo2_test", f = foo2, mode = "EQ", case = {{1,2},{3,4},{5,6}}, expect = {2,11,30}, cycle = 100},
  }
  
  local xobject = xaloy.new("example", case)
  xobject.expect()
  xobject.performance()   -- a easy performance test
  xobject.assert()
  
  -- if u just want to test the function without xaloy's object
  xaloy.expect("foo1_test", "EQ", 100, foo1(1,99))
  xaloy.assert("foo2_test", "EQ", 50, foo1(2,55))
  xaloy.performance("performance_foo1", function() foo1(1,1) end, 100, 1)
```

至于，在ver 0.2.0 的xaloy中附带的C++版本，可以通过使用XALOY_TEST_MODULE的方法来包装测试：

```CPP
#include <xaloy.h>
using namespace xaloy;

DEFINE_XALOY_FUNCTION(sfunc)  {
	int cnt = 100;
	int summ = 0;
	for(int i = 0; i < cnt; i++)
		summ+=i+1;
}

XALOY_TEST_MODULE(simpletest)	{
	XaloyTester::Expect(XL_EQUAL, 1, 0);
	XaloyTester::Expect(XL_LESS, 0, 2);	
	XaloyTester::Expect(XL_GREATER, 0, 2);	
	XaloyTester::Expect_str(XL_EQUAL,"Hello world", "Hello world");
	XaloyTester::Performance(sfunc, 10000, 2000);
}

int main(int argc, char **argv)
{		
	return GLOBAL_TEST->execute();
}
```
