//=============================================================================
// Graphics.h
//=============================================================================
// Author  松野 将之
//=============================================================================

#pragma once

#include "SamplerState.h"
#include "DepthStencilState.h"
#include <System/Singleton/singleton.h>
#include <Renderer/Texture/Texture.h>
#include <Renderer/Texture/DepthStencil.h>

//=============================================================================
// 
// プロトタイプ宣言
// 
//=============================================================================
// DirectX初期化
HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen);


//=============================================================================
// 
// マクロ定義
// 
//=============================================================================

// ブレンドアルファ定義
enum BlendMode
{
	BLEND_ALPHA,
	BLEND_ADD,	// 加算
	BREND_SUB,	// 減算
	BLEND_MAX
};
// カリング定義
enum CullingMode
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,
	CULL_MAX
};

// 深度バッファ定義
enum DepthStencilKind
{
	DEPTHSTENCIL_OFF,
	DEPTHSTENCIL_ON,
	MAX_DEPTHSTENCIL
};

// サンプラー定義
enum SamplerStateKind
{
	SAMPLER_POINT,
	SAMPLER_LINEAR,
	MAX_SAMPLER
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CGraphics : public CSingleton<CGraphics>
{
public:
	void Init();
	void Uninit();
	void BeginDraw();
	void EndDraw();

	// レンダーターゲット
	void SetRenderTarget(Texture** ppRenderTarget, UINT numView, float* pClearColor = nullptr);
	void SetRenderTargetDefault(float* pClearColor = nullptr);
	void SetDepthStencilView(Texture* pDepthStencilView, bool isClear = false);
	void SetDepthStencilViewDefault(bool isClear = false);

	// サンプラー
	void SetSamplerState(SamplerStateKind kind) { m_pDefSamplerState[kind]->Bind(); }
	void SetSamplerState(CSamplerState* pState) { m_pSamplerState = pState; }
	CSamplerState* GetSamplerState() { return m_pSamplerState; }
	// 深度ステンシル
	void SetDepthStencilState(DepthStencilKind kind) { m_pDefDepthStencilState[kind]->Bind(); }
	void SetDepthStencilState(CDepthStencilState* pState) { m_pDepthStencilState = pState; }
	CDepthStencilState* GetDepthStencilState() { return m_pDepthStencilState; }
	void UpdateTargetView();
	void DrawPostEffect();
private:
	// シングルトンのみで生成を許可
	friend class CSingleton;

	CGraphics() = default;
	~CGraphics() = default;

private:
	Texture* m_pDefRenderTarget;
	Texture* m_pDefDepthStencil;
	Texture* m_pRenderTarget[4];
	UINT m_renderTargetNum;
	Texture* m_pDepthStencilView;
	CSamplerState* m_pDefSamplerState[MAX_SAMPLER];
	CSamplerState* m_pSamplerState;
	CDepthStencilState* m_pDefDepthStencilState[MAX_DEPTHSTENCIL];
	CDepthStencilState* m_pDepthStencilState;
};

// カリング設定
void SetCulling(CullingMode cull);