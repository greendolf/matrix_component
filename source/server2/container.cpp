//#include "interfaces.h"
#include "component.h"
//#include <windows.h>
#include <stdio.h>



extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID &clsid, const IID &iid, void **ppv)
{
    printf("IncludedComponent::GetClassObject:\n");

    IUnknown *obj = NULL;

    if (clsid == Constants::CLSID_Matrix)
    {
        obj = (IUnknown *)(IClassFactory *)new Factory();
    }
    else if (obj == NULL)
    {
        return E_NOTIMPL;
    }
    return obj->QueryInterface(iid, ppv);
}

extern "C" __declspec(dllexport) HRESULT __stdcall DllCreateInstance(const CLSID &clsid, const IID &iid, void **ppv)
{
    printf("IncludedComponent::CreateInstance:\n");

    IClassFactory *F = NULL;
    DllGetClassObject(clsid, Constants::IID_IClassFactory, (void **)&F);

    HRESULT res = F->CreateInstance(NULL, iid, ppv);

    F->Release();

    return res;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        printf("Included container attached\n");
        break;

    case DLL_PROCESS_DETACH:
        printf("Included container detached\n");
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
