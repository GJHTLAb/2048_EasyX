#pragma once

#include <string>
#include <graphics.h>

using namespace std;

string TCHARToString(const TCHAR* tcharStr) {
#ifdef UNICODE
	int size = WideCharToMultiByte(CP_UTF8, 0, tcharStr, -1, nullptr, 0, nullptr, nullptr);
	char* buffer = new char[size];
	WideCharToMultiByte(CP_UTF8, 0, tcharStr, -1, buffer, size, nullptr, nullptr);
	string str(buffer);
	delete[] buffer;
	return str;
#else
	return string(tcharStr);
#endif
}

TCHAR* StringToTCHAR(const string& str) {
#ifdef UNICODE
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	wchar_t* buffer = new wchar_t[size];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, size);
	return buffer;
#else 
	return _strdup(str.c_str());
#endif;
}