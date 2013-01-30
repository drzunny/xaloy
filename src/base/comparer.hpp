/*=============================================================================
#     FileName: xtcompare.h
#         Desc: Compare tools
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-28 19:31:31
#      History:
=============================================================================*/

#ifndef XALOY_COMPARE_H
#define XALOY_COMPARE_H

#include <string>
#include <cmath>
#include <string.h>

namespace xaloy
{
    // Property
    static double AllowPrec = 0.005;

    //  Equal
    template<typename T>
    bool isEqual(const T a, const T b) { return fabs((double)a - (double)b) <= AllowPrec; }
    template<>
    bool isEqual(const char *a, const char *b) { return a == NULL || b == NULL ? false:strcmp(a, b) == 0; }    
    template<>
    bool isEqual(const std::string &a, const std::string &b) { return a.compare(b) == 0; }

    // Greater
    template<typename T>
    bool isGreater(const T a, const T b) { return  (double)a - (double)b > AllowPrec; }
    template<>
    bool isGreater(const char *a, const char *b) { return a == NULL || b == NULL ? false : strcmp(a, b) > 0; }         
    template<>
    bool isGreater(const std::string &a, const std::string &b) { return a.compare(b) > 0; }

    template<typename T>
    bool isGreaterEqual(const T a, const T b) { return  (double)a - (double)b > 0; }
    template<>
    bool isGreaterEqual(const char *a, const char *b) { return a == NULL | b == NULL ? false : strcmp(a, b) >= 0; }
    template<>
    bool isGreaterEqual(const std::string &a, const std::string &b) { return a.compare(b) >= 0; }

    // Less
    template<typename T>
    bool isLess(const T a, const T b) { return  (double)a - (double)b < -1 * AllowPrec; }
    template<>
    bool isLess(const char *a, const char *b) { return a == NULL || b == NULL ? false : strcmp(a, b) < 0; }         
    template<>
    bool isLess(const std::string &a, const std::string &b) { return a.compare(b) < 0; }

    template<typename T>
    bool isLessEqual(const T a, const T b) { return  (double)a - (double)b < 0; }
    template<>
    bool isLessEqual(const char *a, const char *b) { return a == NULL | b == NULL ? false : strcmp(a, b) <= 0; }
    template<>
    bool isLessEqual(const std::string &a, const std::string &b) { return a.compare(b) <= 0; }

    // Others
    template<typename T>
    bool isNull(const T *obj) { return obj == NULL; }

    bool ByteEqual(const char *d1, unsigned sz1, const char *d2, unsigned sz2) {
        if (d1 == NULL || d2 == NULL || sz1 != sz2) {
            return false;
        }
        int i;
        for (i = 0; i < sz1; i++) {
            if(d1[i] != d2[i])
                return false;
        }
        return true;
    }
}


#endif
