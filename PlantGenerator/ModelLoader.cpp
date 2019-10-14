#include "ModelLoader.h"
#include <fstream>
#include <vector>

struct VertexGroup {
	int v; //Vertex
	int c; //Tex coord
	int n; //Normal
	bool set = false;
};

struct Face {
	std::vector<VertexGroup> verts = std::vector<VertexGroup>();
};

enum VertReaderType {
	VERTEX,
	COORDINATE,
	NORMAL,
};

/* Create basic resources */
void ModelLoader::Create()
{
	GameObject::Create();

	//Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	Utilities dxutils = Utilities();
	HR(dxutils.CompileShaderFromFile(L"cube.fx", "VS", "vs_4_0", &pVSBlob));

	//Create the vertex shader
	HR(dxshared::m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_vertexShader));

	//Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	//Create the input layout
	HR(dxshared::m_pDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_vertexLayout));
	pVSBlob->Release();

	//Set the input layout
	dxshared::m_pImmediateContext->IASetInputLayout(m_vertexLayout);

	//Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	HR(dxutils.CompileShaderFromFile(L"cube.fx", "PS", "ps_4_0", &pPSBlob));

	//Create the pixel shader
	HR(dxshared::m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pixelShader));
	pPSBlob->Release();

	//Load the texture
	HR(CreateDDSTextureFromFile(dxshared::m_pDevice, L"models/garfield.dds", nullptr, &g_pTextureRV));

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(dxshared::m_pDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear));
}

/* Release the model */
void ModelLoader::Release()
{
	GameObject::Release();

	Memory::SafeRelease(g_pVertexBuffer);
	Memory::SafeRelease(g_pIndexBuffer);
	Memory::SafeRelease(m_vertexShader);
	Memory::SafeRelease(m_pixelShader);
	Memory::SafeRelease(g_pTextureRV);
}

/* Update the model */
void ModelLoader::Update(float dt)
{
	if (vertexCount == 0 && indexCount == 0) return;

	GameObject::Update(dt);
}

/* Render the model */
void ModelLoader::Render(float dt)
{
	if (vertexCount == 0 && indexCount == 0) return;

	GameObject::Render(dt);

	//Set shaders to use
	dxshared::m_pImmediateContext->VSSetShader(m_vertexShader, nullptr, 0);
	dxshared::m_pImmediateContext->PSSetShader(m_pixelShader, nullptr, 0);

	//Set index buffer 
	dxshared::m_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//Set vertex buffer 
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	dxshared::m_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	//Set texture and sampler
	dxshared::m_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
	dxshared::m_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);

	//Draw
	dxshared::m_pImmediateContext->DrawIndexed(indexCount, 0, 0);
}

/* Load a model file (obj) */
void ModelLoader::LoadModel(std::string path)
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
				for (int i = 0; i < str.length()+1; i++)
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
				for (int i = 0; i < str.length()+1; i++)
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
				for (int i = 0; i < str.length()+1; i++)
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
				for (int i = 0; i < str.length()+1; i++) {
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
	std::vector<SimpleVertex> compVertices = std::vector<SimpleVertex>();
	std::vector<WORD> compIndices = std::vector<WORD>();
	int totalIndex = 0;
	for (int i = 0; i < faces.size(); i++) 
	{
		for (int x = 0; x < faces[i].verts.size(); x++)
		{
			SimpleVertex thisVertInfo = SimpleVertex();
			VertexGroup thisGroup = faces[i].verts[x];
			thisVertInfo.Pos = verts[thisGroup.v - 1];
			thisVertInfo.Tex = coords[thisGroup.c - 1];
			compVertices.push_back(thisVertInfo);
			compIndices.push_back((WORD)totalIndex);
			totalIndex++;
		}
	}

	//Create vertex buffer 
	vertexCount = compVertices.size();
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = compVertices.data();
	HR(dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer));

	//Create index buffer 
	indexCount = compIndices.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = compIndices.data();
	HR(dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer));
}
