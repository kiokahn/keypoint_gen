#include "graphics/sys.h"
#include <stdarg.h>
#include <stdio.h>

#include <graphics/string_manip.h>
static FILE *fp;
 
void file_log(const char *fmt, ...)
{
#ifdef __CSKETCH_DEBUG
	if (fp == 0) {
		fp = fopen("my_log.txt", "w+t");
	}
    va_list ap;

    va_start(ap, fmt);
    vfprintf(fp, fmt, ap);
    va_end(ap);
	fflush(fp);
#endif

}

#if defined(__APPLE__) || defined(LINUX)
#include <malloc.h>
void * my_memalign(size_t align, size_t sz)
{
	return memalign(align, sz);
    /* this a hack so that runlog can link with mallocs that don't have */
    /* memalign */
    void *p = malloc(sz + align + 1);
    size_t d = (unsigned long)p % align;

    if (d != 0)
        p = (char *)p + align - d;

    return p;
}
#endif
#if defined(_WINDOWS)
#include <direct.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
typedef int(*NSGetExecutablePathProcPtr)(char *buf, size_t *bufsize);
#elif defined(LINUX)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

bool make_directory(const char* directory)
{


#ifdef _WINDOWS
	if (::_mkdir(directory) == 0) return true;
	errno_t err; _get_errno(&err);
	if (err == EEXIST) return true;
#elif defined(LINUX)
	if (mkdir(directory, ~0u) == 0) return true; // I think this means all permissions..
#elif defined(__APPLE__)
	OSErr err = AddFolderDescriptor('extn', 0, 'relf', 0, 0, 0, directory.c_str(), false);
#endif // _WINDOWS

	return false;
}

int seek_file(FILE*fp, int64_t  _Offset, int _Origin)
{
#if defined(LINUX) || defined (__APPLE__)
    return fseeko(fp, _Offset, _Origin);
#else
    return _fseeki64(fp, _Offset, _Origin);
#endif
}
int64_t tell_file(FILE* fp)
{
#if defined(LINUX) || defined (__APPLE__)
    return ftello(fp);
#else
    return _ftelli64(fp);
#endif
}

bool  file_exist(const char* fname)
{
	FILE* fp = fopen(fname, "r");
	if (fp) {
		fclose(fp);
		return true;
	}
	return false;
}

bool  file_exist(const wchar_t* fname)
{
	FILE* fp;
#ifdef __WINDOWS
	fp = _wfopen(fname, L"r+b");
#else
	std::string name = graphics::to_utf8(std::wstring(fname));
	fp = fopen(name.c_str(), "r");
#endif
	if (fp) {
		fclose(fp);
		return true;
	}
	return false;
}

FILE* file_read_open(const wchar_t* fname)
{
#ifdef __WINDOWS
	return _wfopen(fname, L"r+b");
#else
    std::string name = graphics::to_utf8(std::wstring(fname));
	return fopen(name.c_str(), "r+b");
#endif
}

FILE* file_read_open(const char* fname)
{
	return fopen(fname, "r+b");

}
bool file_stream(const wchar_t* fname, char*& out, int64_t& val)
{
	FILE* fp = file_read_open(fname);
	if (!fp) return false;
	seek_file(fp, 0, SEEK_END);
	val = tell_file(fp);
	out = (char*)malloc(val);
	seek_file(fp, 0, SEEK_SET);
	fread(out, val, 1, fp);
	fclose(fp);
	return true;
}

bool file_stream(const char* fname, char*& out, int64_t& val)
{
	FILE* fp = file_read_open(fname);
	if (!fp) return false;
	seek_file(fp, 0, SEEK_END);
	val = tell_file(fp);
	out = (char*)malloc(val);
	seek_file(fp, 0, SEEK_SET);
	fread(out, val, 1, fp);
	fclose(fp);
	return true;
}
FILE* file_write_open(const wchar_t* fname)
{
#ifdef __WINDOWS
	return _wfopen(fname, L"w+b");
#else
    std::string name = graphics::to_utf8(std::wstring(fname));
	return fopen(name.c_str(), "w+b");
#endif
}

FILE* file_read_open(const wchar_t* fname, const wchar_t* mode)
{
#ifdef __WINDOWS
	return _wfopen(fname, mode);
#else
    std::string name = graphics::to_utf8(std::wstring(fname));
    std::string my_mode = graphics::to_utf8(std::wstring(mode));
	return fopen(name.c_str(), my_mode.c_str());
#endif
}

FILE* file_write_open(const wchar_t* fname, const wchar_t* mode)
{
#ifdef __WINDOWS
	return _wfopen(fname, mode);
#else
    std::string name = graphics::to_utf8(std::wstring(fname));
    std::string my_mode = graphics::to_utf8(std::wstring(mode));
    return fopen(name.c_str(), my_mode.c_str());
#endif
}

wchar_t* string_cpy(wchar_t* dest, const wchar_t* src)
{

	return wcscpy(dest, src);

}

wchar_t* string_cat(wchar_t* dest, const wchar_t* src)
{
    return wcscat(dest, src);
}

int string_cmp(const wchar_t* str1, const wchar_t* str2)
{
    return wcscmp(str1, str2);
}

