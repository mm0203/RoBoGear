//=============================================================================
// DXBuffer.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <main.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class DXBuffer
{
public:

	// �o�b�t�@���
	struct Desc
	{
		const void* pVtx;
		UINT vtxSize;
		UINT vtxCount;
		bool isWrite;
		const void* pIdx;
		UINT idxSize;
		UINT idxCount;
		D3D11_PRIMITIVE_TOPOLOGY topology;
	};
public:
	DXBuffer();
	~DXBuffer();

	HRESULT Create(const Desc& desc);

	void Draw(int count = 0);
	HRESULT Write(void* pVtx);
	HRESULT AssimpWrite(ID3D11DeviceContext* pDC, D3D11_MAPPED_SUBRESOURCE pData);
	HRESULT CreateVertexBuffer(const void* pIdx, UINT size, UINT count, bool isWrite);
	HRESULT CreateIndexBuffer(const void* pVtx, UINT size, UINT count);

private:
	ID3D11Buffer* m_pVtxBuffer;
	UINT m_vtxSize;
	UINT m_vtxCount;

	ID3D11Buffer* m_pIdxBuffer;
	UINT m_idxSize;
	UINT m_idxCount;

	D3D11_PRIMITIVE_TOPOLOGY m_topology;
};

