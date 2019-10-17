#pragma once

#include <windows.h>
#include "dxshared.h"
#include <d3dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "dxerr.h"
#include "DDSTextureLoader.h"
#include "InputHandler.h"

#include <string>
#include <vector>
#include <fstream>

using namespace DirectX;

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

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};

struct VertexGroup {
	int v; //Vertex
	int c; //Tex coord
	int n; //Normal
	bool set = false;
};

enum VertReaderType {
	VERTEX,
	COORDINATE,
	NORMAL,
};

struct LoadedModel {
	std::vector<SimpleVertex> compVertices = std::vector<SimpleVertex>();
	std::vector<WORD> compIndices = std::vector<WORD>();
	std::string textureName = ""; //TODO: Read texture/colour data from MTL
};

struct Face {
	std::vector<VertexGroup> verts = std::vector<VertexGroup>();
};

/* Debug logger */
class Debug {
public:
	static void Log(std::string msg) {
		OutputDebugString(msg.c_str());
		OutputDebugString("\n");
	}
	static void Log(int msg) {
		OutputDebugString(std::to_string(msg).c_str());
		OutputDebugString("\n");
	}
	static void Log(float msg) {
		OutputDebugString(std::to_string(msg).c_str());
		OutputDebugString("\n");
	}
	static void Log(double msg) {
		OutputDebugString(std::to_string(msg).c_str());
		OutputDebugString("\n");
	}
	static void Log(unsigned long msg) {
		OutputDebugString(std::to_string(msg).c_str());
		OutputDebugString("\n");
	}
};

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

	/* Load a model and return its indices and vertexes (todo: make it condense the vertex array, and parse an MTL) */
	LoadedModel LoadModel(std::string path, std::string texture) //TEXTURE PARAM HERE SHOULD BE REMOVED WHEN MTL PARSING IS DONE
	{
		//Open OBJ
		std::ifstream in(path.c_str());
		if (!in) OutputDebugString("Failed to open model file!");

		//Parse the OBJ to vertices/texcoords/normals
		std::vector<XMFLOAT3> verts;
		std::vector<XMFLOAT2> coords;
		std::vector<XMFLOAT3> normals;
		std::vector<Face> faces;
		std::string str;
		while (std::getline(in, str))
		{
			if (str.size() > 0)
			{
				if (str[0] == 'v' && str[1] == ' ')
				{
					str = str.substr(2);
					std::string thisPos = "";
					XMFLOAT3 thisVertPos;
					int vertPosIndex = 0;
					for (int i = 0; i < str.length() + 1; i++)
					{
						if (str[i] == ' ' || i == str.length())
						{
							if (thisPos == "") continue;
							if (vertPosIndex == 0) thisVertPos.x = std::stof(thisPos);
							if (vertPosIndex == 1) thisVertPos.y = std::stof(thisPos);
							if (vertPosIndex == 2) thisVertPos.z = std::stof(thisPos);
							vertPosIndex++;
							thisPos = "";
							continue;
						}
						thisPos += str[i];
					}
					verts.push_back(thisVertPos);
				}
				else if (str[0] == 'v' && str[1] == 't')
				{
					str = str.substr(3);
					std::string thisPos = "";
					XMFLOAT2 thisTexCoord;
					int texCoordIndex = 0;
					for (int i = 0; i < str.length() + 1; i++)
					{
						if (str[i] == ' ' || i == str.length())
						{
							if (thisPos == "") continue;
							if (texCoordIndex == 0) thisTexCoord.x = std::stof(thisPos);
							if (texCoordIndex == 1) thisTexCoord.y = std::stof(thisPos);
							texCoordIndex++;
							thisPos = "";
							continue;
						}
						thisPos += str[i];
					}
					coords.push_back(thisTexCoord);
				}
				else if (str[0] == 'v' && str[1] == 'n')
				{
					str = str.substr(3);
					std::string thisPos = "";
					XMFLOAT3 thisNormal;
					int normalIndex = 0;
					for (int i = 0; i < str.length() + 1; i++)
					{
						if (str[i] == ' ' || i == str.length())
						{
							if (thisPos == "") continue;
							if (normalIndex == 0) thisNormal.x = std::stof(thisPos);
							if (normalIndex == 1) thisNormal.y = std::stof(thisPos);
							if (normalIndex == 2) thisNormal.z = std::stof(thisPos);
							normalIndex++;
							thisPos = "";
							continue;
						}
						thisPos += str[i];
					}
					normals.push_back(thisNormal);
				}
				else if (str[0] == 'f' && str[1] == ' ')
				{
					str = str.substr(2);
					Face thisFace = Face();
					VertexGroup thisVert = VertexGroup();
					VertReaderType next = VertReaderType::VERTEX;
					std::string currentNumber = "";
					for (int i = 0; i < str.length() + 1; i++) {
						char thisChar = str[i];
						if (thisChar == '/' || thisChar == ' ' || i == str.length())
						{
							switch (next) {
							case VertReaderType::VERTEX:
								thisVert.v = std::stoi(currentNumber);
								next = VertReaderType::COORDINATE;
								break;
							case VertReaderType::COORDINATE:
								thisVert.c = std::stoi(currentNumber);
								next = VertReaderType::NORMAL;
								break;
							case VertReaderType::NORMAL:
								thisVert.n = std::stoi(currentNumber);
								next = VertReaderType::VERTEX;
								break;
							}
							thisVert.set = true;
							currentNumber = "";

							if (thisChar == '/') continue;
							if (!thisVert.set) continue;
							thisFace.verts.push_back(thisVert);
							thisVert = VertexGroup();
							continue;
						}
						currentNumber += thisChar;
					}
					faces.push_back(thisFace);
				}
			}
		}
		in.close();

		//Create vertex and index arrays from the data
		LoadedModel thisModel = LoadedModel();
		int totalIndex = 0;
		for (int i = 0; i < faces.size(); i++)
		{
			for (int x = 0; x < faces[i].verts.size(); x++)
			{
				SimpleVertex thisVertInfo = SimpleVertex();
				VertexGroup thisGroup = faces[i].verts[x];
				thisVertInfo.Pos = verts[thisGroup.v - 1];
				thisVertInfo.Tex = coords[thisGroup.c - 1];
				thisModel.compVertices.push_back(thisVertInfo);
				thisModel.compIndices.push_back((WORD)totalIndex);
				totalIndex++;
			}
		}
		thisModel.textureName = texture; //TODO read this info from MTL and parse per model part
		return thisModel;
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