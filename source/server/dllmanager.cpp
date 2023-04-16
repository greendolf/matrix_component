#include <windows.h>
#include <stdio.h>

using CLSID_ = int;
using IID_ = int;
using HRESULT_ = int;
using ULONG_ = int;

typedef HRESULT __stdcall (*FunctionType) (const CLSID_& clsid, const IID_& iid, void** ppv);

HINSTANCE h;

extern "C" __declspec(dllexport) HRESULT GetClassObject(const CLSID_& clsid, const IID_& iid, void** ppv) {
    printf("Manager::GetClassObject\n");

    try {
        FunctionType GCO;
        
        h=LoadLibrary("./build/server/component.dll");

        if (!h) {
            printf("!\n");
            throw "";
        }

        GCO = (FunctionType) GetProcAddress(h, "DllGCO");

        if (!GCO) {
            printf("!!\n");
            throw "";
        }
        return GCO(clsid, iid, ppv);
    }
    catch (...) {
        return E_UNEXPECTED;
    }
}

extern "C" __declspec(dllexport) HRESULT CreateInstance(const CLSID_& clsid, const IID_& iid, void** ppv) {
    printf("Manager::CreateInstance\n");

    try {
        FunctionType CI;

        h=LoadLibrary("./build/server/component.dll");

        if (!h) {
            printf("!\n");
            throw "";
        }

        CI = (FunctionType) GetProcAddress(h, "DllCreateInstance");

        if (!CI) {
            printf("!!\n");
            throw "";
        }

        return CI(clsid, iid, ppv);
    }
    catch (...) {
        return E_UNEXPECTED;
    }
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            printf("Manager attached\n");
            break;

        case DLL_PROCESS_DETACH:
            FreeLibrary(h);
            printf("Manager detached\n");
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
