#include "component.h"
#include <iostream>
#include <cmath>

using namespace std;

IID Constants::IID_IUnknown = {0x00000000, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
IID Constants::IID_IClassFactory = {0x00000001, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};

IID Constants::IID_IMatrix = {0x00000001, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
IID Constants::IID_IMatrixAdvanced = {0x00000002, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
IID Constants::IID_IFactoryAdvanced = {0x00000011, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

//{1D778C4C-A00C-4505-B18D-5BCD0004CFC9}
CLSID Constants::CLSID_Matrix = {0x1D778C4C, 0xA00C, 0x4505, {0xB1, 0x8D, 0x5B, 0xCD, 0x00, 0x04, 0xCF, 0xC9}};
//{D7C3EE79-C27E-4BAE-95C6-08CF8FA30DDC}
CLSID Constants::CLSID_MatrixAdvanced = {0xD7C3EE79, 0xC27E, 0x4BAE, {0x95, 0xC6, 0x08, 0xCF, 0x8F, 0xA3, 0x0D, 0xDC}};

IID Constants::IID_IDispatch = {0x00020400, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};

MatrixAdvanced::MatrixAdvanced()
{
    cout << "MatrixAdvanced::Constructor" << endl;
    fRefCount = 0;

    CoInitialize(NULL);

    IClassFactory *PCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Matrix, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void **)&PCF);

    if (!SUCCEEDED(resFactory))
    {
        printf("No factory\n");
    }

    HRESULT resInstance = PCF->CreateInstance(NULL, Constants::IID_IMatrix, (void **)&ima);

    if (!SUCCEEDED(resInstance))
    {
        printf("No instance\n");
    }

    PCF->Release();

    CoUninitialize();
}

MatrixAdvanced::~MatrixAdvanced()
{
    cout << "MatrixAdvanced::Destructor" << endl;
}

HRESULT __stdcall MatrixAdvanced::QueryInterface(const IID &iid, void **ppv)
{
    // cout << "MatrixAdvanced::QueryInterface:" << iid << endl;

    if (iid == Constants::IID_IUnknown)
    {
        *ppv = (IUnknown *)(IMatrix *)this;
    }
    else if (iid == Constants::IID_IMatrix)
    {
        *ppv = static_cast<IMatrix *>(this);
    }
    else if (iid == Constants::IID_IMatrixAdvanced)
    {
        *ppv = static_cast<IMatrixAdvanced *>(this);
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    this->AddRef();
    return S_OK;
}

ULONG __stdcall MatrixAdvanced::AddRef()
{
    cout << "MatrixAdvanced::AddRef" << endl;
    fRefCount++;
    cout << "Current references: " << fRefCount << endl;
    return fRefCount;
}

ULONG __stdcall MatrixAdvanced::Release()
{
    cout << "MatrixAdvanced::Release" << endl;
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

HRESULT __stdcall MatrixAdvanced::AddMatrixNum(double *a, double b, double *c, int n, int m)
{
    printf("MatrixAdvanced::AddMatrixNum");
    return ima->AddMatrixNum(a, b, c, n, m);;
}

HRESULT __stdcall MatrixAdvanced::SubMatrixNum(double *a, double b, double *c, int n, int m)
{
    printf("MatrixAdvanced::SubMatrixNum");
    return ima->AddMatrixNum(a, -b, c, n, m);;
}

HRESULT __stdcall MatrixAdvanced::MultMatrixNum(double *a, double b, double *c, int n, int m)
{
    printf("MatrixAdvanced::MultMatrixNum");
    return ima->MultMatrixNum(a, b, c, n, m);
}

HRESULT __stdcall MatrixAdvanced::DivMatrixNum(double *a, double b, double *c, int n, int m)
{
    printf("MatrixAdvanced::DivMatrixNum");
    return ima->MultMatrixNum(a, 1/b, c, n, m);
}

HRESULT __stdcall MatrixAdvanced::DetMatrix(double *a, double *det, const int n)
{
    printf("MatrixAdvanced::DetMatrix");
    return ima->DetMatrix(a, det, n);
}

HRESULT __stdcall MatrixAdvanced::AddMatrix(double *a, double *b, double *c, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            c[i * m + j] = a[i * m + j] + b[i * m + j];
        }
    }
    return S_OK;
}

HRESULT __stdcall MatrixAdvanced::MultMatrix(double *a, double *b, double *c, int n, int m, int p)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            c[i * p + j] = 0;
            for (int k = 0; k < m; k++)
            {
                c[i * p + j] += a[i * m + k] * b[k * p + j];
            }
        }
    }
    return S_OK;
}

HRESULT __stdcall MatrixAdvanced::TransMatrix(double *a, double *b, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i * n + j] = a[j * n + i];
        }
    }
    return S_OK;
}

HRESULT __stdcall MatrixAdvanced::InverseMatrix(double *a, double *b, int n)
{
    double *det = new double();
    MatrixAdvanced::DetMatrix(a, det, n);
    if (*det != 0)
    {
        double temp;
        double inverse[n][n * 2];
        // добавление единичной матрицы
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n * 2; j++)
            {
                if (j < n)
                {
                    inverse[i][j] = a[i * n + j];
                }
                else if (j == n + i)
                {
                    inverse[i][j] = 1;
                }
                else
                {
                    inverse[i][j] = 0;
                }
            }
        }
        // зануление низа
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                temp = inverse[j][i] / inverse[i][i];
                for (int k = i; k < n * 2; k++)
                {
                    inverse[j][k] -= temp * inverse[i][k];
                }
            }
        }
        // зануление верха
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                temp = inverse[j][i] / inverse[i][i];
                for (int k = i; k < n * 2; k++)
                {
                    inverse[j][k] -= temp * inverse[i][k];
                }
            }
        }
        // единицы на главной диагонали
        for (int i = 0; i < n; i++)
        {
            temp = inverse[i][i];
            for (int j = i; j < n * 2; j++)
            {
                inverse[i][j] /= temp;
            }
        }
        // вывод обратной матрицы
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                b[i * n + j] = inverse[i][j + n];
            }
        }
    }
    else
    {
        return E_UNEXPECTED;
    }
    return S_OK;
}

HRESULT __stdcall FactoryAdvanced::QueryInterface(const IID &iid, void **ppv)
{
    // cout << "FactoryAdvanced::QueryInterface:" << iid << endl;

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

ULONG __stdcall FactoryAdvanced::AddRef()
{
    cout << "FactoryAdvanced::AddRef" << endl;
    fRefCount++;
    cout << "Current references: " << fRefCount << endl;
    return fRefCount;
}

ULONG __stdcall FactoryAdvanced::Release()
{
    cout << "FactoryAdvanced::Release" << endl;
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

HRESULT __stdcall FactoryAdvanced::CreateInstance(IUnknown *pIUnknownOuter, const IID &iid, void **ppv)
{
    // cout << "FactoryAdvanced::CreateInstance:" << ":" << iid << endl;
    IUnknown *obj = NULL;
    obj = (IUnknown *)(IMatrix *)new MatrixAdvanced();
    return obj->QueryInterface(iid, ppv);
}

HRESULT __stdcall FactoryAdvanced::CreateInstance(const IID &iid, void **ppv)
{
    // cout << "FactoryAdvanced::CreateInstance:" << ":" << iid << endl;
    IUnknown *obj = NULL;
    obj = (IUnknown *)(IMatrix *)new MatrixAdvanced();
    return obj->QueryInterface(iid, ppv);
}

HRESULT __stdcall FactoryAdvanced::LockServer(BOOL fLock)
{
    return S_OK;
}