/*=============================================================================
#     FileName: filestream.h
#         Desc: provide the simple IO operations
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-28 15:34:03
#      History:
=============================================================================*/

#include <string>
#include <stdio.h>

namespace xaloy
{
    class XaloyFilestream {
    public:
        XaloyFilestream (const std::string &path, const char *mode);
        ~XaloyFilestream();

        /*  base operations */
        inline unsigned getSize() { return this->_size; }
        void write(const char *data, unsigned sz);
        char *read(unsigned offset, unsigned len);
        void flush();
    
        /*  static methods  */
        static void copy(const std::string &src, const std::string &dst);
        static void remove(const std::string &path);
    private:
        FILE * _fHandler;
        unsigned _size;
    };
}
