//=============================================================================
// Shader.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

// 警告非表示
//#pragma warning(disable : 4996)

#include <d3d11.h>
#include <map>
#include <string>
#include <Renderer/Texture/Texture.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================

// シェーダ基本クラス
class Shader
{
protected:
	enum Kind
	{
		VertexShader,
		PixelShader
	};
protected:
	Shader(Kind kind);
public:
	virtual ~Shader();
public:
	// シェーダーファイル(*.cso)を読み込む処理
	HRESULT Load(const char* pFileName);
	// 文字列からシェーダをコンパイル
	HRESULT Compile(const char* pCode);

	// シェーダーを描画に使用
	virtual void Bind(void) = 0;

protected:
	// シェーダーファイルを読み込んだ後、シェーダーの種類別に処理を行う
	virtual HRESULT MakeShader(void* pData, UINT size) = 0;

private:
	Kind m_kind;
};

// 頂点シェーダ
class VertexShader : public Shader
{
private:
	using ILKey = std::pair<std::string, ID3D11InputLayout*>;
	using ILList = std::map<std::string, ID3D11InputLayout*>;
public:
	static void ReleaseInputLayout();

	VertexShader();
	~VertexShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	static ILList m_ilList;
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pInputLayout;
};

// ピクセルシェーダ
class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);
private:
	ID3D11PixelShader* m_pPS;
};


// 定数バッファ
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	HRESULT Create(UINT size);
	void Write(const void* pData);
	void BindVS(UINT slot);
	void BindPS(UINT slot);

	ID3D11Buffer& GetBuffer() { return *m_pBuffer; }
private:
	ID3D11Buffer* m_pBuffer;
};

//=============================================================================
// 
// テクスチャセット
// 
//=============================================================================
void SetTextureVS(Texture* pTex, UINT slot = 0);
void SetTexturePS(Texture* pTex, UINT slot = 0);
