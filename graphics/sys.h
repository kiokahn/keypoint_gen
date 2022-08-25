#ifndef __sys_h
#define __sys_h

#include <stdint.h>
#include <stdio.h>
//#include <inttypes.h>
#if defined(_WINDOWS)
#include <windows.h>
#include <conio.h>

#define LOG _cprintf
void file_log(const char *fmt, ...);

#elif defined(LINUX)

#include <stdio.h>

#define LOG printf

void file_log(const char *fmt, ...);

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <ucontext.h>
#include <string.h>
#include <wchar.h>

#endif


#ifdef _WINDOWS
#include  "GL/glew.h"
#include  <GL/gl.h>
#include  <GL/glu.h>
#include  <GL/glext.h>


#elif defined(LINUX)
#include  "GL/glew.h"
#include  <GL/gl.h>
#include  <GL/glu.h>
#include  <GL/glext.h>

#elif defined(__APPLE__)

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include <stdio.h>

#ifdef LINUX

#define	LOG printf

#endif

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#define FLOG fprintf


#if defined(__APPLE__) || defined(LINUX)

void * my_memalign(size_t align, size_t sz);

#endif

int seek_file(FILE*fp, int64_t  _Offset, int _Origin);
int64_t tell_file(FILE* fp);


bool make_directory(const char* directory);

FILE* file_read_open(const wchar_t* fname);
FILE* file_read_open(const char* fname);
FILE* file_write_open(const wchar_t* fname);
bool  file_exist(const char* fname);
bool  file_exist(const wchar_t* fname);
FILE* file_read_open(const wchar_t* fname, const wchar_t* mode);
FILE* file_write_open(const wchar_t* fname, const wchar_t* mode);

bool file_stream(const wchar_t* fname, char*& out, int64_t& val);
bool file_stream(const char* fname, char*& out, int64_t& val);
wchar_t* string_cpy(wchar_t* dest, const wchar_t* src);
wchar_t* string_cat(wchar_t* dest, const wchar_t* src);
int    string_cmp(const wchar_t* str1, const wchar_t* str2);

#endif


//#ifndef	GL_RADEON
//#define GL_RADEON
//#endif
