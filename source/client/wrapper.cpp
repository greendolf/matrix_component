#include <stdio.h>
#include <objbase.h>
#include "wrapper.h"

EMatrix::EMatrix(const char *msg)
{
    this->msg = msg;
}

const char *EMatrix::GetMessage()
{
    return msg;
}

CMatrix::CMatrix()
{
    CoInitialize(NULL);

    printf("Wrapper::GetClassObject\n");

    IClassFactory *ICF = NULL;

    HRESULT res = CoGetClassObject(Constants::CLSID_MATRIX, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void **)&ICF);
    if (res == E_NOTIMPL)
    {
        throw EMatrix("Error while creating CMatrix: Unsupported component");
    }
    else if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrix: Unsupported interface");
    }
    else if (res != S_OK)
    {
        throw EMatrix("Error while creating CMatrix: Unknown error");
    }

    res = ICF->CreateInstance(NULL, Constants::IID_IMatrix, (void **)&IM);
    if (res == S_OK)
    {
        ICF->Release();
    }
    else
    {
        throw EMatrix("Error while creating CMatrix: Unsupported interface");
    }
}

HRESULT __stdcall CMatrix::AddMatrixNum(double *a, double b, double *c, int n, int m)
{
    return IM->AddMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall CMatrix::SubMatrixNum(double *a, double b, double *c, int n, int m)
{
    return IM->SubMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall CMatrix::MultMatrixNum(double *a, double b, double *c, int n, int m)
{
    return IM->MultMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall CMatrix::DivMatrixNum(double *a, double b, double *c, int n, int m)
{
    return IM->DivMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall CMatrix::DetMatrix(double *a, double *det, int n)
{
    return IM->DetMatrix(a, det, n);
}

CMatrix::~CMatrix()
{
    IM->Release();
    FreeLibrary(h);
}

CMatrixA::CMatrixA()
{

    CoInitialize(NULL);

    printf("Wrapper::GetClassObject\n");

    IClassFactory *ICF = NULL;

    HRESULT res = CoGetClassObject(Constants::CLSID_MATRIXA, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void **)&ICF);
    // printf("%ul\n", GetLastError());
    if (res == E_NOTIMPL)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported component");
    }
    else if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }
    else if (res != S_OK)
    {
        throw EMatrix("Error while creating CMatrixA: Unknown error");
    }
    res = ICF->CreateInstance(NULL, Constants::IID_IMatrix, (void **)&IM);
    if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }

    res = ICF->CreateInstance(NULL, Constants::IID_IMatrixA, (void **)&IMA);
    if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }
    ICF->Release();
}

HRESULT __stdcall CMatrixA::AddMatrixNum(double *a, double b, double *c, int n, int m)
{
    return IM->AddMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall CMatrixA::SubMatrixNum(double *a, double b, double *c, int n, int m)
{
    return IM->SubMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall CMatrixA::MultMatrixNum(double *a, double b, double *c, int n, int m)
{
    return IM->MultMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall CMatrixA::DivMatrixNum(double *a, double b, double *c, int n, int m)
{
    return IM->DivMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall CMatrixA::DetMatrix(double *a, double *det, int n)
{
    return IM->DetMatrix(a, det, n);
}

HRESULT __stdcall CMatrixA::AddMatrix(double *a, double *b, double *c, int n, int m)
{
    return IMA->AddMatrix(a, b, c, n, m);
}

HRESULT __stdcall CMatrixA::MultMatrix(double *a, double *b, double *c, int n, int m, int p)
{
    return IMA->MultMatrix(a, b, c, n, m, p);
}

HRESULT __stdcall CMatrixA::TransMatrix(double *a, double *b, int n)
{
    return IMA->TransMatrix(a, b, n);
}

HRESULT __stdcall CMatrixA::InverseMatrix(double *a, double *b, int n)
{
    return IMA->InverseMatrix(a, b, n);
}

CMatrixA::~CMatrixA()
{
    IM->Release();
    IMA->Release();
    FreeLibrary(h);
}