#include <iostream>
#include <iomanip>
#include "wrapper.h"

using namespace std;

IID Constants::IID_IUnknown = {0x00000000, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
IID Constants::IID_IClassFactory = {0x00000001, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};

IID Constants::IID_IMatrix = {0x00000001, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
IID Constants::IID_IMatrixA = {0x00000002, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
IID Constants::IID_IFactoryA = {0x00000011, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

//{1D778C4C-A00C-4505-B18D-5BCD0004CFC9}
CLSID Constants::CLSID_MATRIX = {0x1D778C4C, 0xA00C, 0x4505, {0xB1, 0x8D, 0x5B, 0xCD, 0x00, 0x04, 0xCF, 0xC9}};
//{D7C3EE79-C27E-4BAE-95C6-08CF8FA30DDC}
CLSID Constants::CLSID_MATRIXA = {0xD7C3EE79, 0xC27E, 0x4BAE, {0x95, 0xC6, 0x08, 0xCF, 0x8F, 0xA3, 0x0D, 0xDC}};

IID Constants::IID_IDispatch = {0x00020400, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};

void show(double *a, int m, int n);

int main()
{
    cout << "CLIENT MAIN START" << endl;
    int m, n;
    double *test = new double[3 * 3]{1, 10, 3, 2, 5, 7, 3, 7, 9};
    double *test2 = new double[3 * 3];
    try
    {
        CMatrixA *CMA = new CMatrixA(test, 3, 3);
        cout << "CMATRIXA CREATE SUCCESS" << endl;
        double *det = new double;
        HRESULT res = CMA->DetMatrix(det);
        if (res == S_OK)
        {
            cout << "Det M = " << *det << endl;
        };
        res = CMA->MultMatrixNum(5);
        CMA->GetMatrix(&test2, &m, &n);
        if (res == S_OK)
        {
            cout << endl
                 << "M:" << endl;
            show(test, n, n);
            cout << "\n5M:" << endl;
            show(test2, n, n);
        }
        CMA->GetMatrix(&test, NULL, NULL);
        show(test, n, n);
        cout << endl << "multiple by" << endl;
        show(test2, n, n);
        res = CMA->MultMatrix(test2, 3);
        CMA->GetMatrix(&test, NULL, NULL);
        if (res == S_OK)
        {
            show(test2, n, n);
            cout << endl
                 << "Mult M: " << endl;
            show(test, n, n);
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
}