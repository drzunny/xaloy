/*=============================================================================
#     FileName: common.cc
#         Desc: common methods' implements
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.3.0
#   LastChange: 2013-01-28 15:33:00
#      History:
=============================================================================*/

#include "common.h"

#include <memory.h>

#include <cstdio>
#include <cassert>
#include <cstdlib>

using namespace xaloy;
using namespace std;

/*      helper functions        */

/*      common methods without md5      */
XaloyCommon::XaloyCommon()
{
    this->reset_seed();
}

XaloyCommon::~XaloyCommon()
{
    this->_rSeed = 0;
}

// random
void XaloyCommon::reset_seed()
{
    this->_rSeed = (unsigned)time(0);
    srand(this->_rSeed);
}
int XaloyCommon::random(unsigned start, unsigned end)
{
    assert(start < end);
    return start + rand() % (end - start + 1);    
}
double XaloyCommon::random_f()
{
    return (double)rand() / RAND_MAX;
}

// hash
unsigned XaloyCommon::getHash(const string &s)
{
    const char *str = s.c_str();
    unsigned hash = XALOY_HASH_SEED;
    while(*str)   {
        hash = ((hash) <<7 + hash) + (*str);
        str++;
    }
    return hash;
}

// datetime
XDateInfo XaloyCommon::now(bool isDetail)
{
    XDateInfo dinfo;
    time_t rawtime;
    struct tm *timeInfo = NULL;
    memset(dinfo.timeString, 0, 20);
    time(&rawtime);
    timeInfo = localtime(&rawtime);
    if (isDetail) {
        sprintf(dinfo.timeString, "%04d-%02d-%02d %02d:%02d:%02d",
                1900 + timeInfo->tm_year,
                1 + timeInfo->tm_mon,
                timeInfo->tm_mday,
                timeInfo->tm_hour,
                timeInfo->tm_min,
                timeInfo->tm_sec
        );
    }   else    {
        sprintf(dinfo.timeString, "%04d-%02d-%02d",
                1900 + timeInfo->tm_year,
                1 + timeInfo->tm_mon,
                timeInfo->tm_mday
        );
    }
    dinfo.tick = rawtime;
    return dinfo;
}

/*      MD5 implement start here    */
static const char 
PADDING_CHAR[64] = {0x80};

static const char 
HEX_CHAR[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
};

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + ac; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + ac; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + ac; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + ac; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

struct md5Context {
    unsigned long state[4];
    unsigned long counter[2];
    char buffer[64];
    char digi[16];
    int isdone;
};

/*      md5 object helpers      */

static int
md5_encode(const struct md5Context *ctx, const unsigned long *input, char *output, unsigned sz) {
    unsigned i, j;
	if(ctx == NULL || input == NULL)
		return 0;
    for (i = 0, j = 0; i < sz; i++, j+=4) {
        output[j]= (char)(input[i] & 0xff);
		output[j+1] = (char)((input[i] >> 8) & 0xff);
		output[j+2] = (char)((input[i] >> 16) & 0xff);
		output[j+3] = (char)((input[i] >> 24) & 0xff);        
    }
	return 1;
}

static int
md5_decode(const struct md5Context *ctx, const char *input, unsigned long *output, unsigned sz) {
    unsigned i, j;
	if(ctx == NULL || input == NULL)
		return 0;
    for (i = 0, j = 0; j < sz; i++, j+=4) {
        output[i] = ((unsigned long)input[j]) | (((unsigned long)input[j+1]) << 8) |
            (((unsigned long)input[j+2]) << 16) | (((unsigned long)input[j+3]) << 24);        
    }
	return 1;
}

static void
md5_trans(struct md5Context *ctx, const char block[64]) {
    unsigned long a = ctx->state[0], b = ctx->state[1], c = ctx->state[2], d = ctx->state[3], x[16];
    
    if(block == NULL)
        block = ctx->buffer;
    md5_decode(ctx, block, x, 64);
    /* Round 1 */
	FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
	FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
	FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
	FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
	FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
	FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
	FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
	FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
	FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
	FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
	FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
	FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
	FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
	FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
	FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
	FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
	
    /* Round 2 */
	GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
	GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
	GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
	GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
	GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
	GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
	GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
	GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
	GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
	GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
	GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
	GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
	GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
	GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
	
    /* Round 3 */
	HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
	HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
	HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
	HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
	HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
	HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
	HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
	HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
	HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
	HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
	HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
	HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
	HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
	HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
	HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
	HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
	
    /* Round 4 */
	II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
	II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
	II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
	II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
	II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
	II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
	II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
	II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
	II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
	II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
	II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
	II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
	II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
	II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
	II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
	II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
}

static void
md5_update(struct md5Context *ctx, const char *buffer, unsigned sz) {
    unsigned long i, idx, plen;
    ctx->isdone = 0;

    idx = (unsigned long)(((unsigned long)ctx->counter[0] >> 3) & 0x3f);
    
    if ((ctx->counter[0] += ((unsigned long)sz << 3)) < ((unsigned long)sz << 3)) { 
       ctx->counter[1]++;
    }
    ctx->counter[1] += ((unsigned long)sz >> 29);

    plen = 64 - idx;

    if (sz >= plen) {
        memcpy(&ctx->buffer[idx], buffer, plen);
        md5_trans(ctx, NULL);

        for (i = plen; i + 63 < sz; i += 64) {
            md5_trans(ctx, &buffer[i]);
        }
        idx = 0;
    }   else    {
        i = 0;
    }
    memcpy(&ctx->buffer[idx], &buffer[i], sz - i);
}

struct md5Context *
md5_init(const char *filepath)    {
    struct md5Context *ctx = NULL;
	FILE *f = NULL;
	char fbuffer[1024];
	unsigned blen = 0;
	assert(filepath != NULL);

	/*	open the file	*/
	f = fopen(filepath, "rb");
	if(f == NULL)
		return NULL;

	/*	allocate the md5 context	*/
	ctx = (struct md5Context *)malloc(sizeof(struct md5Context));
    ctx->isdone = 0;

    /*   initalize the state   */
    ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;

    /*   initalize the counter   */
    ctx->counter[0] = ctx->counter[1] = 0;

	/*	read data bytes and update	*/
	do
	{
		blen = fread(fbuffer, sizeof(char), 1024, f);
		md5_update(ctx, fbuffer, blen);
	}while(blen != 0);

    fclose(f);
    return ctx;
}

static void
md5_prepare(struct md5Context *ctx)   {
    char bits[8];
    unsigned long oState[4], oCounter[2], idx, plen;

    memcpy(oState, ctx->state, 16);
    memcpy(oCounter, ctx->counter, 8);

    //md5_encode(ctx, ctx->counter, bits, 8);
	md5_encode(ctx, ctx->counter, bits, 2);  /* sizeof(ctx->counter)/sizeof(ctx->counter[0]) == 2 */

    idx = (unsigned long)((ctx->counter[0] >> 3) & 0x3f);
    plen = (idx < 56) ? (56 - idx) : (120 - idx);
    md5_update(ctx, PADDING_CHAR, plen);
    md5_update(ctx, bits, 8);

    //md5_encode(ctx, ctx->state, ctx->digi, 16);
    md5_encode(ctx, ctx->state, ctx->digi, 4); /* sizeof(ctx->state)/sizeof(ctx->state[0]) == 4 */
 
    memcpy(ctx->state, oState, 16);
    memcpy(ctx->counter, oCounter, 8);
}

static const char *
md5_getdigit(struct md5Context *ctx)  {
	if(ctx->isdone != 1)		{
		ctx->isdone = 1;
		md5_prepare(ctx);
	}
    return ctx->digi;
}

static char *
md5_getstring(struct md5Context *ctx) {
    char *s = NULL;
    unsigned len = sizeof(ctx->digi);
    const char *source = md5_getdigit(ctx);
    unsigned allocSize = len << 1;
    unsigned i, j, t, a, b;
    assert(source != NULL);

    /*  allocate the char array */
    s = (char*)malloc(allocSize + 1);		// allocSize == strlen
	memset(s, 0, allocSize + 1);
    if (s == NULL) {
        return NULL;
    }
    memset(s, 0, (len << 1));

    j = 0;
    for (i = 0; i < len; i++) {
        t = (unsigned char)source[i];
        a = t / 16;
        b = t % 16;
        s[j++] = HEX_CHAR[a];
        s[j++] = HEX_CHAR[b];
    }
    return s;
}

/* ---------------   the real XaloyCommon::md5 implement  ------------------------- */
string XaloyCommon::md5(const string &path)
{
    string s("");
    char *md5str = NULL;
    struct md5Context *md5ctx = NULL;
    if (path.empty())
        return s;
    md5ctx = md5_init(path.c_str());
    if (md5ctx == NULL)
        return s;
    md5str = md5_getstring(md5ctx);
    s.append(md5str);
    free(md5str);
    free(md5ctx);
    md5ctx = NULL;
    md5str = NULL;
    return s;
}

