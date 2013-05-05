/*=============================================================================
#     FileName: printer.h
#         Desc: a printer helper for xaloy tools
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-28 13:57:23
#      History: this source file from project 'milk-tea'
=============================================================================*/

#ifndef XALOY_BASE_PRINTER_H
#define XALOY_BASE_PRINTER_H

namespace xaloy {
#ifdef defined(WIN32) || defined(_WIN32) || defined(_WINDOWS)
    enum    {
        F_RED       = 12,   /*  8 | 4 */
        F_YELLOW    = 14,   /*  8 | 4 | 2 */
        F_BLUE      = 11,   /*  8 | 1 */
        F_GREEN     = 10,   /*  8 | 2 */
        F_WHITE     = 15,   /*  8 | 4 | 2 | 1 */
        F_ORIGINAL  = -1,
        B_RED       = 192,  /*  128 | 64 */
        B_YELLOW    = 224,  /*  128 | 64 | 32 */
        B_BLUE      = 144,  /*  128 | 32 */
        B_GREEN     = 160,  /*  128 | 16 */
    B_ORIGINAL  = -1
    };
#else
    enum    {
        F_RED       = 31,  
        F_YELLOW    = 33,  
        F_BLUE      = 34,  
        F_GREEN     = 32,
        F_WHITE     = 37,
        F_ORIGINAL  = -1,
        B_RED       = 41,  
        B_YELLOW    = 43,  
        B_BLUE      = 44,  
        B_GREEN     = 42,  
        B_ORIGINAL  = -1
    };
#endif

    class XaloyBasePrinter {
    public:
        static void print(const char *msg, int fColor, int bColor);
    
        static inline void println(const char *msg, int fColor, int bColor)    {
            XaloyBasePrinter::print(msg, fColor, bColor);
            XaloyBasePrinter::print("\n", F_ORIGINAL, B_ORIGINAL);
        }
    };
}

#endif
