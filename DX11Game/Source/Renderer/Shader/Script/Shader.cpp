//=============================================================================
// Shader.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

//#define D3DCOMPILER

#include <stdio.h>
#include "Shader.h"
#include <main.h>

#include <d3dcompiler.h>
#ifdef D3DCOMPILER
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler")
#endif

#pragma comment(lib, "d3dcompiler.lib")
//=============================================================================
// 
// シェーダ基本クラス
// 
//=============================================================================

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
Shader::Shader(Kind kind) : m_kind(kind)
{
}
//=============================================================================
// 
//	デストラクタ
// 
//=============================================================================
Shader::~Shader()
{
}

//=============================================================================
// 
// シェーダファイル(*.cso)を読み込む処理
// 
//=============================================================================
HRESULT Shader::Load(const char* pFileName)
{
	HRESULT hr = E_FAIL;

	// ファイルを読み込む
	FILE* fp;
	fp = fopen(pFileName, "rb");
	if (!fp) { return hr; }

	// ファイルのサイズを調べる
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// メモリに読み込み
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);
	fclose(fp);

	// シェーダー作成
	hr = MakeShader(pData, fileSize);

	// 終了処理
	if (pData) { delete[] pData; }
	return hr;
}
//=============================================================================
// 
// 文字列からシェーダをコンパイル
// 
//=============================================================================
HRESULT Shader::Compile(const char* pCode)
{
	static const char* pTargetList[] =
	{
		"vs_5_0",
		"ps_5_0"
	};

	HRESULT hr;
	ID3DBlob* pBlob;
	ID3DBlob* error;
	UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	hr = D3DCompile(pCode, strlen(pCode), nullptr, nullptr, nullptr,
		"main", pTargetList[m_kind], compileFlag, 0, &pBlob, &error);
	if (FAILED(hr)) { return hr; }

	// シェーダ作成
	hr = MakeShader(pBlob->GetBufferPointer(), UINT(pBlob->GetBufferSize()));
	SAFE_RELEASE(pBlob);
	SAFE_RELEASE(error);
	return hr;
}

//=============================================================================
// 
// 頂点シェーダ
// 
//=============================================================================

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
VertexShader::ILList VertexShader::m_ilList;
void VertexShader::ReleaseInputLayout()
{
	ILList::iterator it = m_ilList.begin();
	while (it != m_ilList.end())
	{
		SAFE_RELEASE((it->second));
		++it;
	}
}
//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
VertexShader::VertexShader() : Shader(Shader::VertexShader)
{
	m_pVS = nullptr;
	m_pInputLayout = nullptr;
}

//=============================================================================
// 
// デストラクタ
// 
//=============================================================================
VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_pVS);
}

//=============================================================================
// 
// 頂点シェーダセット
// 
//=============================================================================
void VertexShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	// 使用するシェーダの登録
	pContext->VSSetShader(m_pVS, NULL, 0);
	// 頂点インプットレイアウトをセット
	pContext->IASetInputLayout(m_pInputLayout);
}

//=============================================================================
// 
// 頂点シェーダ生成
// 
//=============================================================================
HRESULT VertexShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	// シェーダ作成
	hr = pDevice->CreateVertexShader(pData, size, NULL, &m_pVS);
	if (FAILED(hr)) { return hr; }

	/*
	シェーダ作成時にシェーダリフレクションを通してインプットレイアウトを取得
	セマンティクスの配置などから識別子を作成
	識別子が登録済→再利用、なければ新規作成
	https://blog.techlab-xe.net/dxc-shader-reflection/
	*/

	ID3D11ShaderReflection* pReflection;
	D3D11_SHADER_DESC shaderDesc;
	D3D11_INPUT_ELEMENT_DESC* pInputDesc;
	D3D11_SIGNATURE_PARAMETER_DESC sigDesc;
	std::string key = "";

	DXGI_FORMAT formats[][4] =
	{
		{
			DXGI_FORMAT_R32_UINT,
			DXGI_FORMAT_R32G32_UINT,
			DXGI_FORMAT_R32G32B32_UINT,
			DXGI_FORMAT_R32G32B32A32_UINT,
		}, {
			DXGI_FORMAT_R32_SINT,
			DXGI_FORMAT_R32G32_SINT,
			DXGI_FORMAT_R32G32B32_SINT,
			DXGI_FORMAT_R32G32B32A32_SINT,
		}, {
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
		},
	};

	// 頂点フォーマットの定義、生成
	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	pReflection->GetDesc(&shaderDesc);
	pInputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
	for (int i = 0; i < shaderDesc.InputParameters; ++i)
	{
		pReflection->GetInputParameterDesc(i, &sigDesc);
		pInputDesc[i].SemanticName = sigDesc.SemanticName;
		pInputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

		// http://marupeke296.com/TIPS_No17_Bit.html
		BYTE elementCount = sigDesc.Mask;
		elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
		elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

		//{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "BONE_INDEX",  0, DXGI_FORMAT_R32G32B32A32_UINT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "BONE_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		switch (sigDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			pInputDesc[i].Format = formats[0][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_SINT32:
			pInputDesc[i].Format = formats[1][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			pInputDesc[i].Format = formats[2][elementCount - 1];
			break;
		}
		pInputDesc[i].InputSlot = 0;
		pInputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		pInputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInputDesc[i].InstanceDataStepRate = 0;

		key += sigDesc.SemanticName;
		key += '0' + sigDesc.SemanticIndex;
	}

	ILList::iterator it = m_ilList.begin();
	while (it != m_ilList.end())
	{
		if (it->first == key)
		{
			m_pInputLayout = it->second;
			break;
		}
		++it;
	}
	if (it == m_ilList.end())
	{
		hr = pDevice->CreateInputLayout(pInputDesc, shaderDesc.InputParameters, pData, size, &m_pInputLayout);
		if (SUCCEEDED(hr))
		{
			m_ilList.insert(ILKey(key, m_pInputLayout));
		}
	}

	SAFE_DELETE_ARRAY(pInputDesc);
	return hr;
}
//=============================================================================
// 
// ピクセルシェーダ
// 
//=============================================================================

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
PixelShader::PixelShader() : Shader(Shader::PixelShader)
{
	m_pPS = nullptr;
}

//=============================================================================
// 
// デストラクタ
// 
//=============================================================================
PixelShader::~PixelShader()
{
	SAFE_RELEASE(m_pPS);
}

//=============================================================================
// 
// ピクセルシェーダセット
// 
//=============================================================================
void PixelShader::Bind(void)
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->PSSetShader(m_pPS, nullptr, 0);
}
//=============================================================================
// 
// ピクセルシェーダ生成
// 
//=============================================================================
HRESULT PixelShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreatePixelShader(pData, size, NULL, &m_pPS);
	return hr;
}
//=============================================================================
// 
// 定数バッファ
// 
//=============================================================================

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
ConstantBuffer::ConstantBuffer()
{
	m_pBuffer = nullptr;
}

//=============================================================================
// 
// デストラクタ
// 
//=============================================================================
ConstantBuffer::~ConstantBuffer()
{
	SAFE_RELEASE(m_pBuffer);
}

//=============================================================================
// 
// 定数バッファ生成
// 
//=============================================================================
HRESULT ConstantBuffer::Create(UINT size)
{
	/* 定数バッファ作成時の注意
	定数バッファの大きさは4バイト区切り(4バイトアライメント)でないと作成できない
	*/
	HRESULT hr;

	// 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	// 定数バッファの大きさは4バイト区切り
	bufDesc.ByteWidth = size;
	// GPU上からしかID3D11Bufferの内容にアクセスできないように
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	// ID3D11Bufferを定数バッファとして使うように宣言
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// バッファの作成
	ID3D11Device* pDevice = GetDevice();
	// 第1引数：作成するID3D11Bufferの情報を表す
	// 第2引数：初期データ
	// 第3引数：作成したID3D11Bufferを受け取る変数	
	hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);

	return hr;
}

//=============================================================================
// 
// バッファ書き込み
// 
//=============================================================================
void ConstantBuffer::Write(const void* pData)
{
	// 定数バッファへの書き込み
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->UpdateSubresource(m_pBuffer, 0, nullptr, pData, 0, 0);
}

//=============================================================================
// 
// 頂点シェーダセット
// 
//=============================================================================
void ConstantBuffer::BindVS(UINT slot)
{
	/*
	定数バッファのデータを送る際、
	どの位置に格納するかを1つ目の引数(StartSlot)に指定する。
	hlslのコードではregister(bX)でバッファの格納位置を決めておく。
	*/
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}
//=============================================================================
// 
// ピクセルシェーダセット
// 
//=============================================================================
void ConstantBuffer::BindPS(UINT slot)
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
}
//=============================================================================
// 
// 頂点シェーダにテクスチャをセット
// 
//=============================================================================
void SetTextureVS(Texture* pTex, UINT slot)
{
	ID3D11ShaderResourceView* pResource = pTex->GetResource();
	GetDeviceContext()->VSSetShaderResources(slot, 1, &pResource);
}

//=============================================================================
// 
// ピクセルシェーダにテクスチャをセット
// 
//=============================================================================
void SetTexturePS(Texture* pTex, UINT slot)
{
	ID3D11ShaderResourceView* pResource = pTex->GetResource();
	GetDeviceContext()->PSSetShaderResources(slot, 1, &pResource);
}