#pragma once

#include "interfaces.h"

class EMatrix {
    private:
        const char* msg;
    public:
        EMatrix(const char* msg);
        const char* GetMessage();
};

class CMatrix {
    private:
        IMatrix* IM;
        CMatrix& operator=(const CMatrix&) {return *this;};
    public:
        CMatrix();

		virtual HRESULT_ __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall DetMatrix(double *a, double *det, int n);

        ~CMatrix();
};

class CMatrixA {
    private:
        IMatrix* IM;
        IMatrixA* IMA;
        CMatrixA& operator=(const CMatrixA&) {return *this;};
    public:
        CMatrixA();

        virtual HRESULT_ __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall DetMatrix(double *a, double *det, int n);

        virtual HRESULT_ __stdcall AddMatrix(double *a, double *b, double *c, int n, int m);
        virtual HRESULT_ __stdcall MultMatrix(double *a, double *b, double *c, int n, int m, int p);
		virtual HRESULT_ __stdcall TransMatrix(double *a, double *b, int n);
		virtual HRESULT_ __stdcall InverseMatrix(double *a, double *b, int n);

        ~CMatrixA();
};