#include <iostream>
#include <windows.h>

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

// Ptr to the original cdtInit function
typedef BOOL(WINAPI* cdtInitPtr)(int* width, int* height);

EXTERN_DLL_EXPORT BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    {
        switch (ul_reason_for_call)
        {
        case DLL_PROCESS_ATTACH:
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
        default:
            break;
        }
        return TRUE;
    }
}

EXTERN_DLL_EXPORT BOOL cdtInit(int* width, int* height) {
    HINSTANCE cards_og_Dll = LoadLibrary(TEXT("cards_og.dll"));
    if (!cards_og_Dll) {
        printf("Format messaged failed with 0x%x\n", GetLastError());
        return FALSE;
    }

    cdtInitPtr cdtInit_og_function = (cdtInitPtr)GetProcAddress(cards_og_Dll, "cdtInit");

    if (!cdtInit_og_function) {
        printf("Format messaged failed with 0x%x\n", GetLastError());
        return FALSE;
    }

    /**** Start Weaponized Code ****/

    /**** End Weaponized code ****/

    // Call the og function
    BOOL result = cdtInit_og_function(width, height);
    FreeLibrary(cards_og_Dll);

    return result;
}