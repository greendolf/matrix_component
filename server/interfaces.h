#ifndef interfaces_h
#define interfaces_h

using CLSID_ = int;
using IID_ = int;
using HRESULT_ = int;
using ULONG_ = int;

const int IID_IUnknown_ = 0;
const int IID_IMatrix = 1;
const int IID_IMatrixA = 2;


const int S_OK_ = 0;
const int E_NOINTERFACE_ = 1;
const int E_NOCOMPONENT_ = 2;
const int E_OUTOFMEMORY_ = 3;
const int E_DET0_ = 4;

class IUnknown_ {
        public:	
                virtual HRESULT_ __stdcall QueryInterface(const IID_& iid, void** ppv)=0;
                virtual ULONG_ __stdcall AddRef()=0;
                virtual ULONG_ __stdcall Release()=0;
}; 

class IMatrix: public IUnknown_ {
        public:
                virtual HRESULT_ __stdcall AddMatrixNum(double *a, double b, double *c, int n, int m) = 0;
                virtual HRESULT_ __stdcall SubMatrixNum(double *a, double b, double *c, int n, int m) = 0;
                virtual HRESULT_ __stdcall MultMatrixNum(double *a, double b, double *c, int n, int m) = 0;
                virtual HRESULT_ __stdcall DivMatrixNum(double *a, double b, double *c, int n, int m) = 0;
                virtual HRESULT_ __stdcall DetMatrix(double *a, double *det, int n) = 0;
};

class IMatrixA: public IUnknown_ {
        public:
                virtual HRESULT_ __stdcall AddMatrix(double *a, double *b, double *c, int n, int m) = 0;
                virtual HRESULT_ __stdcall MultMatrix(double *a, double *b, double *c, int n, int m, int p) = 0;
                virtual HRESULT_ __stdcall TransMatrix(double *a, double *b, int n) = 0;
                virtual HRESULT_ __stdcall InverseMatrix(double *a, double *b, int n) = 0;
};


HRESULT_ __stdcall CreateInstance(const IID_& iid, void** ppv);

#endif