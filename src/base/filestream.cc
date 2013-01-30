/*=============================================================================
#     FileName: filestream.cc
#         Desc: implements of filestream module
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-28 15:40:19
#      History:
=============================================================================*/

#include "filestream.h"

#include <assert.h>
#ifdef XALOY_PLATFORM_WINDOWS
#   include <io.h>
#else
#   include <sys/io.h>
#endif

using namespace xaloy;
using namespace std;

XaloyFilestream::XaloyFilestream(const string &path, const char *mode)
{
    assert(!path.empty() && mode != NULL);
    this->_fHandler = fopen(path.c_str(), mode);
    assert(this->_fHandler != NULL);
    fseek(this->_fHandler, 0, SEEK_END);
    this->_size = ftell(this->_fHandler);
    fseek(this->_fHandler, 0, SEEK_SET);
}

XaloyFilestream::~XaloyFilestream()
{
    if( this->_fHandler != NULL)    {
        fclose(this->_fHandler);
        this->_fHandler = NULL;
        this->_size = 0;
    }
}

/*  BASE OPERATIONS HERE    */

void XaloyFilestream::write(const char *data, unsigned sz)
{
    assert(data != NULL);
    fwrite(data, sizeof(char), sz, this->_fHandler);
}

char *XaloyFilestream::read(unsigned offset, unsigned len)
{
    char *data = NULL;
    if (offset >= this->_size) {
        return data;
    }
    if(offset + len - 1 >= this->_size)  {
        len = this->_size - offset;
    }
    data = new char[len];
    fseek(this->_fHandler, offset, SEEK_SET);
    fread(data, sizeof(char), len, this->_fHandler);
    fseek(this->_fHandler, 0, SEEK_SET);
    return data;
}

void XaloyFilestream::flush()
{
    fflush(this->_fHandler);
}

/*  STATIC OPERATIONS HERE  */

void XaloyFilestream::copy(const string &src, const string &dst)
{
    XaloyFilestream srcFile(src, "rb"), dstFile(dst, "wb");
    char *data = srcFile.read(0, srcFile.getSize());
    dstFile.write(data, srcFile.getSize());
    delete[] data;
}

void XaloyFilestream::remove(const string &path)
{
    remove(path.c_str());
}
