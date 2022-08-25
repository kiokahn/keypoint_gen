#ifndef __unsigned_h
#define __unsigned_h


typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned int uint;

#ifdef LINUX
#include <stdint.h>
typedef uint64_t uint64;
#else
typedef unsigned long long uint64;
#endif 

typedef signed char schar;


#endif
