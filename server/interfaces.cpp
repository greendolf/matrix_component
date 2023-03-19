//#include "interfaces.h"
#include "server.h"

#include <iostream>


using namespace std;


HRESULT_ __stdcall CreateInstance(const CLSID_& clsid, const IID_ & iid, void **ppv) {
    cout << "Function::CreateInstance:" << clsid << ":" << iid << endl;
    IUnknown_ *obj = NULL;
    if (clsid == CLSID_MATRIX) {
        obj = (IUnknown_*)(IMatrix*) new Matrix();
        if (obj == NULL) {
            return E_OUTOFMEMORY_;
        }
    } else {
        *ppv = NULL;
        return E_NOCOMPONENT_;
    }
    return obj->QueryInterface(iid, ppv);
}