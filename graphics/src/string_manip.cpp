#include "graphics/string_manip.h"

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include "graphics/sys.h"
#include "graphics/minmax.h"
#include <locale>
#include <codecvt>
namespace graphics
{
	std::basic_string<wchar_t> ToLower(const std::basic_string<wchar_t>& source)
	{
		std::basic_string<wchar_t> target;
		for(int i=0; i<source.size(); i++)
		{
			wchar_t c = source.c_str()[i];
			if(c >= 'A' && c <= 'Z')
			{
				const wchar_t diff = 'a' - 'A';
				c += diff;
			}
			wchar_t a[2];
			a[0] = c; a[1] = L'\0';

			target.append(a);			
		}
		return target;
	}

	std::basic_string<wchar_t> ToUpper(const std::basic_string<wchar_t>& source)
	{
		std::locale loc("english");
		return std::toupper(source.c_str(), loc);
		std::basic_string<wchar_t> target;
		for(int i=0; i<source.size(); i++)
		{
			wchar_t c = source.c_str()[i];
			if(c >= 'a' && c <= 'z')
			{
				const wchar_t diff = 'a' - 'A';
				c -= diff;
			}

			wchar_t a[2];
			a[0] = c; a[1] = L'\0';
			target.append(a);
		}
		return target;
	}
	std::basic_string<char> ToLower(const std::basic_string<char>& source)
	{
		std::basic_string<char> target;
		for (int i = 0; i < source.size(); i++)
		{
			char c = source.c_str()[i];
			if (c >= 'A' && c <= 'Z')
			{
				const wchar_t diff = 'a' - 'A';
				c += diff;
			}
			char a[2];
			a[0] = c; a[1] = '\0';

			target.append(a);
		}
		return target;
	}

	std::basic_string<char> ToUpper(const std::basic_string<char>& source)
	{
		std::locale loc("english");
		return std::toupper(source.c_str(), loc);
		std::basic_string<char> target;
		for (int i = 0; i < source.size(); i++)
		{
			char c = source.c_str()[i];
			if (c >= 'a' && c <= 'z')
			{
				const char diff = 'a' - 'A';
				c -= diff;
			}

			char a[2];
			a[0] = c; a[1] = '\0';
			target.append(a);
		}
		return target;
	}
	std::basic_string<wchar_t> ReplaceAll(const std::basic_string<wchar_t> &str, const std::basic_string<wchar_t> &pattern, const std::basic_string<wchar_t> &replace)  
	{  
		std::basic_string<wchar_t> result = str;  
		std::basic_string<wchar_t>::size_type pos = 0;  
		std::basic_string<wchar_t>::size_type offset = 0;  

		while((pos = result.find(pattern, offset)) != std::basic_string<wchar_t>::npos)  
		{  
			result.replace(result.begin() + pos, result.begin() + pos + pattern.size(), replace);  
			offset = pos + replace.size();  
		}  

		return result;  
	}
	std::basic_string<char> ReplaceAll(const std::basic_string<char> &str, const std::basic_string<char> &pattern, const std::basic_string<char> &replace)
	{
		std::basic_string<char> result = str;
		std::basic_string<char>::size_type pos = 0;
		std::basic_string<char>::size_type offset = 0;

		while ((pos = result.find(pattern, offset)) != std::basic_string<char>::npos)
		{
			result.replace(result.begin() + pos, result.begin() + pos + pattern.size(), replace);
			offset = pos + replace.size();
		}

		return result;
	}
	std::vector<std::basic_string<wchar_t>> Split(const std::basic_string<wchar_t> &str, const std::basic_string<wchar_t> &pattern)  
	{ 

		std::basic_string<wchar_t>::size_type pos = 0;  
		std::basic_string<wchar_t>::size_type offset = 0;  
		
		std::vector<std::basic_string<wchar_t>::size_type> offsets;
		while((pos = str.find(pattern, offset)) != std::basic_string<wchar_t>::npos)  
		{
			offsets.push_back(offset);
			offset = pos+1;
		}

		std::vector<std::basic_string<wchar_t>> split_string;
		for(int i=0; i<offsets.size(); i++)
		{
			int begin_offset = offsets[i];
			int end_offset(0);
			if(i == offsets.size()-1)
				end_offset = str.size();
			else
				end_offset = offsets[i+1];

			std::basic_string<wchar_t> sub = str.substr(begin_offset, end_offset-begin_offset);
			split_string.push_back(sub);
		}
		return split_string;
	}

	// c:\a\b.txt -> c:/a/
	// c:\a\b\c\d -> c:/a/b/c
	std::basic_string<wchar_t> GetDirectoryPath(const std::basic_string<wchar_t>& path)
	{		
		int lastSlash = path.rfind(L'/');
		int lastBackslash = path.rfind(L'\\');
		lastSlash = max(lastSlash, lastBackslash);
		if(lastSlash == std::basic_string<wchar_t>::npos)
			lastSlash = 0;
		else
			lastSlash += 1;

		std::basic_string<wchar_t> a;
		a.append(path, 0, lastSlash);
		a = ReplaceAll(a, L"\\", L"/");
		return a;
	}

	std::basic_string<wchar_t> GetPathLeafName(const std::basic_string<wchar_t>& path)
	{
		int lastSlash = path.rfind(L'/');
		int lastBackslash = path.rfind(L'\\');
		lastSlash = max(lastSlash, lastBackslash);
		if(lastSlash == std::basic_string<wchar_t>::npos)
			lastSlash = 0;
		else
			lastSlash += 1;

		std::basic_string<wchar_t> a;
		a.append(path, lastSlash, path.size());
		return a;
	}
	// c:\a\b.txt -> c:/a/
		// c:\a\b\c\d -> c:/a/b/c 
	std::basic_string<char> GetDirectoryPath(const std::basic_string<char>& path)
	{
		int lastSlash = path.rfind('/');
		int lastBackslash = path.rfind('\\');
		lastSlash = max(lastSlash, lastBackslash);
		if (lastSlash == std::basic_string<char>::npos)
			lastSlash = 0;
		else
			lastSlash += 1;

		std::basic_string<char> a;
		a.append(path, 0, lastSlash);
		a = ReplaceAll(a, "\\", "/");
		return a;
	}

	std::basic_string<char> GetPathLeafName(const std::basic_string<char>& path)
	{
		int lastSlash = path.rfind('/');
		int lastBackslash = path.rfind('\\');
		lastSlash = max(lastSlash, lastBackslash);
		if (lastSlash == std::basic_string<wchar_t>::npos)
			lastSlash = 0;
		else
			lastSlash += 1;
		 
		std::basic_string<char> a;
		a.append(path, lastSlash, path.size());
		return a;
	}

	void SeparateNameAndExt(const std::basic_string<wchar_t>& path, std::basic_string<wchar_t>& name, std::basic_string<wchar_t>& ext)
	{
		std::basic_string<wchar_t> filename = GetPathLeafName(path);
		name.clear();
		ext.clear();

		int lastDot = filename.rfind(L'.');		
		if(lastDot == std::basic_string<wchar_t>::npos)
			lastDot = filename.size();		
		
		name.append(filename, 0, lastDot);
		ext.append(filename, lastDot, filename.size() - lastDot);		
	}

	void SeparateNameAndExt(const std::basic_string<char>& path, std::basic_string<char>& name, std::basic_string<char>& ext)
	{
		std::basic_string<char> filename = GetPathLeafName(path);
		name.clear();
		ext.clear();

		int lastDot = filename.rfind('.');
		if (lastDot == std::basic_string<wchar_t>::npos)
			lastDot = filename.size();

		name.append(filename, 0, lastDot);
		ext.append(filename, lastDot, filename.size() - lastDot);
	}

	std::basic_string<wchar_t> AbsolutePathToRelativePath(const std::basic_string<wchar_t>& absolutePath, const std::basic_string<wchar_t>& targetPath)
	{
		return L""; 

		// validation
		// targetPath must be absolute path. if it starts with . or .. then it is related path, so it can not be transformed.
		if(targetPath[0] == '.' || targetPath[1] == '.')
			return L""; // return empty string.

		std::basic_string<wchar_t> abPath = ToLower(ReplaceAll(absolutePath, L"\\", L"/"));
		std::basic_string<wchar_t> tarPath = ToLower(ReplaceAll(targetPath, L"\\", L"/"));

		std::vector<std::basic_string<wchar_t>> abPathDirs = Split(abPath, L"/");		
		std::vector<std::basic_string<wchar_t>> tarPathDirs = Split(tarPath, L"/");		

		int i(0);
		for( ; i < min(abPathDirs.size(), tarPathDirs.size()) ; i++)
		{
			if(abPathDirs[i] != tarPathDirs[i])
				break;
		}
	}

	void get_tokens(std::string input, std::vector<std::string>& tokens, const char* sep)
	{
		char separator[100];
		strcpy(separator, sep);
		int n = strlen(separator);
#ifdef LINUX
		if (separator[n - 1] == '\n')
			strcat(separator, "\r");
#endif
		tokens.clear();
		char *    token;
		token = strtok(const_cast<char*>(input.c_str()), separator);
		while (token != NULL) {
			tokens.push_back(std::string(token));
			token = strtok(NULL, separator);
		}
	}
	void get_tokens(std::wstring input, std::vector<std::wstring>& tokens, const wchar_t* sep)
	{
		wchar_t separator[100];
		wcscpy(separator, sep);
#ifdef LINUX
		int n = wcslen(separator);
		if (separator[n - 1] == L'\n')
			wcscat(separator, L"\r");
#endif
		tokens.clear();
		wchar_t	*	temp; 
		wchar_t *   token;
		token = wcstok(const_cast<wchar_t*>(input.c_str()), separator, &temp);
		while (token != NULL) {
			tokens.push_back(std::wstring(token));
			token = wcstok(NULL, separator, &temp);
		}
	}
	void separate_string(std::string input, std::string& out1, std::string& out2, const char* delim)
	{
		size_t pos = input.find(delim);
		if (pos != input.npos) {
			std::string t1 = input.substr(0, pos);
			stripoff_blank(t1, out1);

			t1 = input.substr(pos);
			stripoff_blank(t1, out2);
		}
	}

	void stripoff_blank(std::string& input, std::string& out)
	{
		size_t pos1 = input.npos, pos2 = input.npos;
		for (int i = 0 ; i < input.size() ; i++) {
			if (input[i] == ' ' || input[i] == '\t') {
				pos1 = i;
			}
			if (input[i] != ' ' && input[i] != '\t') break;
		}
		for (int i = input.size()-1 ; i >= 0 ; i--) {
			if (input[i] == ' ') {
				pos2 = i;
			}
			if (input[i] != ' ') break;
		}

		//if (pos2 < pos1) {
		//	out.resize(0);
		//	//out[0] = input[0];
		//	return;
		//}
		if (pos1 == input.npos) {
			pos1 = 0;
		} else {
			pos1++;
		}

		if (pos2 == input.npos) {
			pos2 = input.size()-1;
		} else {
			pos2--;
		}
		if (pos2 > 100000000) { out = input; return; }
		if (pos2 - pos1 + 1 < 0)
			out.resize(0);
		else
			out.resize(pos2-pos1+1);
		for (int i = 0 ; i < out.size() ; i++)
			out[i] = input[pos1+i];
	}



	std::string to_utf8(const std::wstring& input)
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(input);
	}
	std::wstring to_utf16(const std::string& input)
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(input);
	}
}