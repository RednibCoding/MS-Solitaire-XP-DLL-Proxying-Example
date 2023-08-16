// Include necessary headers
#include <iostream>  // For input-output operations (used for printf here)
#include <windows.h> // For Windows API functions

// Define a macro for external DLL export, which tells the compiler that the function is intended to be exposed 
// outside of the DLL, so other applications or DLLs can call it.
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

// Define a function pointer type for the original cdtInit function
// This pointer will be used to call the original function from the real cards.dll (now renamed cards_og.dll)
typedef BOOL(WINAPI* cdtInitPtr)(int* width, int* height);

// DllMain is a special function that's called when a DLL is loaded into or unloaded from memory.
EXTERN_DLL_EXPORT BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: // Called when DLL is loaded into a process's memory space
    case DLL_PROCESS_DETACH: // Called when DLL is unloaded from a process's memory space
    case DLL_THREAD_ATTACH:  // Called when a thread is created within a process that has this DLL loaded
    case DLL_THREAD_DETACH:  // Called when a thread is destroyed within a process that has this DLL loaded
        break;
    default: // Handle any other reasons, although generally not used
        break;
    }
    // Return TRUE to allow the DLL to load, otherwise returning FALSE would prevent it from loading
    return TRUE;
}

// This is our modified version of the cdtInit function
EXTERN_DLL_EXPORT BOOL cdtInit(int* width, int* height) {
    // Load the original cards.dll (now renamed to cards_og.dll) into memory
    HINSTANCE cards_og_Dll = LoadLibrary(TEXT("cards_og.dll"));

    // Check if the original DLL loaded successfully
    if (!cards_og_Dll) {
        // Print an error message if failed to load, showing the error code
        printf("Failed to load cards_og.dll with error code: 0x%x\n", GetLastError());
        return FALSE;
    }

    // Get the address of the original cdtInit function from cards_og.dll
    cdtInitPtr cdtInit_og_function = (cdtInitPtr)GetProcAddress(cards_og_Dll, "cdtInit");

    // Check if we successfully retrieved the address of the original function
    if (!cdtInit_og_function) {
        // Print an error message if failed to retrieve, showing the error code
        printf("Failed to find cdtInit function in cards_og.dll with error code: 0x%x\n", GetLastError());
        return FALSE;
    }

    /**** Start Weaponized Code ****/
    // Any malicious or modified code you want to run before calling the original function goes here

    /**** End Weaponized code ****/

    // Call the original cdtInit function from cards_og.dll using our function pointer
    BOOL result = cdtInit_og_function(width, height);

    // Free the loaded original cards_og.dll from memory. Important to release resources!
    FreeLibrary(cards_og_Dll);

    // Return the result from the original function to the caller
    return result;
}
