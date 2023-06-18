#pragma once

#include "interfaces.h"

// typedef HRESULT __stdcall (*FunctionType) (const CLSID& clsid, const IID& iid, void** ppv);

class EMatrix
{
private:
    const char *msg;

public:
    EMatrix(const char *msg);
    const char *GetMessage();
};

class CMatrix
{
private:
    IMatrix *IM;
    HINSTANCE h;
    CMatrix &operator=(const CMatrix &) { return *this; };

public:
    CMatrix();
    CMatrix(double *a, int m, int n);

    virtual HRESULT __stdcall SetMatrix(double *a, int m, int n);
    virtual HRESULT __stdcall GetMatrix(double **a, int *m, int *n);

    virtual HRESULT __stdcall MultMatrixNum(double b);
    virtual HRESULT __stdcall DivMatrixNum(double b);
    virtual HRESULT __stdcall DetMatrix(double *det);

    ~CMatrix();
};

class CMatrixA
{
private:
    IMatrix *IM;
    IMatrixAdvanced *IMA;
    HINSTANCE h;
    CMatrixA &operator=(const CMatrixA &) { return *this; };

public:
    CMatrixA();
    CMatrixA(double *a, int m, int n);

    virtual HRESULT __stdcall SetMatrix(double *a, int m, int n);
    virtual HRESULT __stdcall GetMatrix(double **a, int *m, int *n);

    virtual HRESULT __stdcall MultMatrixNum(double b);
    virtual HRESULT __stdcall DivMatrixNum(double b);
    virtual HRESULT __stdcall DetMatrix(double *det);

    virtual HRESULT __stdcall AddMatrix(double *b);
    virtual HRESULT __stdcall MultMatrix(double *b, int p);
    virtual HRESULT __stdcall TransMatrix();
    virtual HRESULT __stdcall InverseMatrix();

    ~CMatrixA();
};