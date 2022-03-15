//=============================================================================
// StartLogo.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "StartLogo.h"
#include <Manager/GameManager.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <Manager/StageManager.h>
#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const auto StageLogo = L"data/texture/UI/StartLogo.png";
	const auto StageNumber = L"data/texture/UI/StartNumber.png";
	const int TextMove = 3; // �e�L�X�g�㉺�ړ��̐U�蕝
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CStartLogo::CStartLogo()
{
	m_TextureMove = std::make_unique<CTextureMoveComponent>();
	m_nTime = 0;
	m_TextMove = 0.0f;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CStartLogo::Init()
{
	m_TextureFades.resize(eStartLogoMax);

	// �X�^�[�g�e�N�X�`��
	m_Polygon->SetSize(SCREEN_WIDTH, 500.0f);
	m_Polygon->SetAlpha(0);	// �ŏ��͔�\��
	m_Polygon->LoadTexture(StageLogo);

	// �i���o�[
	m_Number.Init(StageNumber);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CStartLogo::Uninit()
{
	// �i���o�[�I��
	m_Number.Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CStartLogo::Update()
{
	bool FadeState = m_TextureFades[eStartLogo].GetFadeState();

	if (FadeState)
	{
		// �e�L�X�g�㉺
		m_nTime += TextMove;
		m_TextMove += ((sinf(m_nTime * (float)M_PI / 100)));
		m_TextureMove->TextureUpDown(m_Polygon);
		// �e�L�X�g�t�F�[�h�C���A�E�g
		m_TextureFades[eStartLogo].FadeInOut(m_Polygon);
		m_TextureFades[eStartNumber].FadeInOut(m_Number.GetPolygon());
	}
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CStartLogo::Draw()
{
	m_Polygon->Draw();
	int StageNumber = CGameManager::GetStageMenu();
	XMFLOAT2 pos = { 300, m_TextMove };
	// �i���o�[�`��
	m_Number.Draw(StageNumber + 1,pos);
}
