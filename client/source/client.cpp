#include <iostream>
#include <iomanip>
#include "wrapper.h"

using namespace std;

void show(double *a, int n, int m);


int main () {
    cout << "CLIENT MAIN START" << endl;

    int n = 3;
    double* test = new double[n*n] {1, 10, 3, 2, 5, 7, 3, 7, 9};
    try {
        CMatrixA CMA;
        cout << "CMATRIX CREATE SUCCESS" << endl;
        double *det = new double();
        HRESULT_ res = CMA.DetMatrix(test, det, n);
        if (res == S_OK_) { cout << "Det M = " << *det << endl; };

        double* test2 = new double[n*n];
        res = CMA.InverseMatrix(test, test2, n);
        if (res == S_OK_) {
            cout << endl << "M:" << endl;
            show(test, n, n);
            cout << "\nInv M:" << endl;
            show(test2, n, n);
        }

        res = CMA.TransMatrix(test, test2, n);
        if (res == S_OK_) {
            cout << endl << "Trans M: " << endl;
            show(test2, n, n);
        }
        CMA.~CMatrixA();
        cin.get();
    }
    catch(EMatrix& e) { cout << e.GetMessage() << endl; };
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