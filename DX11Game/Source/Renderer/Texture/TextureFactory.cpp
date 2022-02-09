//=============================================================================
// TextureFactory.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "TextureFactory.h"
#include "RenderTarget.h"
#include <main.h>
#include <Renderer/Graphics/Graphics.h>
#include <Renderer/Texture/DepthStencil.h>

//=============================================================================
// 
// �e�N�X�`���ݒ�
// 
//=============================================================================
D3D11_TEXTURE2D_DESC MakeTexDesc(DXGI_FORMAT format, UINT width, UINT height)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = format;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	return desc;
}

//=============================================================================
// 
// �t�@�C�����琶��
// 
//=============================================================================
Texture* TextureFactory::CreateFromFile(const char* fileName)
{
#if USE_DIRECTXTEX
	HRESULT hr;

	// �����ϊ�
	wchar_t wPath[MAX_PATH];
	size_t wLen = 0;
	MultiByteToWideChar(0, 0, fileName, -1, wPath, MAX_PATH);

	// �t�@�C���ʓǂݍ���
	DirectX::TexMetadata mdata;
	DirectX::ScratchImage image;
	if (strstr(fileName, ".tga"))
	{
		hr = DirectX::LoadFromTGAFile(wPath, &mdata, image);
	}
	else
	{
		hr = DirectX::LoadFromWICFile(wPath, DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &mdata, image);
	}

	// �V�F�[�_���\�[�X����
	ID3D11ShaderResourceView* pSRV;
	hr = CreateShaderResourceView(GetDevice(), image.GetImages(), image.GetImageCount(), mdata, &pSRV);
	if (FAILED(hr)) { return nullptr; }

	// �C���X�^���X����
	Texture* pTexture = new Texture;
	pTexture->m_pSRV = pSRV;
	pTexture->m_width = mdata.width;
	pTexture->m_height = mdata.height;
	return pTexture;
#else
	return nullptr;
#endif
}

//=============================================================================
// 
// ����
// 
//=============================================================================
Texture* TextureFactory::CreateFromData(DXGI_FORMAT format, UINT width, UINT height, const void* pData)
{
	// �e�N�X�`���ݒ�
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(format, width, height);

	// �C���X�^���X����
	Texture* pTexture = new Texture;
	if (SUCCEEDED(pTexture->CreateResource(desc, pData)))
	{
		pTexture->m_width = width;
		pTexture->m_height = height;
	}
	else
	{
		SAFE_DELETE(pTexture);
	}

	return pTexture;
}
//=============================================================================
// 
// ����
// 
//=============================================================================
Texture* TextureFactory::CreateRenderTarget(DXGI_FORMAT format, UINT width, UINT height)
{
	// �e�N�X�`���ݒ�
	// �����_�[�e�N�X�`������shader���\�[�X�r���[���쐬
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(format, width, height);
	desc.BindFlags |= D3D11_BIND_RENDER_TARGET;

	// �C���X�^���X����
	RenderTarget* pTexture = new RenderTarget;

	// �����_�[�^�[�Q�b�g�r���[�쐬
	if (SUCCEEDED(pTexture->CreateResource(desc)))
	{
		pTexture->m_width = width;
		pTexture->m_height = height;
	}
	else
	{
		SAFE_DELETE(pTexture);
	}
	return pTexture;
}

//=============================================================================
// 
// �����_�[�^�[�Q�b�g�r���[����
// 
//=============================================================================
Texture* TextureFactory::CreateRenderTargetFromScreen()
{
	HRESULT hr;
	RenderTarget* pTexture = new RenderTarget;

	// �o�b�N�o�b�t�@�̃|�C���^���擾
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pTexture->m_pTex);

	// �o�b�N�o�b�t�@�ւ̃|�C���^���w�肵�ă����_�[�^�[�Q�b�g�r���[���쐬
	if (SUCCEEDED(hr))
	{
		hr = GetDevice()->CreateRenderTargetView(pTexture->m_pTex, NULL, &pTexture->m_pRTV);
		if (SUCCEEDED(hr))
		{
			D3D11_TEXTURE2D_DESC desc;
			pTexture->m_pTex->GetDesc(&desc);
			pTexture->m_width = desc.Width;
			pTexture->m_height = desc.Height;
		}
	}

	// �쐬�Ɏ��s���Ă�����폜
	if (FAILED(hr))
	{
		SAFE_DELETE(pTexture);
	}

	return pTexture;
}

//=============================================================================
// 
// �[�x�r���[����
// 
//=============================================================================
Texture* TextureFactory::CreateDepthStencil(UINT width, UINT height, bool useStencil)
{
	// �e�N�X�`���ݒ�
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(
		useStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS, width, height);
	desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;

	// �C���X�^���X����
	DepthStencil* pTexture = new DepthStencil;
	if (SUCCEEDED(pTexture->CreateResource(desc)))
	{
		pTexture->m_width = width;
		pTexture->m_height = height;
	}
	else
	{
		SAFE_DELETE(pTexture);
	}
	return pTexture;
}