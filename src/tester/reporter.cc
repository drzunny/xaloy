/*=============================================================================
#     FileName: reporter.cc
#         Desc: implements of report
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-29 15:10:07
#      History:
=============================================================================*/

#include "reporter.h"

#include <stdio.h>

#include "../base/printer.h"
#include "testcase.hpp"

using namespace xaloy;
using namespace xaloy::test;

void TestReporter::caseReportHeader(const XaloyTestcases *pcase)
{
    if (pcase->isBenchmark) {
        printf("\nBENCHMARK   : ");
    }
    else
        printf("\nTest Case   : ");
    XaloyBasePrinter::print(pcase->name, F_BLUE, B_ORIGINAL);
    printf("\n--------------------------------------------\n\n");
}

void TestReporter::caseReport(const XaloyTestcases *pcase)
{
    /*      HEADER      */
    printf("\n--------------------------------------------\n");
    /*      CONTENT     */
    printf("Status:");
    if (pcase->error > 0) {
        XaloyBasePrinter::print("FAILURE", F_RED, B_ORIGINAL);
    }   else    {
        XaloyBasePrinter::print("SUCCESS", F_GREEN, B_ORIGINAL);
    }
    printf("   Total:%d    Pass:%d    Error:%d\n\n", pcase->counter, pcase->pass, pcase->error);
}
