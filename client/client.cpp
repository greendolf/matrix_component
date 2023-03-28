#include <iostream>
#include <iomanip>
#include "interfaces.h"

using namespace std;

void show(double *a, int n, int m);


int main () {
    cout << "CLIENT MAIN START" << endl;

    int n = 3;
    double* test = new double[n*n] {1, 10, 3, 2, 5, 7, 3, 7, 9};

    IMatrix *M = NULL;
    HRESULT_ res = CreateInstance(CLSID_MATRIXA, IID_IMatrix, (void**) &M);

    if (res == S_OK_) {
        cout << "IMATRIX CREATE SUCCESS" << endl;
        double* det = new double();
        res = M->DetMatrix(test, det, n);
        if (res == S_OK_) { cout << "Det M = " << *det << endl; }
        res = -1;
    }

    IMatrixA *MA = NULL;
    res = M->QueryInterface(IID_IMatrixA, (void**) &MA);

    if (res == S_OK_) {
        cout << "IMATRIXA QI SUCCESS" << endl;
        double* test2 = new double[n*n];
        res = MA->InverseMatrix(test, test2, n);

        if (res == S_OK_) {
            cout << endl << "M:" << endl;
            show(test, n, n);
            cout << "\nInv M:" << endl;
            show(test2, n, n);
        }

        res = MA->TransMatrix(test, test2, n);
        if (res == S_OK_) {
            cout << endl << "Trans M: " << endl;
            show(test2, n, n);
        }
    }

    cout << endl;
    
    M->Release();
    MA->Release();
    cout << "\nend." << endl << endl;

    IFactory *IF = NULL;
    res = GetClassObject(CLSID_Factory, IID_IFactory, (void**) &IF);
    if (res == S_OK_) {
        cout << "GetClassObject Success" << endl;
        IMatrix *IMA = NULL;
        res = IF -> CreateInstance(1, (void**) &IMA);
        if (res == S_OK_) {
            cout << "IBF::CreateInstance Success" << endl;
            double* test4 = new double[n * n];
            res = IMA->AddMatrixNum(test, 5, test4, 3, 3);
            if (res == S_OK_) {
                cout << "Matrix:" << endl;
                show(test, n, n);
                cout << "AddMatrixNum 5 res:" << endl;
                show(test4, n, n);
            }
        }
    }
    cin.get();
    return 0;
}


void show(double *a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(12) << a[i * m + j] << " | ";
        }
        cout << endl;
    }
}