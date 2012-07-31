Xaloy Test Framework
=====
Xaloy测试框架是为Quab而设的一款用于Lua或者C/C++类库的自动化测试工具。致力于简化Quab的测试流程。

希望Xaloy以后能够成为一款通用的测试工具～

Xaloy的将会使用到下面的开源库

+ lua 5.2
+ luajit 2.0 beta 10
+ swig

但是Xaloy **不会** 在这里的源码里面提供这些库

请自行下载并编译后，将头文件和库文件放进lib的文件夹里面～谢谢合作


# 如何测试C/C++的函数
=========
可以自写Lua wrapper或者使用swig生成lua Binding的代码。然后用xaloy进行测试。

在xaloy的ver 0.2.0中新增了C++ port，现在可以使用C++ port进行测试。代码在src/C-VER里