#define WIN32_LEAN_AND_MEAN // Makes Windows header smaller
#include <windows.h>       // The main Windows API header

#include <codecvt>  // For the specific converter UTF-8 <-> UTF-16
#include <iostream> // For error messages
#include <locale>   // For the conversion facets/classes
#include <string>

namespace clipboard 
{   
    bool copyStringToClipboard(const std::string& str, HWND owner_hwnd);
    bool copyWStringToWindowsClipboard(const std::wstring& text, HWND owner_hwnd);
    std::wstring stringToWstring(const std::string& str);
}