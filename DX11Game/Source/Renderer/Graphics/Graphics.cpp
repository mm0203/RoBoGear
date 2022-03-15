//=============================================================================
// CGraphics.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include <main.h>
#include "Graphics.h"
#include <Renderer/Texture/TextureFactory.h>
#include <Renderer/Texture/RenderTarget.h>

//=============================================================================
// 
// �O���[�o���ϐ�
// 
//=============================================================================
ID3D11Device* g_pDevice;				// �f�o�C�X
ID3D11DeviceContext* g_pDeviceContext;	// �f�o�C�X�R���e�L�X�g
IDXGISwapChain* g_pSwapChain;			// �X���b�v�`�F�[��

ID3D11RasterizerState* g_pRasterizer[MAX_CULLMODE];	 // ���X�^���C�U �X�e�[�g
ID3D11BlendState* g_pBlendState[MAX_BLENDSTATE];	 // �u�����h �X�e�[�g
//PostProcessing g_postEffect;
//=============================================================================
// 
// DirectX������
// 
//=============================================================================
HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen)
{
	HRESULT hr = S_OK;

	// �X���b�v�`�F�C���̐ݒ�
	// �X���b�v�`�F�C���Ƃ́A�E�C���h�E�ւ̕\���_�u���o�b�t�@���Ǘ�����
	// �}���`�T���v�����O�A���t���b�V�����[�g���ݒ�ł���
	// �����̃o�b�N�o�b�t�@���쐬�ł���
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
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_11_0,		// DirectX11�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_0,		// DirectX10�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_1		// Direct9.1�Ή�GPU���x��
	};

	// �X���b�v�`�F�C������
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &scd,
		&g_pSwapChain, &g_pDevice, nullptr, &g_pDeviceContext);
	if (FAILED(hr)) return hr;

	// ���X�^���C�Y�ݒ�
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

	// �A���t�@�u�����h
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
// ������
// 
//=============================================================================
void CGraphics::Init()
{
	// �����_�[�^�[�Q�b�g�r���[����
	m_pDefRenderTarget = CTextureFactory::CreateRenderTargetFromScreen();
	// �e�N�X�`��->�[�x�o�b�t�@�^�[�Q�b�g
	m_pDefDepthStencil = CTextureFactory::CreateDepthStencil(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	m_pDefRenderTarget->GetResource();
	// �T���v���[������ ����
	m_pDefSamplerState[SAMPLER_POINT] = new CSamplerState;
	m_pDefSamplerState[SAMPLER_POINT]->Create(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
	m_pDefSamplerState[SAMPLER_LINEAR] = new CSamplerState;
	m_pDefSamplerState[SAMPLER_LINEAR]->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
	// �f�v�X�X�e���V�������� ����
	m_pDefDepthStencilState[DEPTHSTENCIL_OFF] = new CDepthStencilState;
	m_pDefDepthStencilState[DEPTHSTENCIL_OFF]->Create(false, false);
	m_pDefDepthStencilState[DEPTHSTENCIL_ON] = new CDepthStencilState;
	m_pDefDepthStencilState[DEPTHSTENCIL_ON]->Create(true, false);

	// �����l�ݒ�
	m_pDepthStencilView = m_pDefDepthStencil;
	SetRenderTargetDefault();
	SetDepthStencilViewDefault();
	SetSamplerState(SAMPLER_LINEAR);
	SetDepthStencilState(DEPTHSTENCIL_ON);

	//g_postEffect.Init(g_pDevice);
}

//=============================================================================
// 
// �I��
// 
//=============================================================================
void CGraphics::Uninit()
{
	SAFE_DELETE(m_pDefDepthStencilState[DEPTHSTENCIL_OFF]);
	SAFE_DELETE(m_pDefDepthStencilState[DEPTHSTENCIL_ON]);
	SAFE_DELETE(m_pDefSamplerState[SAMPLER_LINEAR]);
	SAFE_DELETE(m_pDefSamplerState[SAMPLER_POINT]);
	SAFE_DELETE(m_pDefDepthStencil);
	SAFE_DELETE(m_pDefRenderTarget);

	//g_postEffect.Uninit();

	// �u�����h �X�e�[�g���
	for (int i = 0; i < MAX_BLENDSTATE; ++i)
		SAFE_RELEASE(g_pBlendState[i]);

	// ���X�^���C�U �X�e�[�g���
	for (int i = 0; i < MAX_CULLMODE; ++i)
		SAFE_RELEASE(g_pRasterizer[i]);

	// �o�b�N�o�b�t�@���
	if (g_pDeviceContext)
		g_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	// �X���b�v�`�F�[�����
	SAFE_RELEASE(g_pSwapChain);
	// �f�o�C�X �R���e�L�X�g�̊J��
	SAFE_RELEASE(g_pDeviceContext);
	// �f�o�C�X�̊J��
	SAFE_RELEASE(g_pDevice);
}

//=============================================================================
// 
// �`�揉���ݒ�
// 
//=============================================================================
void CGraphics::BeginDraw()
{
	float color[4] = { 0.8f, 0.8f, 0.9f, 1.0f };
	ID3D11RenderTargetView* pRTV = reinterpret_cast<CRenderTarget*>(m_pDefRenderTarget)->GetView();
	ID3D11DepthStencilView* pDSV = reinterpret_cast<CDepthStencil*>(m_pDefDepthStencil)->GetView();
	g_pDeviceContext->ClearRenderTargetView(pRTV, color);
	g_pDeviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//=============================================================================
// 
// �X���b�v�`�F�C���X�V
// 
//=============================================================================
void CGraphics::EndDraw()
{
	g_pSwapChain->Present(0, 0);
}

//=============================================================================
// 
// �����_���[�ݒ�
// 
//=============================================================================
void CGraphics::SetRenderTarget(Texture** ppRenderTarget, UINT numView, float* pClearColor)
{
	// �X�V�`�F�b�N
	if (!ppRenderTarget || !ppRenderTarget[0])	return;

	// �����_�[�^�[�Q�b�g�X�V
	//m_renderTargetNum = min(numView, 4);
	m_renderTargetNum = (((numView) < (4)) ? (numView) : (4));
	for (UINT i = 0; i < m_renderTargetNum; ++i)
		m_pRenderTarget[i] = ppRenderTarget[i];

	// �e�^�[�Q�b�g�r���[�������_�[�^�[�Q�b�g�ɐݒ�
	UpdateTargetView();

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<FLOAT>(m_pRenderTarget[0]->GetWidth());
	vp.Height = static_cast<FLOAT>(m_pRenderTarget[0]->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_pDeviceContext->RSSetViewports(1, &vp);

	// �N���A
	if (pClearColor)
	{
		for (UINT i = 0; i < m_renderTargetNum; ++i)
		{
			ID3D11RenderTargetView* pRTV = reinterpret_cast<CRenderTarget*>(m_pRenderTarget[i])->GetView();
			g_pDeviceContext->ClearRenderTargetView(pRTV, pClearColor);
		}
	}
}
//=============================================================================
// 
// �����_���[�����ݒ�
// 
//=============================================================================
void CGraphics::SetRenderTargetDefault(float* pClearColor)
{
	SetRenderTarget(&m_pDefRenderTarget, 1, pClearColor);
}
//=============================================================================
// 
// �[�x�o�b�t�@�ݒ�
// 
//=============================================================================
void CGraphics::SetDepthStencilView(Texture* pDepthStencilView, bool isClear)
{
	// �X�V�`�F�b�N
	if (!pDepthStencilView || m_pDepthStencilView == pDepthStencilView)
	{
		return;
	}

	// �[�x�o�b�t�@�ݒ�
	m_pDepthStencilView = pDepthStencilView;
	UpdateTargetView();

	// �o�b�t�@�N���A
	if (isClear)
	{
		CDepthStencil* pDSV = reinterpret_cast<CDepthStencil*>(m_pDepthStencilView);
		g_pDeviceContext->ClearDepthStencilView(
			pDSV->GetView(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			// �[�x�l���������������̒l
			// �J�������f����͈͍͂ŏI�I��0~1�͈̔͂Ɋۂ߂��邽�߁A1����ԉ��ɂȂ�B
			1.0f,
			0
		);
	}
}

//=============================================================================
// 
// �[�x�o�b�t�@�����ݒ�
// 
//=============================================================================
void CGraphics::SetDepthStencilViewDefault(bool isClear)
{
	SetDepthStencilView(m_pDefDepthStencil, isClear);
}

//=============================================================================
// 
// �����_�[�^�[�Q�b�g�X�V
// 
//=============================================================================
void CGraphics::UpdateTargetView()
{
	// �����_�[�^�[�Q�b�g�擾
	ID3D11RenderTargetView* pRTV[4] = {};
	for (UINT i = 0; i < m_renderTargetNum && i < 4; ++i)
	{
		pRTV[i] = reinterpret_cast<CRenderTarget*>(m_pRenderTarget[i])->GetView();
	}
	// �[�x�X�e���V���擾
	CDepthStencil* pDSV = reinterpret_cast<CDepthStencil*>(m_pDepthStencilView);
	// �ݒ�
	g_pDeviceContext->OMSetRenderTargets(m_renderTargetNum, pRTV, pDSV->GetView());
}
//=============================================================================
// 
// �f�o�C�X�擾
// 
//=============================================================================
ID3D11Device* GetDevice()
{ 
	return g_pDevice;
}

//=============================================================================
// 
// �X���b�v�`�F�C���擾
// 
//=============================================================================
IDXGISwapChain* GetSwapChain() 
{ 
	return g_pSwapChain; 
}

//=============================================================================
// 
// �f�o�C�X�R���e�L�X�g�擾
// 
//=============================================================================
ID3D11DeviceContext* GetDeviceContext() 
{ 
	return g_pDeviceContext;
}

//=============================================================================
// 
// �u�����h�X�e�[�g�ݒ�
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
// �J�����O
// 
//=============================================================================
void SetCulling(CullingMode cull)
{
	g_pDeviceContext->RSSetState(g_pRasterizer[cull]);
}
