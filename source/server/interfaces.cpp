//#include "interfaces.h"
#include "component.h"

#include <iostream>


using namespace std;


HRESULT_ __stdcall CreateInstance(const CLSID_& clsid, const IID_ & iid, void **ppv) {
    cout << "Component::CreateInstance:" << clsid << ":" << iid << endl;

    IFactory *F = NULL;
    GetClassObject(clsid, IID_IFactory, (void**) &F);

    HRESULT_ res = F->CreateInstance(iid, ppv);

    F->Release();
    
    return res;
}

HRESULT_ __stdcall GetClassObject(const CLSID_& clsid, const IID_& iid, void** ppv) {
    cout << "Component::GetClassObject:" << clsid << ":" << iid << endl;

    IUnknown_ *obj = NULL;

    if (clsid == CLSID_Factory) {
        obj = (IUnknown_*)(IFactory*) new Factory();
    } else if (clsid == CLSID_FactoryA) {
        obj = (IUnknown_*)(IFactoryA*) new FactoryA();
    } else if (obj == NULL) {
        return E_NOCOMPONENT_;
    }
    return obj->QueryInterface(iid, ppv);
}
