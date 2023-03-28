#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "interfaces.h"

class Matrix: public IMatrix {
	private:
	    int fRefCount;
	public:
		Matrix();
	    ~Matrix();

	    virtual HRESULT_ __stdcall QueryInterface(const IID_& iid, void** ppv);
	    virtual ULONG_ __stdcall AddRef();
	    virtual ULONG_ __stdcall Release();

		virtual HRESULT_ __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall DetMatrix(double *a, double *det, int n);
};

class MatrixA: public IMatrix, IMatrixA {
	private:
	    int fRefCount;
	public:
	    MatrixA();
	    ~MatrixA();

	    virtual HRESULT_ __stdcall QueryInterface(const IID_& iid, void** ppv);
	    virtual ULONG_ __stdcall AddRef();
	    virtual ULONG_ __stdcall Release();

		virtual HRESULT_ __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m);
        virtual HRESULT_ __stdcall DetMatrix(double *a, double *det, int n);

        virtual HRESULT_ __stdcall AddMatrix(double *a, double *b, double *c, int n, int m);
        virtual HRESULT_ __stdcall MultMatrix(double *a, double *b, double *c, int n, int m, int p);
		virtual HRESULT_ __stdcall TransMatrix(double *a, double *b, int n);
		virtual HRESULT_ __stdcall InverseMatrix(double *a, double *b, int n);
        
};

class Factory: public IFactory {
	private:
		int fRefCount;
	public:
		virtual HRESULT_ __stdcall QueryInterface(const IID_& iid, void** ppv);
	    virtual ULONG_ __stdcall AddRef();
	    virtual ULONG_ __stdcall Release();

		virtual HRESULT_ __stdcall CreateInstance(const IID_& iid, void** ppv);
};

class FactoryA: public IFactory {
	private:
		int fRefCount;
	public:
		virtual HRESULT_ __stdcall QueryInterface(const IID_& iid, void** ppv);
	    virtual ULONG_ __stdcall AddRef();
	    virtual ULONG_ __stdcall Release();

		virtual HRESULT_ __stdcall CreateInstance(const IID_& iid, void** ppv);
};

#endif // SERVER_H_INCLUDED