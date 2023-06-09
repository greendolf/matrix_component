#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "interfaces2.h"

class Matrix : public IMatrix, public IDispatch
{
private:
	int fRefCount;

public:
	double *matrix;
	int m, n;
	Matrix();
	Matrix(double *a, int n, int m);
	~Matrix();

	virtual HRESULT __stdcall QueryInterface(const IID &iid, void **ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	virtual HRESULT __stdcall SetMatrix(double *a, int n, int m);
	virtual HRESULT __stdcall GetMatrix(double **a);

	virtual HRESULT __stdcall AddMatrixNum(double b, double *c, int n, int m);
	virtual HRESULT __stdcall SubMatrixNum(double b, double *c, int n, int m);
	virtual HRESULT __stdcall MultMatrixNum(double b, double *c, int n, int m);
	virtual HRESULT __stdcall DivMatrixNum(double b, double *c, int n, int m);
	virtual HRESULT __stdcall DetMatrix(double *det, int n);

	virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	virtual HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
	virtual HRESULT __stdcall GetTypeInfoCount(UINT *pctinfo);
	virtual HRESULT __stdcall GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
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
	virtual HRESULT __stdcall CreateInstanceAdvanced(const IID &iid, void **ppv, double *a, int n, int m);

	virtual HRESULT __stdcall LockServer(BOOL fLock);
};

#endif // SERVER_H_INCLUDED