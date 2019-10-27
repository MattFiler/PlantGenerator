#include "dxshared.h"

/* Init shared values */
ID3D11Device* dxshared::m_pDevice = nullptr;
ID3D11DeviceContext* dxshared::m_pImmediateContext = nullptr;

UINT dxshared::m_renderWidth = 0;
UINT dxshared::m_renderHeight = 0;

DirectX::XMMATRIX dxshared::mView;
DirectX::XMMATRIX dxshared::mProjection;

DirectX::XMFLOAT4 dxshared::ambientLightColour;

bool dxshared::enableDebug = false;