﻿#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:\"mainCRTStartup\"")

#include <tchar.h>
#include <Windows.h>

int main(int argc, char *argv[])
{
#if defined(_WIN64) && defined(_DEBUG)
    HINSTANCE hDll = LoadLibrary(TEXT("Sugoi64d.dll"));
#elif defined(_WIN64) && !defined(_DEBUG)
    HINSTANCE hDll = LoadLibrary(_T("Sugoi64.dll"));
#elif !defined(_WIN64) && defined(_DEBUG)
    HINSTANCE hDll = LoadLibrary(_T("Sugoid.dll"));
#elif !defined(_WIN64) && !defined(_DEBUG)
    HINSTANCE hDll = LoadLibrary(_T("Sugoi.dll"));
#endif
    int ret = -1;
    if (hDll != nullptr)
    {
        typedef int(*playerApp)(int, char *[]);
        playerApp app = (playerApp)GetProcAddress(hDll, "sugoiAppMain");
        ret = app(argc, argv);
        FreeLibrary(hDll);
    }
    else
    {
        MessageBox(nullptr, TEXT("Failed to load dll. Contact with the developers for more details."), TEXT("Error"), MB_OK | MB_ICONERROR);
    }
    return ret;
}
