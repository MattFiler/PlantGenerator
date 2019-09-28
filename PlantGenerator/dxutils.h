#pragma once

#include "dxshared.h"
#include <d3dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "dxerr.h"

/* Handle DX HRESULT errors nicely in debug */
#ifdef _DEBUG
	#ifndef HR
		#define HR(x) { HRESULT hr = x; if (FAILED(hr)) { DXTraceW(__FILEW__, __LINE__, hr, L#x, TRUE); } }
	#endif
#else
	#ifndef HR
		#define HR(x) x;
	#endif
#endif

class Utilities
{
public:
	/* Try and compile a shader from file (function created by Microsoft originally) */
	HRESULT CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		//Request d3d debugging if in debug
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		dwShaderFlags |= D3DCOMPILE_DEBUG;
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		//Try and compile shader, handle errors
		ID3DBlob* pErrorBlob = nullptr;
		HRESULT hr = S_OK;
		hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hr))
		{
			if (pErrorBlob)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
				pErrorBlob->Release();
			}
			return hr;
		}
		if (pErrorBlob) pErrorBlob->Release();

		return S_OK;
	}
};

namespace Memory 
{
	/* Safely delete a pointer */
	template <class T> void SafeDelete(T& t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
		}
	}

	/* Safely delete a pointer array */
	template <class T> void SafeDeleteArray(T& t)
	{
		if (t)
		{
			delete[] t;
			t = nullptr;
		}
	}

	/* Safely release a d3d resource */
	template <class T> void SafeRelease(T& t)
	{
		if (t)
		{
			t->Release();
			t = nullptr;
		}
	}
};