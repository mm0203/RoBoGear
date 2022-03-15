//=============================================================================
// Texture.h
//=============================================================================
// Author  松野 将之
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
// クラス定義
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
	//! テクスチャ横幅
	UINT m_width;
	//! テクスチャ縦幅
	UINT m_height;

	// リソースビュー
	ID3D11ShaderResourceView* m_pSRV;

protected:
	ID3D11Texture2D* m_pTex;
};

template <class T>
void Texture::Filter(T filter)
{
	Clone([this, &filter](void* pData, UINT dataSize, UINT width, UINT height)->void
		{
			// 画像情報取得
			D3D11_TEXTURE2D_DESC texDesc;
			m_pTex->GetDesc(&texDesc);

			// フィルターが適用できるフォーマットかチェック
			if (filter.CheckFormat(texDesc.Format))
			{
				// フィルターを適用
				filter.Apply(pData, dataSize, texDesc.Width, texDesc.Height);
				// 以前のリソースを破棄
				Release();
				// フィルター適用済みデータで作成
				CreateResource(texDesc, pData);
			}
		}
	);
}
//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CTexture
{
public:
	static ID3D11ShaderResourceView* GetTexture(ID3D11Device* d3dDevice, const char* pszFilename)
	{
		// プールから検索
		const auto& itr = m_texturePool_c.find(pszFilename);

		// 既にプールにあったら
		if (m_texturePool_c.end() != itr)
		{
			return itr->second;
		}

		// 新しくロード
		ID3D11ShaderResourceView* tex = nullptr;
		HRESULT hr = CreateTextureFromFile(d3dDevice, pszFilename, &tex);

		// エラー判定
		if (FAILED(hr))
		{
			//MessageBoxA(GetMainWnd(), "テクスチャ読み込みエラー", pszFilename, MB_OK);
			return nullptr;
		}

		// 格納
		m_texturePool_c.emplace(pszFilename, tex);

		return tex;
	}

	static ID3D11ShaderResourceView* GetTexture(ID3D11Device* d3dDevice, const wchar_t* pszFilename)
	{
		// プールから検索

		const auto& itr = m_texturePool_w.find(pszFilename);

		// 既にプールにあったら
		if (m_texturePool_w.end() != itr)
		{
			return itr->second;
		}

		// 新しくロード
		ID3D11ShaderResourceView* tex = nullptr;
		HRESULT hr = CreateTextureFromFile(d3dDevice, pszFilename, &tex);

		// エラー判定
		if (FAILED(hr))
		{
			//MessageBox(GetMainWnd(), L"テクスチャ読み込みエラー", pszFilename, MB_OK);
			return nullptr;
		}

		// 格納
		m_texturePool_w.emplace(pszFilename, tex);

		return tex;
	}
private:

	static std::map<const std::string, ID3D11ShaderResourceView*> m_texturePool_c;
	static std::map<const std::wstring, ID3D11ShaderResourceView*> m_texturePool_w;

	// テクスチャ生成
	static HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
		_In_z_ const wchar_t* szFileName,
		_Out_opt_ ID3D11ShaderResourceView** textureView,
		_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
	);

	// テクスチャ生成
	static HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
		_In_z_ const char* szFileName,
		_Out_opt_ ID3D11ShaderResourceView** textureView,
		_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
	);

};

// テクスチャ生成
HRESULT CreateTextureFromMemory(_In_ ID3D11Device* d3dDevice,
	_In_bytecount_(wicDataSize) const uint8_t* wicData,
	_In_ size_t wicDataSize,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);

// テクスチャ生成
HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const wchar_t* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);

// テクスチャ生成
HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const char* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);
