#ifndef interfaces_h
#define interfaces_h

#include <windows.h>

class Constants
{
public:
        static IID IID_IUnknown;
        static IID IID_IClassFactory;

        static IID IID_IMatrix;
        static IID IID_IMatrixA;
        static IID IID_IFactoryA;

        static CLSID CLSID_MATRIX;
        static CLSID CLSID_MATRIXA;
        static IID IID_IDispatch;
};

class IMatrix : public IUnknown
{
public:
        virtual HRESULT __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m) = 0;
        virtual HRESULT __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m) = 0;
        virtual HRESULT __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m) = 0;
        virtual HRESULT __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m) = 0;
        virtual HRESULT __stdcall DetMatrix(double *a, double *det, int n) = 0;
};

class IMatrixA : public IUnknown
{
public:
        virtual HRESULT __stdcall AddMatrix(double *a, double *b, double *c, int n, int m) = 0;
        virtual HRESULT __stdcall MultMatrix(double *a, double *b, double *c, int n, int m, int p) = 0;
        virtual HRESULT __stdcall TransMatrix(double *a, double *b, int n) = 0;
        virtual HRESULT __stdcall InverseMatrix(double *a, double *b, int n) = 0;
};

class IFactoryA : public IUnknown
{
public:
        virtual HRESULT __stdcall CreateInstanceA(const IID &iid, void **ppv) = 0;
};

#endif