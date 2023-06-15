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
    CMatrix(double *a, int n, int m);

    virtual HRESULT __stdcall AddMatrixNum(double b, double *c, int n, int m);
    virtual HRESULT __stdcall SubMatrixNum(double b, double *c, int n, int m);
    virtual HRESULT __stdcall MultMatrixNum(double b, double *c, int n, int m);
    virtual HRESULT __stdcall DivMatrixNum(double b, double *c, int n, int m);
    virtual HRESULT __stdcall DetMatrix(double *det, int n);

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
    CMatrixA(double *a, int n, int m);

    virtual HRESULT __stdcall AddMatrixNum(double b, double *c, int n, int m);
    virtual HRESULT __stdcall SubMatrixNum(double b, double *c, int n, int m);
    virtual HRESULT __stdcall MultMatrixNum(double b, double *c, int n, int m);
    virtual HRESULT __stdcall DivMatrixNum(double b, double *c, int n, int m);
    virtual HRESULT __stdcall DetMatrix(double *det, int n);

    virtual HRESULT __stdcall AddMatrix(double *b, double *c, int n, int m);
    virtual HRESULT __stdcall MultMatrix(double *b, double *c, int n, int m, int p);
    virtual HRESULT __stdcall TransMatrix(double *b, int n);
    virtual HRESULT __stdcall InverseMatrix(double *b, int n);

    ~CMatrixA();
};