#include "interfaces.h"
#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) HRESULT_ __stdcall DllGCO(const CLSID_& clsid, const IID_& iid, void** ppv) {
    printf("Container::DllGetClassObject\n");
    return GetClassObject(clsid, iid, ppv);
}

extern "C" __declspec(dllexport) HRESULT_ __stdcall DllCreateInstance(const CLSID_& clsid, const IID_& iid, void** ppv) {
    printf("Container::DllCreateInstance\n");
    return CreateInstance(clsid, iid, ppv);
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            printf("Container attached\n");
            break;

        case DLL_PROCESS_DETACH:
            printf("Container detached\n");
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
