#include <iostream>
#include <iomanip>
#include "wrapper.h"

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

void show(double *a, int m, int n);

int main()
{
    cout << "CLIENT MAIN START" << endl;
    int m = 3, n = 3;
    double *M = new double[m * n]{1, 10, 3, 2, 5, 7, 3, 7, 9};
    try
    {
        CMatrixA *CMA = new CMatrixA(M, 3, 3);
        cout << "CMATRIXA CREATE SUCCESS" << endl;
        double *det = new double;
        HRESULT res = CMA->DetMatrix(det);
        if (res == S_OK)
        {
            printf("Det M = %.2f\n", *det);
        };
        res = CMA->MultMatrixNum(5);
        if (res == S_OK)
        {
            printf("M:\n");
            show(M, m, n);
            double *M5 = NULL;
            CMA->GetMatrix(&M5, &m, &n);
            cout << "M * 5:" << endl;
            show(M5, m, n);
        }
        CMA->SetMatrix(M, m, n);
        res = CMA->MultMatrix(M, n);
        if (res == S_OK)
        {
            printf("M:\n");
            show(M, n, n);
            double *mulRes = NULL;
            CMA->GetMatrix(&mulRes, NULL, NULL);
            printf("M * M:\n");
            show(mulRes, n, n);
        }
        CMA->SetMatrix(M, m, n);
        res = CMA->TransMatrix();
        if (res == S_OK)
        {
            printf("M:\n");
            show(M, n, n);
            double *transRes = NULL;
            CMA->GetMatrix(&transRes, NULL, NULL);
            printf("Trans M:\n");
            show(transRes, m, n);
        }
        CMA->SetMatrix(M, m, n);
        res = CMA->InverseMatrix();
        if (res == S_OK)
        {
            printf("M:\n");
            show(M, n, n);
            double *invRes = NULL;
            CMA->GetMatrix(&invRes, NULL, NULL);
            printf("Inverse M:\n");
            show(invRes, m, n);
        }
        cin.get();
        printf("%s\n", "CLIENT FINISH");
    }
    catch (EMatrix &e)
    {
        cout << e.GetMessage() << endl;
    };
    return 0;
}

void show(double *a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(12) << a[i * m + j] << " | ";
        }
        cout << endl;
    }
    cout << endl;
}