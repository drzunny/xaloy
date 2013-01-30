/*=============================================================================
#     FileName: testprocess.h
#         Desc: the test process manager
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-29 13:53:59
#      History:
=============================================================================*/

#ifndef XALOY_TEST_PROCESS_H
#define XALOY_TEST_PROCESS_H

namespace xaloy
{
namespace test
{
    class XaloyTestcases;
    struct _taskQueue;

    class XaloyTestProcess {
    public:
        static XaloyTestProcess* create();
        ~XaloyTestProcess();

        int execute(bool isPager = false);
        void push(XaloyTestcases *pCase);
        void report(const XaloyTestcases *pCase);
    private:
        static XaloyTestProcess *_instance;
        _taskQueue *_taskqueue;
        XaloyTestProcess();

        void _startHeader(const XaloyTestcases *pCase);
    };
}
}

#endif
