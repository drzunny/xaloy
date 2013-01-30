/*=============================================================================
#     FileName: common.h
#         Desc: xaloy's common helper, include string hash, md5, etc.
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-28 14:33:54
#      History:
=============================================================================*/

#ifndef XALOY_BASE_COMMON_H
#define XALOY_BASE_COMMON_H

#include <string>
#include <ctime>

#define XALOY_HASH_SEED 3779

namespace xaloy {
    struct XDateInfo {
        char timeString[20];
        unsigned tick;
        double msecond() const { return (double)this->tick * 1000.0 / CLOCKS_PER_SEC; }
    };

    class XaloyCommon {
    public:
        XaloyCommon ();
        ~XaloyCommon();

        void reset_seed();
        int random(unsigned start = 0, unsigned end = 0);
        double random_f();

        unsigned getHash(const std::string &s);
        std::string md5(const std::string &filepath);

        XDateInfo now(bool isDetail = true);
        double diffTime(const XDateInfo &start, const XDateInfo &end) { return end.msecond() - start.msecond(); }
    private:
        unsigned _rSeed;
    };
}

#endif
