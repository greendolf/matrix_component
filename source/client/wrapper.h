#pragma once

#include "interfaces.h"

typedef HRESULT __stdcall (*FunctionType) (const CLSID& clsid, const IID& iid, void** ppv);

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
        HINSTANCE h;
        CMatrix& operator=(const CMatrix&) {return *this;};
    public:
        CMatrix();

		virtual HRESULT __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT __stdcall DetMatrix(double *a, double *det, int n);

        ~CMatrix();
};

class CMatrixA {
    private:
        IMatrix* IM;
        IMatrixA* IMA;
        HINSTANCE h;
        CMatrixA& operator=(const CMatrixA&) {return *this;};
    public:
        CMatrixA();

        virtual HRESULT __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT __stdcall DetMatrix(double *a, double *det, int n);

        virtual HRESULT __stdcall AddMatrix(double *a, double *b, double *c, int n, int m);
        virtual HRESULT __stdcall MultMatrix(double *a, double *b, double *c, int n, int m, int p);
		virtual HRESULT __stdcall TransMatrix(double *a, double *b, int n);
		virtual HRESULT __stdcall InverseMatrix(double *a, double *b, int n);

        ~CMatrixA();
};