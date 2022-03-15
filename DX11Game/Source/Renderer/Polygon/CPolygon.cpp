//=============================================================================
// CPolygon.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "CPolygon.h"

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CPolygon::CPolygon()
{
	Init();
}

//=============================================================================
// 
// �f�X�g���N�^
// 
//=============================================================================
CPolygon::~CPolygon()
{
	if (m_pTex && m_isLoadTex) SAFE_RELEASE(m_pTex);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CPolygon::Init()
{
	// �����o�ϐ�������
	m_pTex = nullptr;
	m_Pos = XMFLOAT2(0.0f, 0.0f);
	m_Size = XMFLOAT2(1.0f, 1.0f);
	m_UV = XMFLOAT2(0.0f, 0.0f);
	m_FrameSize = XMFLOAT2(1.0f, 1.0f);
	m_PolygonAngle = 0.0f;
	m_Alpha = 1.0f;
	m_Color = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CPolygon::Draw()
{
	SetBlendState(BS_ALPHABLEND);
	CSingleton<CGraphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_OFF);
	//SetZBuffer(false);
	// �|���S�����Z�b�g
	if (m_pTex != nullptr)	SetPolygonTexture(m_pTex);
	else SetPolygonTexture(nullptr);
	SetPolygonPos(m_Pos.x, m_Pos.y);
	SetPolygonSize(m_Size.x, m_Size.y);
	SetPolygonAngle(m_PolygonAngle);
	SetPolygonUV(m_UV.x, m_UV.y);
	SetPolygonFrameSize(m_FrameSize.x, m_FrameSize.y);
	SetPolygonColor(m_Color.x, m_Color.y, m_Color.z);
	SetPolygonAlpha(m_Alpha);
	// �`��
	DrawPolygon(GetDeviceContext());
	//SetZWrite(true);
	CSingleton<CGraphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_ON);
	SetBlendState(BS_NONE);
}

//=============================================================================
// 
// �e�N�X�`�����[�h
// 
//=============================================================================
HRESULT CPolygon::LoadTexture(const wchar_t* FileName)
{
	HRESULT hr = S_OK;
	hr = CreateTextureFromFile(GetDevice(), FileName, &m_pTex);
	m_isLoadTex = true;
	return hr;
}

//=============================================================================
// 
// �e�N�X�`�����[�h
// 
//=============================================================================
HRESULT CPolygon::LoadTexture(const char* FileName)
{
	HRESULT hr = S_OK;
	hr = CreateTextureFromFile(GetDevice(), FileName, &m_pTex);
	m_isLoadTex = true;
	return hr;
}