#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "interfaces.h"

class MatrixAdvanced : public IMatrix, IMatrixAdvanced
{
private:
	int fRefCount;
	IMatrix *im;
	double *matrix;
	int n, m;

public:
	MatrixAdvanced();
	MatrixAdvanced(double *a, int n, int m);
	~MatrixAdvanced();

	virtual HRESULT __stdcall QueryInterface(const IID &iid, void **ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	virtual HRESULT __stdcall SetMatrix(double *a, int m, int n);
	virtual HRESULT __stdcall GetMatrix(double **a, int *m, int *n);

	virtual HRESULT __stdcall MultMatrixNum(double b);
	virtual HRESULT __stdcall DivMatrixNum(double b);
	virtual HRESULT __stdcall DetMatrix(double *det);

	virtual HRESULT __stdcall AddMatrix(double *b);
	virtual HRESULT __stdcall SubMatrix(double *b);
	virtual HRESULT __stdcall MultMatrix(double *b, int n2);
	virtual HRESULT __stdcall TransMatrix();
	virtual HRESULT __stdcall InverseMatrix();
};

class FactoryAdvanced : public IClassFactory, IFactoryAdvanced
{
private:
	int fRefCount;

public:
	virtual HRESULT __stdcall QueryInterface(const IID &iid, void **ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	virtual HRESULT __stdcall CreateInstance(IUnknown *pUnkOuter, const IID &iid, void **ppv);
	virtual HRESULT __stdcall CreateInstance(const IID &iid, void **ppv);
	virtual HRESULT __stdcall CreateInstanceAdvanced(const IID &iid, void **ppv, double *a, int m, int n);

	virtual HRESULT __stdcall LockServer(BOOL fLock);
};

#endif // SERVER_H_INCLUDED