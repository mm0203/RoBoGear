//=============================================================================
// Graphics.h
//=============================================================================
// Author  ���� ���V
//=============================================================================

#pragma once

#include "SamplerState.h"
#include "DepthStencilState.h"
#include <System/Singleton/singleton.h>
#include <Renderer/Texture/Texture.h>
#include <Renderer/Texture/DepthStencil.h>

//=============================================================================
// 
// �v���g�^�C�v�錾
// 
//=============================================================================
// DirectX������
HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen);


//=============================================================================
// 
// �}�N����`
// 
//=============================================================================

// �u�����h�A���t�@��`
enum BlendMode
{
	BLEND_ALPHA,
	BLEND_ADD,	// ���Z
	BREND_SUB,	// ���Z
	BLEND_MAX
};
// �J�����O��`
enum CullingMode
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,
	CULL_MAX
};

// �[�x�o�b�t�@��`
enum DepthStencilKind
{
	DEPTHSTENCIL_OFF,
	DEPTHSTENCIL_ON,
	MAX_DEPTHSTENCIL
};

// �T���v���[��`
enum SamplerStateKind
{
	SAMPLER_POINT,
	SAMPLER_LINEAR,
	MAX_SAMPLER
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class Graphics : public Singleton<Graphics>
{
public:
	void Init();
	void Uninit();
	void BeginDraw();
	void EndDraw();

	// �����_�[�^�[�Q�b�g
	void SetRenderTarget(Texture** ppRenderTarget, UINT numView, float* pClearColor = nullptr);
	void SetRenderTargetDefault(float* pClearColor = nullptr);
	void SetDepthStencilView(Texture* pDepthStencilView, bool isClear = false);
	void SetDepthStencilViewDefault(bool isClear = false);

	// �T���v���[
	void SetSamplerState(SamplerStateKind kind) { m_pDefSamplerState[kind]->Bind(); }
	void SetSamplerState(SamplerState* pState) { m_pSamplerState = pState; }
	SamplerState* GetSamplerState() { return m_pSamplerState; }
	// �[�x�X�e���V��
	void SetDepthStencilState(DepthStencilKind kind) { m_pDefDepthStencilState[kind]->Bind(); }
	void SetDepthStencilState(DepthStencilState* pState) { m_pDepthStencilState = pState; }
	DepthStencilState* GetDepthStencilState() { return m_pDepthStencilState; }
	void UpdateTargetView();
	void DrawPostEffect();
private:
	// �V���O���g���݂̂Ő���������
	friend class Singleton;

	Graphics() = default;
	~Graphics() = default;

private:
	Texture* m_pDefRenderTarget;
	Texture* m_pDefDepthStencil;
	Texture* m_pRenderTarget[4];
	UINT m_renderTargetNum;
	Texture* m_pDepthStencilView;
	SamplerState* m_pDefSamplerState[MAX_SAMPLER];
	SamplerState* m_pSamplerState;
	DepthStencilState* m_pDefDepthStencilState[MAX_DEPTHSTENCIL];
	DepthStencilState* m_pDepthStencilState;
};

// �J�����O�ݒ�
void SetCulling(CullingMode cull);