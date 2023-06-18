#ifndef interfaces_h
#define interfaces_h

#include <windows.h>

class Constants
{
public:
        static IID IID_IUnknown;
        static IID IID_IClassFactory;

        static IID IID_IMatrix;
        static IID IID_IMatrixAdvanced;
        static IID IID_IFactoryAdvanced;

        static CLSID CLSID_Matrix;
        static CLSID CLSID_MatrixAdvanced;
        static IID IID_IDispatch;
};

class IMatrix : public IUnknown
{
public:
        virtual HRESULT __stdcall SetMatrix(double *a, int m, int n) = 0;
        virtual HRESULT __stdcall GetMatrix(double **a, int *m, int *n) = 0;

        virtual HRESULT __stdcall MultMatrixNum(double b) = 0;
        virtual HRESULT __stdcall DivMatrixNum(double b) = 0;
        virtual HRESULT __stdcall DetMatrix(double *det) = 0;
};

class IMatrixAdvanced : public IUnknown
{
public:
        virtual HRESULT __stdcall AddMatrix(double *b) = 0;
        virtual HRESULT __stdcall SubMatrix(double *b) = 0;
        virtual HRESULT __stdcall MultMatrix(double *b, int p) = 0;
        virtual HRESULT __stdcall TransMatrix() = 0;
        virtual HRESULT __stdcall InverseMatrix() = 0;
};

class IFactoryAdvanced : public IUnknown
{
public:
        virtual HRESULT __stdcall CreateInstance(const IID &iid, void **ppv) = 0;
        virtual HRESULT __stdcall CreateInstanceAdvanced(const IID &iid, void **ppv, double* a, int m, int n) = 0;
};

#endif