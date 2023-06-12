#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "interfaces.h"

class Matrix : public IMatrix, public IDispatch
{
private:
	int fRefCount;

public:
	Matrix();
	~Matrix();

	virtual HRESULT __stdcall QueryInterface(const IID &iid, void **ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	virtual HRESULT __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m);
	virtual HRESULT __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m);
	virtual HRESULT __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m);
	virtual HRESULT __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m);
	virtual HRESULT __stdcall DetMatrix(double *a, double *det, int n);

	virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	virtual HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
	virtual HRESULT __stdcall GetTypeInfoCount(UINT *pctinfo);
	virtual HRESULT __stdcall GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
};

class MatrixAdvanced : public IMatrix, IMatrixAdvanced
{
private:
	int fRefCount;

public:
	MatrixAdvanced();
	~MatrixAdvanced();

	virtual HRESULT __stdcall QueryInterface(const IID &iid, void **ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	virtual HRESULT __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m);
	virtual HRESULT __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m);
	virtual HRESULT __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m);
	virtual HRESULT __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m);
	virtual HRESULT __stdcall DetMatrix(double *a, double *det, int n);

	virtual HRESULT __stdcall AddMatrix(double *a, double *b, double *c, int n, int m);
	virtual HRESULT __stdcall MultMatrix(double *a, double *b, double *c, int n, int m, int p);
	virtual HRESULT __stdcall TransMatrix(double *a, double *b, int n);
	virtual HRESULT __stdcall InverseMatrix(double *a, double *b, int n);

};

class Factory : public IClassFactory, IFactoryAdvanced
{
private:
	int fRefCount;

public:
	virtual HRESULT __stdcall QueryInterface(const IID &iid, void **ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	virtual HRESULT __stdcall CreateInstance(IUnknown *pUnkOuter, const IID &iid, void **ppv);
	virtual HRESULT __stdcall CreateInstance(const IID &iid, void **ppv);

	virtual HRESULT __stdcall LockServer(BOOL fLock);
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

	virtual HRESULT __stdcall LockServer(BOOL fLock);
};

#endif // SERVER_H_INCLUDED