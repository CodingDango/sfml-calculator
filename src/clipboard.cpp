#include "clipboard.hpp"


bool clipboard::copyStringToClipboard(const std::string& str, HWND owner_hwnd)
{   
    const std::wstring w_str = clipboard::stringToWstring(str);
    return copyWStringToWindowsClipboard(w_str, owner_hwnd);
}

bool clipboard::copyWStringToWindowsClipboard(const std::wstring& text, HWND owner_hwnd)
{
    // 1. Try to gain access to the clipboard. Only one program
    //    can access it at a time. Needs the window handle (HWND).
    if (!OpenClipboard(owner_hwnd)) {
        std::cerr << "Error: Cannot open clipboard.\n";
        return false; // Failed
    }

    // 2. Clear whatever was on the clipboard before.
    if (!EmptyClipboard()) {
        std::cerr << "Error: Cannot empty clipboard.\n";
        CloseClipboard(); // IMPORTANT: Always close if you opened it!
        return false; // Failed
    }

    // 3. Allocate special Windows memory for the text.
    //    The +1 is for the hidden null character that marks the end of the text.
    size_t buffer_size_bytes = (text.length() + 1) * sizeof(wchar_t);
    HGLOBAL hGlobalMemory = GlobalAlloc(GMEM_MOVEABLE, buffer_size_bytes); // Ask Windows for memory
    if (hGlobalMemory == NULL) {
        std::cerr << "Error: Cannot allocate memory for clipboard.\n";
        CloseClipboard(); // Close before exiting
        return false; // Failed
    }

    // 4. "Lock" the memory to get a pointer we can write to.
    LPVOID pLockedMemory = GlobalLock(hGlobalMemory);
    if (pLockedMemory == NULL) {
        std::cerr << "Error: Cannot lock memory for clipboard.\n";
        GlobalFree(hGlobalMemory); // Need to free memory if Lock fails
        CloseClipboard();
        return false; // Failed
    }

    // 5. Copy the actual text data into that Windows memory.
    memcpy(pLockedMemory, text.c_str(), buffer_size_bytes);

    // 6. "Unlock" the memory.
    GlobalUnlock(hGlobalMemory);

    // 7. Give the memory handle to Windows to put on the clipboard.
    //    CF_UNICODETEXT tells Windows the data is in the wstring format.
    //    IMPORTANT: If this works, Windows now OWNS the memory. We DON'T free it.
    if (SetClipboardData(CF_UNICODETEXT, hGlobalMemory) == NULL) {
        std::cerr << "Error: Cannot set clipboard data.\n";
        // If it failed, Windows did NOT take ownership, so WE must free it.
        GlobalFree(hGlobalMemory);
        CloseClipboard();
        return false; // Failed
    }

    // 8. Release access to the clipboard.
    CloseClipboard();

    return true; // Success!
}

std::wstring clipboard::stringToWstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    try {
         // Do the conversion
         return converter.from_bytes(str);
    } catch(const std::range_error& e) {
         // Handle potential errors if the input string isn't valid UTF-8
         std::cerr << "Warning: String to Wstring conversion error: " << e.what() << std::endl;
         // Return an empty wstring or some default on error
         return L""; // L"" is an empty wide string
    }
    // Note: wstring_convert is technically deprecated in C++17, but it's widely used
    // and often the simplest way for this task without bringing in large libraries.
}
