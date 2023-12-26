#ifndef MACRO_H
#define MACRO_H

#include<windows.h>
#include <minwindef.h>

#define CHAR2LPCWSTR(charArray)  (convertCharArrayToLPCWSTR(charArray))

static wchar_t *convertCharArrayToLPCWSTR(const char *charArray) {
    auto *wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

#endif