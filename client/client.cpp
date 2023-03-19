#include <iostream>
#include <iomanip>
#include "../server/interfaces.h"

using namespace std;


int main () {
    cout << "CLIENT MAIN START" << endl;
    int n = 3;
    double* test = new double[n*n] {1, 10, 3, 2, 5, 7, 3, 7, 9};
    double* test2 = new double[n*n];
    double* det = new double();

    IMatrix *M = NULL;
    HRESULT_ res = CreateInstance(IID_IMatrix, (void**) &M);
    if (res == S_OK_) {
        cout << "IMATRIX CREATE SUCCESS" << endl;
        res = M->DetMatrix(test, det, n);
        if (res == S_OK_) { cout << "Det M = " << *det << endl; }
        res = -1;
    }
    IMatrixA *MA = NULL;
    res = M->QueryInterface(IID_IMatrixA, (void**) &MA);
    if (res == S_OK_) {
            cout << "IMATRIXA QI SUCCESS" << endl;
            res = MA->InverseMatrix(test, test2, n);
            if (res == S_OK_) {
                cout << endl << "M:" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << setw(12) << test[i * n + j] << " | ";
                }
                cout << endl;
            }
            cout << "\nInv M:" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << setw(12) << test2[i * n + j] << " | ";
                }
                cout << endl;
            }
        } 
        res = MA->TransMatrix(test, test2, n);
        if (res == S_OK_) {
            cout << endl << "Trans M: " << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << setw(12) << test2[i * n + j] << " | ";
                }
                cout << endl;
            }
        }
    }
    cout << endl;
    
    M->Release();
    MA->Release();
    cout << "\nend." << endl;
    cin.get();
    return 0;
}