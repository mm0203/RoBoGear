//=============================================================================
// Texture.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <memory.h>
#include <stdlib.h>
#include "Texture.h"
#include <main.h>


#pragma comment(lib, "DirectXTex")

using namespace DirectX;

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================
std::map < const std::string, ID3D11ShaderResourceView* > CTexture::m_texturePool_c;
std::map<const std::wstring, ID3D11ShaderResourceView*> CTexture::m_texturePool_w;

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
Texture::Texture()
{
	m_width = 0;
	m_height = 0;
	m_pTex = nullptr;
	m_pSRV = nullptr;
}
//=============================================================================
// 
// �f�X�g���N�^
// 
//=============================================================================
Texture::~Texture()
{
	Release();
}

//=============================================================================
// 
// ���
// 
//=============================================================================
void Texture::Release()
{
	
	SAFE_RELEASE(m_pSRV);
	SAFE_RELEASE(m_pTex);
}

//=============================================================================
// 
// �����擾
// 
//=============================================================================
UINT Texture::GetWidth() const
{
	return m_width;
}
//=============================================================================
// 
// �����擾
// 
//=============================================================================
UINT Texture::GetHeight() const
{
	return m_height;
}

//=============================================================================
// 
// ���\�[�X�擾
// 
//=============================================================================
ID3D11ShaderResourceView* Texture::GetResource() const
{
	return m_pSRV;
}

//=============================================================================
// 
// ���\�[�X�̕���
// 
//=============================================================================
void Texture::Clone(std::function<void(void* pData, UINT dataSize, UINT width, UINT height)> func)
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pContext = GetDeviceContext();
	HRESULT hr;

	// �R�s�[�惊�\�[�X�쐬�̂��߂ɁA���\�[�X�̏����擾
	D3D11_TEXTURE2D_DESC texDesc;
	m_pTex->GetDesc(&texDesc);

	// �R�s�[�惊�\�[�X�쐬
	texDesc.BindFlags = 0;
	texDesc.Usage = D3D11_USAGE_STAGING;
	texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	ID3D11Texture2D* pCopyTex;
	hr = pDevice->CreateTexture2D(&texDesc, nullptr, &pCopyTex);
	if (FAILED(hr)) { return; }

	// ���\�[�X���R�s�[
	pContext->CopyResource(pCopyTex, m_pTex);

	// �R�s�[�������\�[�X����ǂݎ��
	D3D11_MAPPED_SUBRESOURCE mapped;
	hr = pContext->Map(pCopyTex, 0, D3D11_MAP_READ, 0, &mapped);
	if (FAILED(hr)) { return; }
	UINT rowPitch = m_width * GetPixelSize(texDesc.Format);
	BYTE* pData = new BYTE[rowPitch * m_height];
	for (UINT i = 0; i < m_height; ++i)
	{
		BYTE* pDst = pData + i * rowPitch;
		BYTE* pSrc = reinterpret_cast<BYTE*>(mapped.pData) + i * mapped.RowPitch;
		memcpy(pDst, pSrc, rowPitch);
	}
	pContext->Unmap(pCopyTex, 0);

	// �ǂݎ�����f�[�^�ɑ΂��ď��������s
	func(pData, rowPitch * m_height, m_width, m_height);
	delete[] pData;
	SAFE_RELEASE(pCopyTex);
}

//=============================================================================
// 
// �s�N�Z���T�C�Y�ݒ�
// 
//=============================================================================
BYTE Texture::GetPixelSize(DXGI_FORMAT format)
{
	switch (format)
	{
	default:
		return 0;
	case DXGI_FORMAT_R32_SINT:
	case DXGI_FORMAT_R32_FLOAT:
	case DXGI_FORMAT_R32_UINT:
	case DXGI_FORMAT_R32_TYPELESS:
		return 4;
	}
}

//=============================================================================
// 
// �e�N�X�`������
// 
//=============================================================================
HRESULT Texture::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// �e�N�X�`���쐬
	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = pData;
	data.SysMemPitch = desc.Width * 4;
	GetDevice()->CreateTexture2D(&desc, pData ? &data : nullptr, &m_pTex);

	// �ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// ����
	return GetDevice()->CreateShaderResourceView(m_pTex, &srvDesc, &m_pSRV);
}

//=============================================================================
// 
// �e�N�X�`������
// 
//=============================================================================
HRESULT CreateTextureFromMemory(_In_ ID3D11Device* d3dDevice,
	_In_bytecount_(wicDataSize) const uint8_t* wicData,
	_In_ size_t wicDataSize,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ TexMetadata* pTexInfo)
{
	*textureView = nullptr;
	TexMetadata meta;
	ScratchImage image;
	HRESULT hr;
	if (wicDataSize >= 18 && memcmp(&wicData[wicDataSize - 18], "TRUEVISION-XFILE.", 18) == 0) {
		hr = LoadFromTGAMemory(wicData, wicDataSize, &meta, image);
	} else if (wicDataSize >= 4 && memcmp(wicData, "DDS ", 4) == 0) {
		hr = LoadFromDDSMemory(wicData, wicDataSize, DDS_FLAGS_FORCE_RGB, &meta, image);
	} else {
		hr = LoadFromWICMemory(wicData, wicDataSize, WIC_FLAGS_FORCE_RGB, &meta, image);
	}
	if (FAILED(hr)) return hr;
	if (pTexInfo) *pTexInfo = meta;
	return CreateShaderResourceView(d3dDevice, image.GetImages(), image.GetImageCount(), meta, textureView);
}

//=============================================================================
// 
// �e�N�X�`������
// 
//=============================================================================
HRESULT CTexture::CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const wchar_t* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ TexMetadata* pTexInfo)
{
	*textureView = nullptr;
	TexMetadata meta;
	ScratchImage image;
	WCHAR wszExt[_MAX_EXT];
	_wsplitpath(szFileName, nullptr, nullptr, nullptr, wszExt);
	HRESULT hr;
	if (_wcsicmp(wszExt, L".tga") == 0)
		hr = LoadFromTGAFile(szFileName, &meta, image);
	else if (_wcsicmp(wszExt, L".dds") == 0)
		hr = LoadFromDDSFile(szFileName, DDS_FLAGS_FORCE_RGB, &meta, image);
	else
		hr = LoadFromWICFile(szFileName, WIC_FLAGS_FORCE_RGB, &meta, image);
	if (FAILED(hr)) return hr;
	if (pTexInfo) *pTexInfo = meta;
	return CreateShaderResourceView(d3dDevice, image.GetImages(), image.GetImageCount(), meta, textureView);
}

//=============================================================================
// 
// �e�N�X�`������
// 
//=============================================================================
HRESULT CTexture::CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const char* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ TexMetadata* pTexInfo)
{
	WCHAR wszTexFName[_MAX_PATH];
	int nLen = MultiByteToWideChar(CP_ACP, 0, szFileName, lstrlenA(szFileName), wszTexFName, _countof(wszTexFName));
	if (nLen <= 0) return E_FAIL;
	wszTexFName[nLen] = L'\0';
	return CreateTextureFromFile(d3dDevice, wszTexFName, textureView, pTexInfo);
}


// �t�@�C�����琶��
HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const wchar_t* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ TexMetadata* pTexInfo)
{
	*textureView = nullptr;
	TexMetadata meta;
	ScratchImage image;
	WCHAR wszExt[_MAX_EXT];
	_wsplitpath(szFileName, nullptr, nullptr, nullptr, wszExt);
	HRESULT hr;
	if (_wcsicmp(wszExt, L".tga") == 0)
		hr = LoadFromTGAFile(szFileName, &meta, image);
	else if (_wcsicmp(wszExt, L".dds") == 0)
		hr = LoadFromDDSFile(szFileName, DDS_FLAGS_FORCE_RGB, &meta, image);
	else
		hr = LoadFromWICFile(szFileName, WIC_FLAGS_FORCE_RGB, &meta, image);
	if (FAILED(hr)) return hr;
	if (pTexInfo) *pTexInfo = meta;
	return CreateShaderResourceView(d3dDevice, image.GetImages(), image.GetImageCount(), meta, textureView);
}

HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const char* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ TexMetadata* pTexInfo)
{
	WCHAR wszTexFName[_MAX_PATH];
	int nLen = MultiByteToWideChar(CP_ACP, 0, szFileName, lstrlenA(szFileName), wszTexFName, _countof(wszTexFName));
	if (nLen <= 0) return E_FAIL;
	wszTexFName[nLen] = L'\0';
	return CreateTextureFromFile(d3dDevice, wszTexFName, textureView, pTexInfo);
}
