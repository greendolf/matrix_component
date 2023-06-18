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

    HRESULT resInstance = PCF->CreateInstance(NULL, Constants::IID_IMatrix, (void **)&im);

    if (!SUCCEEDED(resInstance))
    {
        printf("No instance\n");
    }

    this->matrix = new double;
    this->im->SetMatrix(matrix, 0, 0);

    PCF->Release();

    CoUninitialize();
}

MatrixAdvanced::MatrixAdvanced(double *a, int n, int m)
{
    cout << "MatrixAdvanced::ConstructorAdvanced" << endl;
    fRefCount = 0;

    CoInitialize(NULL);

    IFactoryAdvanced *PCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Matrix, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IFactoryAdvanced, (void **)&PCF);

    if (!SUCCEEDED(resFactory))
    {
        printf("No factory\n");
    }

    HRESULT resInstance = PCF->CreateInstanceAdvanced(Constants::IID_IMatrix, (void **)&im, a, m, n);

    if (!SUCCEEDED(resInstance))
    {
        printf("No instance\n");
    }

    PCF->Release();

    this->matrix = NULL;
    printf("\n\n%p\n\n%p\n\n", (this->matrix), &(this->matrix));
    this->n = n;
    this->m = m;

    im->GetMatrix(&(this->matrix), &(this->n), &(this->m));
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

HRESULT __stdcall MatrixAdvanced::SetMatrix(double *a, int m, int n)
{
    return im->SetMatrix(a, m, n);
}
HRESULT __stdcall MatrixAdvanced::GetMatrix(double **a, int *m, int *n)
{
    return im->GetMatrix(a, m, n);
}

HRESULT __stdcall MatrixAdvanced::MultMatrixNum(double b)
{
    printf("MatrixAdvanced::MultMatrixNum");
    return im->MultMatrixNum(b);
}

HRESULT __stdcall MatrixAdvanced::DivMatrixNum(double b)
{
    printf("MatrixAdvanced::DivMatrixNum");
    return im->MultMatrixNum(1 / b);
}

HRESULT __stdcall MatrixAdvanced::DetMatrix(double *det)
{
    printf("MatrixAdvanced::DetMatrix");
    return im->DetMatrix(det);
}

HRESULT __stdcall MatrixAdvanced::AddMatrix(double *b)
{
    printf("MatrixAdvanced::AddMatrix");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i * n + j] += b[i * n + j];
        }
    }
    return S_OK;
}

HRESULT __stdcall MatrixAdvanced::SubMatrix(double *b)
{
    printf("MatrixAdvanced::SubMatrix");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i * m + j] -= b[i * m + j];
        }
    }
    return S_OK;
}

HRESULT __stdcall MatrixAdvanced::MultMatrix(double *b, int n2)
{
    double *temp = new double[m * n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i * m + j] = matrix[i * m + j];
        }
    }
    delete[] matrix;
    matrix = new double[m * n2];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            double sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += temp[i * m + k] * b[k * m + j];
            }
            matrix[i * m + j] = sum;
        }
    }
    return S_OK;
}

HRESULT __stdcall MatrixAdvanced::TransMatrix()
{
    double *temp = new double[m * n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i * m + j] = matrix[i * m + j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->matrix[i * n + j] = this->matrix[j * n + i];
        }
    }
    return S_OK;
}

HRESULT __stdcall MatrixAdvanced::InverseMatrix()
{
    double *det = new double;
    MatrixAdvanced::DetMatrix(det);
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
                    inverse[i][j] = this->matrix[i * n + j];
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
                this->matrix[i * n + j] = inverse[i][j + n];
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

HRESULT __stdcall FactoryAdvanced::CreateInstanceAdvanced(const IID &iid, void **ppv, double *a, int m, int n)
{
    // cout << "FactoryAdvanced::CreateInstanceAdvanced:" << ":" << iid << endl;
    IUnknown *obj = NULL;
    obj = (IUnknown *)(IMatrix *)new MatrixAdvanced(a, m, n);
    return obj->QueryInterface(iid, ppv);
}

HRESULT __stdcall FactoryAdvanced::LockServer(BOOL fLock)
{
    return S_OK;
}