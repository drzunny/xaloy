/*=============================================================================
#     FileName: reporter.h
#         Desc: Xaloy's test reporter
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-29 14:55:09
#      History:
=============================================================================*/

#ifndef XALOY_TEST_REPORTER_H
#define XALOY_TEST_REPORTER_H

namespace xaloy {
namespace test  {

    // forward declaration
    class XaloyTestcases;

    class TestReporter {
    public:
        static void caseReportHeader(const XaloyTestcases *pcase);
        static void caseReport(const XaloyTestcases *pcase);
    };
}}

#endif
