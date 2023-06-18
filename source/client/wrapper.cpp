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

    printf("Wrapper::CMatrix::GetClassObject\n");

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

CMatrix::CMatrix(double *a, int m, int n)
{
    CoInitialize(NULL);

    printf("Wrapper::CMatrix::GetClassObject\n");

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

    res = ICF->CreateInstanceAdvanced(Constants::IID_IMatrix, (void **)&IM, a, m, n);
    if (res == S_OK)
    {
        ICF->Release();
    }
    else
    {
        throw EMatrix("Error while creating CMatrix: Unsupported interface");
    }
}

HRESULT __stdcall CMatrix::SetMatrix(double *a, int m, int n)
{
    return IM->SetMatrix(a, m, n);
}
HRESULT __stdcall CMatrix::GetMatrix(double **a, int *m, int *n)
{
    return IM->GetMatrix(a, m, n);
}

HRESULT __stdcall CMatrix::MultMatrixNum(double b)
{
    return IM->MultMatrixNum(b);
}

HRESULT __stdcall CMatrix::DivMatrixNum(double b)
{
    return IM->DivMatrixNum(b);
}

HRESULT __stdcall CMatrix::DetMatrix(double *det)
{
    return IM->DetMatrix(det);
}

CMatrix::~CMatrix()
{
    IM->Release();
    FreeLibrary(h);
}

CMatrixA::CMatrixA()
{

    CoInitialize(NULL);

    printf("Wrapper::CMatrixA::GetClassObject\n");

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

CMatrixA::CMatrixA(double *a, int m, int n)
{
    CoInitialize(NULL);

    printf("Wrapper::CMatrixA::GetClassObject\n");

    IFactoryAdvanced *IFA = NULL;

    HRESULT res = CoGetClassObject(Constants::CLSID_MatrixAdvanced, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IFactoryAdvanced, (void **)&IFA);
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

    res = IFA->CreateInstanceAdvanced(Constants::IID_IMatrixAdvanced, (void **)&IMA, a, m, n);

    if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }

    res = IMA->QueryInterface(Constants::IID_IMatrix, (void **)&IM);
    if (res == E_NOINTERFACE)
    {
        throw EMatrix("Error while creating CMatrixA: Unsupported interface");
    }
    IFA->Release();
}

HRESULT __stdcall CMatrixA::SetMatrix(double *a, int m, int n)
{
    return IM->SetMatrix(a, m, n);
}
HRESULT __stdcall CMatrixA::GetMatrix(double **a, int *m, int *n)
{
    return IM->GetMatrix(a, m, n);
}

HRESULT __stdcall CMatrixA::MultMatrixNum(double b)
{
    return IM->MultMatrixNum(b);
}

HRESULT __stdcall CMatrixA::DivMatrixNum(double b)
{
    return IM->DivMatrixNum(b);
}

HRESULT __stdcall CMatrixA::DetMatrix(double *det)
{
    return IM->DetMatrix(det);
}

HRESULT __stdcall CMatrixA::AddMatrix(double *b)
{
    return IMA->AddMatrix(b);
}

HRESULT __stdcall CMatrixA::MultMatrix(double *b, int p)
{
    return IMA->MultMatrix(b, p);
}

HRESULT __stdcall CMatrixA::TransMatrix()
{
    return IMA->TransMatrix();
}

HRESULT __stdcall CMatrixA::InverseMatrix()
{
    return IMA->InverseMatrix();
}

CMatrixA::~CMatrixA()
{
    IM->Release();
    IMA->Release();
    FreeLibrary(h);
}