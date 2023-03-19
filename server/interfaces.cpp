//#include "interfaces.h"
#include "server.h"

#include <iostream>


using namespace std;


HRESULT_ __stdcall CreateInstance(const IID_ & iid, void **ppv) {
    cout << "Function::CreateInstance" << endl;
    if (iid == IID_IMatrix) {
        IUnknown_ *obj = (IUnknown_*)(IMatrix*)new Matrix();
        if (obj == NULL) {
            return E_OUTOFMEMORY_;
        }
        obj->AddRef();
        *ppv = obj;
        return S_OK_;
    }
    else if (iid == IID_IMatrixA) {
        IUnknown_ *obj = (IUnknown_*)(IMatrixA*)new Matrix();
        if (obj == NULL) {
            return E_OUTOFMEMORY_;
        }
        obj->AddRef();
        *ppv = obj;
        return S_OK_;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE_;
    }
}