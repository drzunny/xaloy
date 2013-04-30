/*=============================================================================
#     FileName: testcase.hpp
#         Desc: base class for test case
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-29 13:48:55
#      History:
=============================================================================*/

#ifndef XALOY_TEST_CASE_H
#define XALOY_TEST_CASE_H

namespace xaloy {
namespace test  {
    class XaloyTestcases {
    public:
        XaloyTestcases () { name = NULL; counter = pass = error = runCycle = runLimit = 0; isBenchmark = false; }
        ~XaloyTestcases () { name = NULL; counter = pass = error = runCycle = runLimit = 0; isBenchmark = false; }

        virtual void run() {}

        const char *name;
        bool isBenchmark;
        unsigned counter, pass, error, runCycle, runLimit, runCost;
    };
}}

#endif
