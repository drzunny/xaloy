/*=============================================================================
#     FileName: testsuite_demo.cc
#         Desc: test suite demo
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.0.1
#   LastChange: 2013-01-30 09:36:42
#      History:
=============================================================================*/
#include "../src/XTest.hpp"

using namespace xaloy;
using namespace xaloy::test;

XALOY_TEST_REGISTER(array_test)
{
    int arr[] = {1, 1, 2};
    void *p = NULL;
    XALOY_EXPECT_EQUAL(arr[0], arr[1]);
    XALOY_ASSERT_EQUAL(arr[0], arr[1]);
    XALOY_EXPECT_GREATER(arr[0], arr[2]);
    XALOY_ASSERT_ISNULL(p);
}

int main(int argc, const char *argv[])
{
    return GLOBAL_TESTER->execute();
}
