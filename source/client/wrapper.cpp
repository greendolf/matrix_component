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

    HRESULT res = CoGetClassObject(Constants::CLSID_Matrix, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void **)&ICF);
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

CMatrix::CMatrix(double *a, int n, int m)
{
    CoInitialize(NULL);

    printf("Wrapper::GetClassObject\n");

    IFactoryAdvanced *ICF = NULL;

    HRESULT res = CoGetClassObject(Constants::CLSID_Matrix, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IFactoryAdvanced, (void **)&ICF);
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

    res = ICF->CreateInstanceAdvanced(Constants::IID_IMatrix, (void **)&IM, a, n, m);
    if (res == S_OK)
    {
        ICF->Release();
    }
    else
    {
        throw EMatrix("Error while creating CMatrix: Unsupported interface");
    }
}

HRESULT __stdcall CMatrix::AddMatrixNum(double b, double *c, int n, int m)
{
    return IM->AddMatrixNum(b, c, n, m);
}

HRESULT __stdcall CMatrix::SubMatrixNum(double b, double *c, int n, int m)
{
    return IM->SubMatrixNum(b, c, n, m);
}

HRESULT __stdcall CMatrix::MultMatrixNum(double b, double *c, int n, int m)
{
    return IM->MultMatrixNum(b, c, n, m);
}

HRESULT __stdcall CMatrix::DivMatrixNum(double b, double *c, int n, int m)
{
    return IM->DivMatrixNum(b, c, n, m);
}

HRESULT __stdcall CMatrix::DetMatrix(double *det, int n)
{
    return IM->DetMatrix(det, n);
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

    HRESULT res = CoGetClassObject(Constants::CLSID_MatrixAdvanced, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void **)&ICF);
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

    res = ICF->CreateInstance(NULL, Constants::IID_IMatrixAdvanced, (void **)&IMA);
    if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }
    ICF->Release();
}

CMatrixA::CMatrixA(double *a, int n, int m)
{
    CoInitialize(NULL);

    printf("Wrapper::GetClassObject\n");

    IFactoryAdvanced *ICF = NULL;

    HRESULT res = CoGetClassObject(Constants::CLSID_MatrixAdvanced, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IFactoryAdvanced, (void **)&ICF);
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
    res = ICF->CreateInstanceAdvanced(Constants::IID_IMatrixAdvanced, (void **)&IM, a, n, m);
    if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }

    res = ICF->QueryInterface(Constants::IID_IMatrix, (void **)&IM);
    if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }
    ICF->Release();
}

HRESULT __stdcall CMatrixA::AddMatrixNum(double b, double *c, int n, int m)
{
    return IM->AddMatrixNum(b, c, n, m);
}

HRESULT __stdcall CMatrixA::SubMatrixNum(double b, double *c, int n, int m)
{
    return IM->SubMatrixNum(b, c, n, m);
}

HRESULT __stdcall CMatrixA::MultMatrixNum(double b, double *c, int n, int m)
{
    return IM->MultMatrixNum(b, c, n, m);
}

HRESULT __stdcall CMatrixA::DivMatrixNum(double b, double *c, int n, int m)
{
    return IM->DivMatrixNum(b, c, n, m);
}

HRESULT __stdcall CMatrixA::DetMatrix(double *det, int n)
{
    return IM->DetMatrix(det, n);
}

HRESULT __stdcall CMatrixA::AddMatrix(double *b, double *c, int n, int m)
{
    return IMA->AddMatrix(b, c, n, m);
}

HRESULT __stdcall CMatrixA::MultMatrix(double *b, double *c, int n, int m, int p)
{
    return IMA->MultMatrix(b, c, n, m, p);
}

HRESULT __stdcall CMatrixA::TransMatrix(double *b, int n)
{
    return IMA->TransMatrix(b, n);
}

HRESULT __stdcall CMatrixA::InverseMatrix(double *b, int n)
{
    return IMA->InverseMatrix(b, n);
}

CMatrixA::~CMatrixA()
{
    IM->Release();
    IMA->Release();
    FreeLibrary(h);
}