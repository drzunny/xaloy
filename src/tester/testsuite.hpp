/*=============================================================================
#     FileName: testsuite.hpp
#         Desc: provide the macro function to use the xaloy test framework
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-29 15:11:08
#      History:
=============================================================================*/

#ifndef XALOY_TEST_SUITE_H
#define XALOY_TEST_SUITE_H

#include <stdio.h>
#include <iostream>

#include "testprocess.h"
#include "testcase.hpp"
#include "../base/printer.h"
#include "../base/comparer.hpp"

using namespace xaloy;
using namespace xaloy::test;
/*      Test case generator start      */

// Global Target
static XaloyTestProcess *GLOBAL_TESTER = XaloyTestProcess::create();

// normal
#define XALOY_TEST_REGISTER(casename)   \
    class casename:public XaloyTestcases {   \
    private: \
        bool _currentResult; \
        static bool _initFlag; \
    public: \
        virtual void run(); \
    };  \
    static bool casename##Initalize() {\
        casename *pcase = new casename(); \
        pcase->name = #casename; \
        GLOBAL_TESTER->push(pcase); \
        return true; \
    } \
    bool casename::_initFlag = casename##Initalize(); \
    void casename::run()

// benchmark
#define XALOY_BENCHMARK_REGISTER(casename, cycle, limit) \
    class casename##_benchmark____:public XaloyTestcases {\
    private:\
        static bool _initFlag;\
    public:\
        virtual void run();\
    };\
    static bool casename##Benchmark() {\
        casename##_benchmark____ *pcase = new casename##_benchmark____(); \
        pcase->name = #casename; \
        pcase->isBenchmark = true;\
        pcase->runCycle = cycle; \
        pcase->runLimit = limit; \
        GLOBAL_TESTER->push(pcase); \
        return true; \
    } \
    bool casename##_benchmark____::_initFlag = casename##Benchmark(); \
    void casename##_benchmark____::run()

/*      Test case generator end      */

/*      ASSERT and Expect Macros     */
#define XALOY_COMPARE_OP(act, exp, cmp, op)    \
    this->_currentResult = cmp(act, exp);   \
    this->counter++; \
    if(this->_currentResult) this->pass++; else this->error++; \
    printf("[ "); \
    XaloyBasePrinter::print("  ", F_ORIGINAL, this->_currentResult? B_GREEN : B_RED); \
    printf(" ]  expression: %s %s %s  \n        value: ", #act, op, #exp); \
    std::cout << act << " " << op <<" " << exp << std::endl

#define XALOY_EXPECT_EQUAL(act, exp)    \
    XALOY_COMPARE_OP(act, exp, isEqual, "==")

#define XALOY_EXPECT_NOT_EQUAL(act, exp) \
    XALOY_COMPARE_OP(act,exp, !isEqual, "!=")

#define XALOY_EXPECT_LESS(act, exp) \
    XALOY_COMPARE_OP(act, exp, isLess, "<")

#define XALOY_EXPECT_LESS_EQUAL(act, exp) \
    XALOY_COMPARE_OP(act, exp, isLessEqual, "<=")

#define XALOY_EXPECT_GREATER(act, exp) \
    XALOY_COMPARE_OP(act, exp, isGreater, ">")

#define XALOY_EXPECT_GREATER_EQUAL(act, exp) \
    XALOY_COMPARE_OP(act, exp, isGreaterEqual, ">=")

#define XALOY_EXPECT_ISNULL(ptr) \
    this->_currentResult = isNull(ptr);   \
    this->counter++; \
    if(this->_currentResult) this->pass++; else this->error++; \
    printf("[ "); \
    XaloyBasePrinter::print("  ", F_ORIGINAL, this->_currentResult? B_GREEN : B_RED); \
    printf(" ]  expression: %s == null  \n        value: ", #ptr); \
    printf("%s == %p\n", #ptr, ptr);

#define XALOY_EXPECT_BYTE_EQUAL(act, sz1, exp, sz2) \
    this->_currentResult = ByteEqual(act, sz1, exp, sz2);   \
    this->counter++; \
    if(this->_currentResult) this->pass++; else this->error++; \
    printf("[ "); \
    XaloyBasePrinter::print("  ", F_ORIGINAL, this->_currentResult? B_GREEN : B_RED); \
    printf(" ]  expression: %s == %s  \n        size: ", #act, #exp); \
    printf("%s : %d, %s : %d\n", #act, sz1, #exp, sz2);

#define XALOY_ASSERT(result) \
        if (!result) { \
            XaloyBasePrinter::print("\nAssert Happend!\n-----------------\nFile   :  ", F_YELLOW, B_ORIGINAL); \
            printf("%s\n", __FILE__);   \
            XaloyBasePrinter::print("LINE   :  ", F_YELLOW, B_ORIGINAL); \
            printf("%d\n", __LINE__);  \
            return; \
        }

#define XALOY_ASSERT_EQUAL(act, exp) \
        XALOY_EXPECT_EQUAL(act, exp); \
        XALOY_ASSERT(this->_currentResult)

#define XALOY_ASSERT_NOT_EQUAL(act, exp) \
        XALOY_EXPECT_NOT_EQUAL(act, exp); \
        XALOY_ASSERT(this->_currentResult)

#define XALOY_ASSERT_LESS(act, exp) \
        XALOY_EXPECT_LESS(act, exp); \
        XALOY_ASSERT(this->_currentResult)        

#define XALOY_ASSERT_LESS_EQUAL(act, exp)   \
        XALOY_EXPECT_LESS_EQUAL(act, exp); \
        XALOY_ASSERT(this->_currentResult)        

#define XALOY_ASSERT_GREATER(act, exp)  \
        XALOY_EXPECT_GREATER(act, exp); \
        XALOY_ASSERT(this->_currentResult)

#define XALOY_ASSERT_GREATER_EQUAL(act, exp)    \
        XALOY_EXPECT_GREATER_EQUAL(act, exp); \
        XALOY_ASSERT(this->_currentResult)

#define XALOY_ASSERT_ISNULL(ptr)    \
        XALOY_EXPECT_ISNULL(ptr); \
        XALOY_ASSERT(this->_currentResult)

#define XALOY_ASSERT_BYTE_EQUAL(act, sz1, exp, sz2)   \
        XALOY_EXPECT_BYTE_EQUAL(act, sz1, exp, sz2); \
        XALOY_ASSERT(this->_currentResult)


#endif
