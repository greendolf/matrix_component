#include "component.h"
#include <iostream>
#include <cmath>

using namespace std;

IID Constants::IID_IUnknown = {0x00000000, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
IID Constants::IID_IMatrix = {0x00000001, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
IID Constants::IID_IClassFactory = {0x00000001, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
IID Constants::IID_IFactoryAdvanced = {0x00000011, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

//{1D778C4C-A00C-4505-B18D-5BCD0004CFC9}
CLSID Constants::CLSID_Matrix = {0x1D778C4C, 0xA00C, 0x4505, {0xB1, 0x8D, 0x5B, 0xCD, 0x00, 0x04, 0xCF, 0xC9}};

IID Constants::IID_IDispatch = {0x00020400, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};

Matrix::Matrix()
{
    cout << "Matrix::Constructor" << endl;
    fRefCount = 0;
}

Matrix::~Matrix()
{
    cout << "Matrix::Destructor" << endl;
}

HRESULT __stdcall Matrix::QueryInterface(const IID &iid, void **ppv)
{
    // cout << "Matrix::QueryInterface:" << iid << endl;

    if (iid == Constants::IID_IUnknown)
    {
        *ppv = (IUnknown *)(IMatrix *)this;
    }
    else if (iid == Constants::IID_IMatrix)
    {
        *ppv = static_cast<IMatrix *>(this);
    }
    else if (iid == Constants::IID_IDispatch)
    {
        *ppv = static_cast<IDispatch *>(this);
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    this->AddRef();
    return S_OK;
}

ULONG __stdcall Matrix::AddRef()
{
    cout << "Matrix::AddRef" << endl;
    fRefCount++;
    cout << "Current references: " << fRefCount << endl;
    return fRefCount;
}

ULONG __stdcall Matrix::Release()
{
    cout << "Matrix::Release" << endl;
    fRefCount--;
    cout << "Current references: " << fRefCount << endl;
    if (fRefCount <= 0)
    {
        cout << "Self-destructing..." << endl;
        delete this;
        cout << "Self-destructing...OK" << endl;
    }
    return fRefCount;
}

HRESULT __stdcall Matrix::AddMatrixNum(double *a, double b, double *c, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i * m + j] = a[i * m + j] + b;
        }
    }
    return S_OK;
}

HRESULT __stdcall Matrix::SubMatrixNum(double *a, double b, double *c, int n, int m)
{
    return Matrix::AddMatrixNum(a, -b, c, n, m);
}

HRESULT __stdcall Matrix::MultMatrixNum(double *a, double b, double *c, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i * m + j] = a[i * m + j] * b;
        }
    }
    return S_OK;
}

HRESULT __stdcall Matrix::DivMatrixNum(double *a, double b, double *c, int n, int m)
{
    return Matrix::MultMatrixNum(a, 1 / b, c, n, m);
}

HRESULT __stdcall Matrix::DetMatrix(double *a, double *det, int n)
{
    cout << "Matrix::DetMatrix" << endl;
    double epsilon = 0.0000000001;
    double d = 1.0;
    double tmp;
    double matrix[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = a[i * n + j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            while (fabs(matrix[j][i]) > epsilon)
            {
                tmp = matrix[i][i] / matrix[j][i];
                for (int k = 0; k < n; k++)
                {
                    matrix[i][k] -= tmp * matrix[j][k];
                    swap(matrix[i][k], matrix[j][k]);
                }
                d = -d;
            }
        }
        d *= matrix[i][i];
    }
    *det = d;
    return S_OK;
}

HRESULT __stdcall Matrix::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    printf("Matrix::GetIDsOfNames\n");

    if (cNames != 1)
    {
        return E_NOTIMPL;
    }

    if (wcscmp(rgszNames[0], L"AddMatrixNum") == 0)
    {
        rgDispId[0] = 1;
    }

    else if (wcscmp(rgszNames[0], L"SubMatrixNum") == 0)
    {
        rgDispId[0] = 2;
    }

    else if (wcscmp(rgszNames[0], L"MultMatrixNum") == 0)
    {
        rgDispId[0] = 3;
    }

    else if (wcscmp(rgszNames[0], L"DivMatrixNum") == 0)
    {
        rgDispId[0] = 4;
    }

    else if (wcscmp(rgszNames[0], L"DetMatrix") == 0)
    {
        rgDispId[0] = 5;
    }

    else
    {
        return E_NOTIMPL;
    }

    return S_OK;
}

HRESULT __stdcall Matrix::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    if (dispIdMember == 1)
    {
        printf("Matrix::Invoke::1");
    }
    else if (dispIdMember == 2)
    {
        printf("Matrix::Invoke::2");
    }
    else if (dispIdMember == 3)
    {
        printf("Matrix::Invoke::3");
    }
    else if (dispIdMember == 4)
    {
        printf("Matrix::Invoke::4");
    }
    else if (dispIdMember == 5)
    {
        printf("Matrix::Invoke::5");
    }
    else
    {
        return E_NOTIMPL;
    }

    return S_OK;
}

HRESULT __stdcall Matrix::GetTypeInfoCount(UINT *pctinfo)
{
    return S_OK;
}

HRESULT __stdcall Matrix::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    return S_OK;
}

HRESULT __stdcall Factory::QueryInterface(const IID &iid, void **ppv)
{
    // cout << "Factory::QueryInterface:" << iid << endl;

    if (iid == Constants::IID_IUnknown)
    {
        *ppv = (IUnknown *)(IClassFactory *)this;
    }
    else if (iid == Constants::IID_IClassFactory)
    {
        *ppv = static_cast<IClassFactory *>(this);
    }
    else if (iid == Constants::IID_IFactoryAdvanced)
    {
        *ppv = static_cast<IFactoryAdvanced *>(this);
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    this->AddRef();
    return S_OK;
}

ULONG __stdcall Factory::AddRef()
{
    cout << "Factory::AddRef" << endl;
    fRefCount++;
    cout << "Current references: " << fRefCount << endl;
    return fRefCount;
}

ULONG __stdcall Factory::Release()
{
    cout << "Factory::Release" << endl;
    fRefCount--;
    cout << "Current references: " << fRefCount << endl;
    if (fRefCount == 0)
    {
        cout << "Self-destructing..." << endl;
        delete this;
        cout << "Self-destructing...OK" << endl;
    }
    return fRefCount;
}

HRESULT __stdcall Factory::CreateInstance(IUnknown *pIUnknownOuter, const IID &iid, void **ppv)
{
    // cout << "Factory::CreateInstance:" << ":" << iid << endl;
    IUnknown *obj = NULL;
    obj = (IUnknown *)(IMatrix *)new Matrix();
    if (obj == NULL)
    {
        return E_OUTOFMEMORY;
    }
    return obj->QueryInterface(iid, ppv);
}

HRESULT __stdcall Factory::CreateInstance(const IID &iid, void **ppv)
{
    // cout << "Factory::CreateInstance:" << ":" << iid << endl;
    IUnknown *obj = NULL;
    obj = (IUnknown *)(IMatrix *)new Matrix();
    if (obj == NULL)
    {
        return E_OUTOFMEMORY;
    }
    return obj->QueryInterface(iid, ppv);
}

HRESULT __stdcall Factory::LockServer(BOOL fLock)
{
    return S_OK;
}