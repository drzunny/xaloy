/*=============================================================================
#     FileName: testprocess.cc
#         Desc: implement of the test proecess
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-29 15:10:29
#      History:
=============================================================================*/
#include "testprocess.h"

#include <stdio.h>
#include <stddef.h>
#include <queue>

#include "testcase.hpp"
#include "reporter.h"

namespace xaloy
{   
namespace test
{
    // implement of _taskQueue
    struct _taskQueue {
        std::queue<XaloyTestcases*> caseQueue;
        unsigned counter;

        _taskQueue() { counter = 0; }
    };

    // static instance
    XaloyTestProcess *XaloyTestProcess::_instance = NULL;

    /****        constructure methods       ****/
    XaloyTestProcess::XaloyTestProcess()
    {
        this->_taskqueue = new _taskQueue();
    }
    XaloyTestProcess::~XaloyTestProcess()
    {
        delete this->_taskqueue;
    }
    XaloyTestProcess* XaloyTestProcess::create()
    {
        if (!XaloyTestProcess::_instance) {
            XaloyTestProcess::_instance = new XaloyTestProcess();
        }
        return XaloyTestProcess::_instance;
    }

    /****       operation implements        ****/
    int XaloyTestProcess::execute(bool isPager)
    {
        XaloyTestcases *current = NULL;
        while(!_taskqueue->caseQueue.empty())   {
            current = _taskqueue->caseQueue.front();
            this->_startHeader(current);
            current->run();
            this->report(current);
            delete current;
            _taskqueue->caseQueue.pop();
            if (isPager) {
                printf("Press enter to continue\n");
                getchar();
            }
        }
    }
    void XaloyTestProcess::push(XaloyTestcases *pCase)
    {
        _taskqueue->counter++;
        _taskqueue->caseQueue.push(pCase);
    }
    void XaloyTestProcess::report(const XaloyTestcases *pCase)
    {
        TestReporter::caseReport(pCase);
    }
    void XaloyTestProcess::_startHeader(const XaloyTestcases *pCase)
    {
        TestReporter::caseReportHeader(pCase);
    }
} // test
} // xaloy
