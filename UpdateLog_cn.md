# 2012-07-31

##Lua部分
+ 实现了object test的功能，通过xaloy.new创建一个新的测试对象
+ 修复了一些潜在的bug，优化了xaloytool的代码

##C++ port
+ 实现了C++版本的xaloy
+ 调用方式和Lua有所差别，使用了仿gtest的方式，以test module对测试过程进行包装
+ 支持assert, expect, performance操作，并且另外增加了assert_str, expect_str, assert_bytes, expect_bytes的功能
+ 当前C++ port的版本是 ver 0.1.0, 完善程度不丰富。但是可以进行简单的测试（本来就是面向Quab的简单测试工具）

        下一步可能会先放缓xaloy的更新，全程投入到Quab的开发当中。
        下次更新主要以修复Lua部分的bug和重构C++ port为主，暂不增加新功能，
        版本号依然是ver 0.2.x

# 2012-07-11

+ 基本上重构了全部的代码
+ 到目前为止已经实现了单个的assert, expect, performance测试
+ 支持打印日志和输出html
+ 经测试表明xaloy能够直接用于luajit上
+ 目前版本 ver.0.2.0

        下次更新将会完成剩下的Object Test功能，支持以对象为单位执行指定的测试用例集合