//=============================================================================
// Graphics.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include <main.h>
#include "Graphics.h"
#include <Renderer/Texture/TextureFactory.h>
#include <Renderer/Texture/RenderTarget.h>

//=============================================================================
// 
// グローバル変数
// 
//=============================================================================
ID3D11Device* g_pDevice;				// デバイス
ID3D11DeviceContext* g_pDeviceContext;	// デバイスコンテキスト
IDXGISwapChain* g_pSwapChain;			// スワップチェーン

ID3D11RasterizerState* g_pRasterizer[MAX_CULLMODE];	 // ラスタライザ ステート
ID3D11BlendState* g_pBlendState[MAX_BLENDSTATE];	 // ブレンド ステート
//PostProcessing g_postEffect;
//=============================================================================
// 
// DirectX初期化
// 
//=============================================================================
HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen)
{
	HRESULT hr = S_OK;

	// スワップチェインの設定
	// スワップチェインとは、ウインドウへの表示ダブルバッファを管理する
	// マルチサンプリング、リフレッシュレートが設定できる
	// 複数のバックバッファが作成できる
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = fullscreen ? FALSE : TRUE;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1		// Direct9.1対応GPUレベル
	};

	// スワップチェイン生成
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &scd,
		&g_pSwapChain, &g_pDevice, nullptr, &g_pDeviceContext);
	if (FAILED(hr)) return hr;

	// ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[CULL_NONE]);
	rd.CullMode = D3D11_CULL_FRONT;
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[CULL_FRONT]);
	rd.CullMode = D3D11_CULL_BACK;
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[CULL_BACK]);
	g_pDeviceContext->RSSetState(g_pRasterizer[2]);

	// アルファブレンド
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[BLEND_ALPHA]);
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[BLEND_ADD]);
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[BREND_SUB]);
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[BLEND_MAX]);
	SetBlendState(BS_ALPHABLEND);

	return hr;
}

//=============================================================================
// 
// 初期化
// 
//=============================================================================
void Graphics::Init()
{
	// レンダーターゲットビュー生成
	m_pDefRenderTarget = TextureFactory::CreateRenderTargetFromScreen();
	// テクスチャ->深度バッファターゲット
	m_pDefDepthStencil = TextureFactory::CreateDepthStencil(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	m_pDefRenderTarget->GetResource();
	// サンプラー初期化 生成
	m_pDefSamplerState[SAMPLER_POINT] = new SamplerState;
	m_pDefSamplerState[SAMPLER_POINT]->Create(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
	m_pDefSamplerState[SAMPLER_LINEAR] = new SamplerState;
	m_pDefSamplerState[SAMPLER_LINEAR]->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
	// デプスステンシル初期化 生成
	m_pDefDepthStencilState[DEPTHSTENCIL_OFF] = new DepthStencilState;
	m_pDefDepthStencilState[DEPTHSTENCIL_OFF]->Create(false, false);
	m_pDefDepthStencilState[DEPTHSTENCIL_ON] = new DepthStencilState;
	m_pDefDepthStencilState[DEPTHSTENCIL_ON]->Create(true, false);

	// 初期値設定
	m_pDepthStencilView = m_pDefDepthStencil;
	SetRenderTargetDefault();
	SetDepthStencilViewDefault();
	SetSamplerState(SAMPLER_LINEAR);
	SetDepthStencilState(DEPTHSTENCIL_ON);

	//g_postEffect.Init(g_pDevice);
}

//=============================================================================
// 
// 終了
// 
//=============================================================================
void Graphics::Uninit()
{
	SAFE_DELETE(m_pDefDepthStencilState[DEPTHSTENCIL_OFF]);
	SAFE_DELETE(m_pDefDepthStencilState[DEPTHSTENCIL_ON]);
	SAFE_DELETE(m_pDefSamplerState[SAMPLER_LINEAR]);
	SAFE_DELETE(m_pDefSamplerState[SAMPLER_POINT]);
	SAFE_DELETE(m_pDefDepthStencil);
	SAFE_DELETE(m_pDefRenderTarget);

	//g_postEffect.Uninit();

	// ブレンド ステート解放
	for (int i = 0; i < MAX_BLENDSTATE; ++i)
		SAFE_RELEASE(g_pBlendState[i]);

	// ラスタライザ ステート解放
	for (int i = 0; i < MAX_CULLMODE; ++i)
		SAFE_RELEASE(g_pRasterizer[i]);

	// バックバッファ解放
	if (g_pDeviceContext)
		g_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	// スワップチェーン解放
	SAFE_RELEASE(g_pSwapChain);
	// デバイス コンテキストの開放
	SAFE_RELEASE(g_pDeviceContext);
	// デバイスの開放
	SAFE_RELEASE(g_pDevice);
}

//=============================================================================
// 
// 描画初期設定
// 
//=============================================================================
void Graphics::BeginDraw()
{
	float color[4] = { 0.8f, 0.8f, 0.9f, 1.0f };
	ID3D11RenderTargetView* pRTV = reinterpret_cast<RenderTarget*>(m_pDefRenderTarget)->GetView();
	ID3D11DepthStencilView* pDSV = reinterpret_cast<DepthStencil*>(m_pDefDepthStencil)->GetView();
	g_pDeviceContext->ClearRenderTargetView(pRTV, color);
	g_pDeviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//=============================================================================
// 
// スワップチェイン更新
// 
//=============================================================================
void Graphics::EndDraw()
{
	g_pSwapChain->Present(0, 0);
}

//=============================================================================
// 
// レンダラー設定
// 
//=============================================================================
void Graphics::SetRenderTarget(Texture** ppRenderTarget, UINT numView, float* pClearColor)
{
	// 更新チェック
	if (!ppRenderTarget || !ppRenderTarget[0])	return;

	// レンダーターゲット更新
	//m_renderTargetNum = min(numView, 4);
	m_renderTargetNum = (((numView) < (4)) ? (numView) : (4));
	for (UINT i = 0; i < m_renderTargetNum; ++i)
		m_pRenderTarget[i] = ppRenderTarget[i];

	// 各ターゲットビューをレンダーターゲットに設定
	UpdateTargetView();

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<FLOAT>(m_pRenderTarget[0]->GetWidth());
	vp.Height = static_cast<FLOAT>(m_pRenderTarget[0]->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_pDeviceContext->RSSetViewports(1, &vp);

	// クリア
	if (pClearColor)
	{
		for (UINT i = 0; i < m_renderTargetNum; ++i)
		{
			ID3D11RenderTargetView* pRTV = reinterpret_cast<RenderTarget*>(m_pRenderTarget[i])->GetView();
			g_pDeviceContext->ClearRenderTargetView(pRTV, pClearColor);
		}
	}
}
//=============================================================================
// 
// レンダラー初期設定
// 
//=============================================================================
void Graphics::SetRenderTargetDefault(float* pClearColor)
{
	SetRenderTarget(&m_pDefRenderTarget, 1, pClearColor);
}
//=============================================================================
// 
// 深度バッファ設定
// 
//=============================================================================
void Graphics::SetDepthStencilView(Texture* pDepthStencilView, bool isClear)
{
	// 更新チェック
	if (!pDepthStencilView || m_pDepthStencilView == pDepthStencilView)
	{
		return;
	}

	// 深度バッファ設定
	m_pDepthStencilView = pDepthStencilView;
	UpdateTargetView();

	// バッファクリア
	if (isClear)
	{
		DepthStencil* pDSV = reinterpret_cast<DepthStencil*>(m_pDepthStencilView);
		g_pDeviceContext->ClearDepthStencilView(
			pDSV->GetView(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			// 深度値を初期化した時の値
			// カメラが映せる範囲は最終的に0~1の範囲に丸められるため、1が一番奥になる。
			1.0f,
			0
		);
	}
}

//=============================================================================
// 
// 深度バッファ初期設定
// 
//=============================================================================
void Graphics::SetDepthStencilViewDefault(bool isClear)
{
	SetDepthStencilView(m_pDefDepthStencil, isClear);
}

//=============================================================================
// 
// レンダーターゲット更新
// 
//=============================================================================
void Graphics::UpdateTargetView()
{
	// レンダーターゲット取得
	ID3D11RenderTargetView* pRTV[4] = {};
	for (UINT i = 0; i < m_renderTargetNum && i < 4; ++i)
	{
		pRTV[i] = reinterpret_cast<RenderTarget*>(m_pRenderTarget[i])->GetView();
	}
	// 深度ステンシル取得
	DepthStencil* pDSV = reinterpret_cast<DepthStencil*>(m_pDepthStencilView);
	// 設定
	g_pDeviceContext->OMSetRenderTargets(m_renderTargetNum, pRTV, pDSV->GetView());
}
//=============================================================================
// 
// デバイス取得
// 
//=============================================================================
ID3D11Device* GetDevice()
{ 
	return g_pDevice;
}

//=============================================================================
// 
// スワップチェイン取得
// 
//=============================================================================

IDXGISwapChain* GetSwapChain() 
{ 
	return g_pSwapChain; 
}

//=============================================================================
// 
// デバイスコンテキスト取得
// 
//=============================================================================
ID3D11DeviceContext* GetDeviceContext() 
{ 
	return g_pDeviceContext;
}

//=============================================================================
// 
// ブレンドステート設定
// 
//=============================================================================
void SetBlendState(int nBlendState)
{
	if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE)
	{
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		g_pDeviceContext->OMSetBlendState(g_pBlendState[nBlendState], blendFactor, 0xffffffff);
	}
}
//=============================================================================
// 
// カリング
// 
//=============================================================================
void SetCulling(CullingMode cull)
{
	g_pDeviceContext->RSSetState(g_pRasterizer[cull]);
}

//
//void Graphics::DrawPostEffect()
//{
//	// ポストエフェクトポストエフェクト描画
//	UpdateTargetView();
//	g_postEffect.Draw(g_pDeviceContext);
//}
//
//void SetRenderTarget()
//{
//	// 各ターゲットビューをレンダーターゲットに設定
//	g_pDeviceContext->OMSetRenderTargets(1, &g_postEffect.m_pRenderTargetView, g_postEffect.m_pDepthStencilView);
//}
//
//void PostEffectBuffer()
//{
//	// ポストエフェクトバッファ
//	float color[4] = { 0.8f, 0.8f, 0.9f, 1.0f };
//	g_pDeviceContext->ClearRenderTargetView(g_postEffect.m_pRenderTargetView, color);
//	g_pDeviceContext->ClearDepthStencilView(g_postEffect.m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//}
