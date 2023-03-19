#include "server.h"

#include <iostream>
using namespace std;

Matrix::Matrix() {
    cout << "Matrix::Constructor" << endl;
    fRefCount = 0;
}

Matrix::~Matrix() {
    cout << "Matrix::Destructor" << endl;  
}

HRESULT_ __stdcall Matrix::QueryInterface(const IID_& iid, void** ppv) {
    cout << "Matrix::QueryInterface:" << iid << endl;

    if (iid == IID_IUnknown_) {
        *ppv = (IUnknown_*)(IMatrix*)this;
    }
    else if (iid == IID_IMatrix) {
        *ppv = static_cast<IMatrix*>(this);
    }
    else if (iid == IID_IMatrixA) {
        *ppv = static_cast<IMatrixA*>(this);
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE_;
    }
    this->AddRef();
    return S_OK_;
}

ULONG_ __stdcall Matrix::AddRef() {
   cout << "Matrix::AddRef" << endl;
   fRefCount++;
   cout << "Current references: " << fRefCount << endl;
   return fRefCount;
}

ULONG_ __stdcall Matrix::Release() {
    cout << "Matrix::Release" << endl;
    fRefCount--;
    cout << "Current references: " << fRefCount << endl;
    if (fRefCount==0) {
        cout << "Self-destructing..." << endl;
        delete this;
        cout << "Self-destructing...OK" << endl;
    }
    return fRefCount;
}

HRESULT_ __stdcall Matrix::AddMatrixNum(double *a, double b, double *c, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i * m + j] = a[i * m + j] + b;
        }
    }
    return S_OK_;
}

HRESULT_ __stdcall Matrix::SubMatrixNum(double *a, double b, double *c, int n, int m) {
    return Matrix::AddMatrixNum(a, -b, c, n, m);
}

HRESULT_ __stdcall Matrix::MultMatrixNum(double *a, double b, double *c, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i * m + j] = a[i * m + j] * b;
        }
    }
    return S_OK_;
}

HRESULT_ __stdcall Matrix::DivMatrixNum(double *a, double b, double *c, int n, int m) {
    return Matrix::MultMatrixNum(a, 1/b, c, n, m);
}

HRESULT_ __stdcall Matrix::DetMatrix(double *a, double *det, int n) {
    cout << "Matrix::DetMatrix" << endl;
    double eps = 0.0000000001;
    double d = 1.0;
    double tmp;
    double matrix[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = a[i * n + j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (abs(matrix[j][i]) > eps) {
                tmp = matrix[i][i] / matrix[j][i];
                for (int k = 0; k < n; k++) {
                    matrix[i][k] -= tmp * matrix[j][k];
                    swap(matrix[i][k], matrix[j][k]);
                }
                d = -d;
            }
        }
        d *= matrix[i][i];
    }
    *det = d;
    return S_OK_;
}

HRESULT_ __stdcall Matrix::AddMatrix(double *a, double *b, double *c, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i * m + j] = a[i * m + j] + b[i * m + j];
        }
    }
    return S_OK_;
}

HRESULT_ __stdcall Matrix::MultMatrix(double *a, double *b, double *c, int n, int m, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            c[i * p + j] = 0;
            for (int k = 0; k < m; k++) {
                c[i * p + j] += a[i * m + k] * b[k * p + j];
            }
        }
    }
    return S_OK_;
}

HRESULT_ __stdcall Matrix::TransMatrix(double *a, double *b, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i * n + j] = a[j * n + i];
        }
    }
    return S_OK_;
}

HRESULT_ __stdcall Matrix::InverseMatrix(double *a, double *b, int n) {
    double *det = new double();
    Matrix::DetMatrix(a, det, n);
    if (*det != 0) {
        double temp;
        double inverse[n][n*2];
        //добавление единичной матрицы
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n*2; j++) {
                if (j < n) {
                    inverse[i][j] = a[i * n + j];
                } else if (j == n + i) {
                    inverse[i][j] = 1;
                } else {
                    inverse[i][j] = 0;
                }
            }
        }
        //зануление низа
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                temp = inverse[j][i] / inverse[i][i];
                for (int k = i; k < n*2; k++) {
                    inverse[j][k] -= temp * inverse[i][k];
                }
            }
        }
        //зануление верха
        for (int i = n-1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                temp = inverse[j][i] / inverse[i][i];
                for (int k=i; k < n*2; k++) {
                    inverse[j][k] -= temp * inverse[i][k];
                }
            }
        }
        //единицы на главной диагонали
        for (int i = 0; i < n; i++) {
            temp = inverse[i][i];
            for (int j = i; j < n*2; j++) {
                inverse[i][j] /= temp;
            }
        }
        //вывод обратной матрицы
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b[i * n + j] = inverse[i][j + n];
            }
        }
    } else {
        return E_DET0_;
    }
    return S_OK_;
}