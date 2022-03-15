//=============================================================================
// Texture.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#ifdef _MSC_VER
#pragma once
#endif

#include <d3d11.h>
#include <DirectXTex.h>
#include <string>
#include <map>
#include <functional>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <stdint.h>
#pragma warning(pop)
//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class Texture
{
public:
	friend class CTextureFactory;

public:
	Texture();
	virtual ~Texture();
	virtual void Release();

	template <class T>
	void Filter(T filter);

	UINT GetWidth() const;
	UINT GetHeight() const;
	ID3D11ShaderResourceView* GetResource() const;

private:
	void Clone(std::function<void(void* pData, UINT dataSize, UINT width, UINT height)>);
	BYTE GetPixelSize(DXGI_FORMAT format);
protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	//! �e�N�X�`������
	UINT m_width;
	//! �e�N�X�`���c��
	UINT m_height;

	// ���\�[�X�r���[
	ID3D11ShaderResourceView* m_pSRV;

protected:
	ID3D11Texture2D* m_pTex;
};

template <class T>
void Texture::Filter(T filter)
{
	Clone([this, &filter](void* pData, UINT dataSize, UINT width, UINT height)->void
		{
			// �摜���擾
			D3D11_TEXTURE2D_DESC texDesc;
			m_pTex->GetDesc(&texDesc);

			// �t�B���^�[���K�p�ł���t�H�[�}�b�g���`�F�b�N
			if (filter.CheckFormat(texDesc.Format))
			{
				// �t�B���^�[��K�p
				filter.Apply(pData, dataSize, texDesc.Width, texDesc.Height);
				// �ȑO�̃��\�[�X��j��
				Release();
				// �t�B���^�[�K�p�ς݃f�[�^�ō쐬
				CreateResource(texDesc, pData);
			}
		}
	);
}
//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CTexture
{
public:
	static ID3D11ShaderResourceView* GetTexture(ID3D11Device* d3dDevice, const char* pszFilename)
	{
		// �v�[�����猟��
		const auto& itr = m_texturePool_c.find(pszFilename);

		// ���Ƀv�[���ɂ�������
		if (m_texturePool_c.end() != itr)
		{
			return itr->second;
		}

		// �V�������[�h
		ID3D11ShaderResourceView* tex = nullptr;
		HRESULT hr = CreateTextureFromFile(d3dDevice, pszFilename, &tex);

		// �G���[����
		if (FAILED(hr))
		{
			//MessageBoxA(GetMainWnd(), "�e�N�X�`���ǂݍ��݃G���[", pszFilename, MB_OK);
			return nullptr;
		}

		// �i�[
		m_texturePool_c.emplace(pszFilename, tex);

		return tex;
	}

	static ID3D11ShaderResourceView* GetTexture(ID3D11Device* d3dDevice, const wchar_t* pszFilename)
	{
		// �v�[�����猟��

		const auto& itr = m_texturePool_w.find(pszFilename);

		// ���Ƀv�[���ɂ�������
		if (m_texturePool_w.end() != itr)
		{
			return itr->second;
		}

		// �V�������[�h
		ID3D11ShaderResourceView* tex = nullptr;
		HRESULT hr = CreateTextureFromFile(d3dDevice, pszFilename, &tex);

		// �G���[����
		if (FAILED(hr))
		{
			//MessageBox(GetMainWnd(), L"�e�N�X�`���ǂݍ��݃G���[", pszFilename, MB_OK);
			return nullptr;
		}

		// �i�[
		m_texturePool_w.emplace(pszFilename, tex);

		return tex;
	}
private:

	static std::map<const std::string, ID3D11ShaderResourceView*> m_texturePool_c;
	static std::map<const std::wstring, ID3D11ShaderResourceView*> m_texturePool_w;

	// �e�N�X�`������
	static HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
		_In_z_ const wchar_t* szFileName,
		_Out_opt_ ID3D11ShaderResourceView** textureView,
		_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
	);

	// �e�N�X�`������
	static HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
		_In_z_ const char* szFileName,
		_Out_opt_ ID3D11ShaderResourceView** textureView,
		_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
	);

};

// �e�N�X�`������
HRESULT CreateTextureFromMemory(_In_ ID3D11Device* d3dDevice,
	_In_bytecount_(wicDataSize) const uint8_t* wicData,
	_In_ size_t wicDataSize,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);

// �e�N�X�`������
HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const wchar_t* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);

// �e�N�X�`������
HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const char* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);
