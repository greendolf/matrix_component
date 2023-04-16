#include <stdio.h>
#include "wrapper.h"

EMatrix::EMatrix(const char* msg) {
    this->msg = msg;
}

const char* EMatrix::GetMessage() {
    return msg;
}


CMatrix::CMatrix() {
    IFactory *IF = NULL;

    printf("Wrapper::GetClassObject\n");

    FunctionType GCO;

    h = LoadLibrary("./build/client/dllmanager.dll");

    if (!h) {
        printf("!\n");
        throw EMatrix("Error while creating CMatrix: No dll");;
    }

    GCO = (FunctionType) GetProcAddress(h, "GetClassObject");

    if (!GCO) {
        printf("!!\n");
        throw EMatrix("Error while creating CMatrix: No function");
    }

    HRESULT_ res = GCO(CLSID_Factory, IID_IFactory, (void**) &IF);

    if (res == E_NOCOMPONENT_) {
        throw EMatrix("Error while creating CMatrix: Unsupported component");
    }
    else if (res == E_NOINTERFACE_) {
        throw EMatrix("Error while creating CMatrix: Unsupported interface");
    }
    else if (res != S_OK_) {
        throw EMatrix("Error while creating CMatrix: Unknown error");
    }

    res = IF->CreateInstance(IID_IMatrix, (void**) &IM);
    if (res == S_OK_) { IF->Release(); }
    else { throw EMatrix("Error while creating CMatrix: Unsupported interface"); }
}

HRESULT_ __stdcall CMatrix::AddMatrixNum(double *a, double b, double *c, int n, int m) {
    return IM->AddMatrixNum(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrix::SubMatrixNum(double *a, double b, double *c, int n, int m) {
    return IM->SubMatrixNum(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrix::MultMatrixNum(double *a, double b, double *c, int n, int m) {
    return IM->MultMatrixNum(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrix::DivMatrixNum(double *a, double b, double *c, int n, int m) {
    return IM->DivMatrixNum(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrix::DetMatrix(double *a, double *det, int n) {
    return IM->DetMatrix(a, det, n);
}

CMatrix::~CMatrix() {
    IM->Release();
    FreeLibrary(h);
}

CMatrixA::CMatrixA() {
    IFactory *IF = NULL;

    printf("Wrapper::GetClassObject\n");

    FunctionType GCO;

    h = LoadLibrary("./build/client/dllmanager.dll");

    if (!h) {
        printf("!\n");
        throw EMatrix("Error while creating CMatrix: No dll");;
    }

    GCO = (FunctionType) GetProcAddress(h, "GetClassObject");

    if (!GCO) {
        printf("!!\n");
        throw EMatrix("Error while creating CMatrix: No function");
    }

    HRESULT_ res = GCO(CLSID_FactoryA, IID_IFactory, (void**) &IF);

    if (res == E_NOCOMPONENT_) {
        throw EMatrix("Error while creating CMatrixA: Unsupported component");
    }
    else if (res == E_NOINTERFACE_) {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }
    else if (res != S_OK_) {
        throw EMatrix("Error while creating CMatrixA: Unknown error");
    }

    res = IF->CreateInstance(IID_IMatrix, (void**) &IM);
    if (res == E_NOINTERFACE_) {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }

    res = IF->CreateInstance(IID_IMatrixA, (void**) &IMA);
    if (res == E_NOINTERFACE_) {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }

    IF->Release();
}

HRESULT_ __stdcall CMatrixA::AddMatrixNum(double *a, double b, double *c, int n, int m) {
    return IM->AddMatrixNum(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrixA::SubMatrixNum(double *a, double b, double *c, int n, int m) {
    return IM->SubMatrixNum(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrixA::MultMatrixNum(double *a, double b, double *c, int n, int m) {
    return IM->MultMatrixNum(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrixA::DivMatrixNum(double *a, double b, double *c, int n, int m) {
    return IM->DivMatrixNum(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrixA::DetMatrix(double *a, double *det, int n) {
    return IM->DetMatrix(a, det, n);
}


HRESULT_ __stdcall CMatrixA::AddMatrix(double *a, double *b, double *c, int n, int m) {
    return IMA->AddMatrix(a, b, c, n, m);
}

HRESULT_ __stdcall CMatrixA::MultMatrix(double *a, double *b, double *c, int n, int m, int p) {
    return IMA->MultMatrix(a, b, c, n, m, p);
}

HRESULT_ __stdcall CMatrixA::TransMatrix(double *a, double *b, int n) {
    return IMA->TransMatrix(a, b, n);
}

HRESULT_ __stdcall CMatrixA::InverseMatrix(double *a, double *b, int n) {
    return IMA->InverseMatrix(a, b, n);
}

CMatrixA::~CMatrixA() {
    IM->Release();
    IMA->Release();
    FreeLibrary(h);
}