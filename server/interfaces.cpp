//#include "interfaces.h"
#include "server.h"

#include <iostream>


using namespace std;


HRESULT_ __stdcall CreateInstance(const CLSID_& clsid, const IID_ & iid, void **ppv) {
    cout << "Function::CreateInstance:" << clsid << ":" << iid << endl;
    IUnknown_ *obj = NULL;
    if (clsid == CLSID_MATRIX) {
        obj = (IUnknown_*)(IMatrix*) new Matrix();
    } else  if (clsid == CLSID_MATRIXA) {
        obj = (IUnknown_*)(IMatrix*) new MatrixA();
    } else {
        *ppv = NULL;
        return E_NOCOMPONENT_;
    }
    return obj->QueryInterface(iid, ppv);
}

HRESULT_ __stdcall GetClassObject(const CLSID_& clsid, const IID_& iid, void** ppv) {
    cout << "IFactory::GetClassObject:" << clsid << ":" << iid << endl;
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
