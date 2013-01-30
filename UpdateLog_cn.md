# 2013-01-30

新版本(0.3.0)开发，目前基本完成了：

+ 测试模块的重构，优化了调用的流程和代码生成，其中代码生成用了一个统一的hpp文件处理
+ 开始修改cmake的构建脚本

0.3.0版本着手于测试模块的重构开发，将来的0.3.5将会提供build tools模块， 0.4.0则提供测试生成模块

# 2012-08-04

本次是一次重要更新，版本是ver 0.2.1


  + 重构了xaloytest模块，合并了assert和expect操作为compare操作
  + 添加了 “XALOY_*” 系列的宏函数作为xaloy的测试API，取代了原来使用XaloyTester::Assert等
  + 在GLOBAL_TEST的execute中新增了一个ispager的参数，默认为false，为true时可以分页预览case
  + 修改了测试输出的文字描述，通过使用宏API可以输出比较时候的表达式和相应的比较操作
  + 每个case的测试新增了测试的方法数和通过数的统计
  + 重写了一下cmakelists.txt

        本次属于修复型的更新，0.2.0版本在编译时会有大量的warining。在本次更新中已经解决。
        并且追加了之前版本中因计划延误等问题而没有加上的一些功能，例如如total和pass的统计
  
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
