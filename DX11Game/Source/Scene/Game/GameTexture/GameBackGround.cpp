//=============================================================================
// GameBackGround.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "GameBackGround.h"
#include <Manager/GameManager.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	// TODO cpp�킯��ׂ��H
	const auto GameOperation = L"data/texture/UI/OperationUI.png";
	const auto BackGroundFrame = L"data/texture/UI/Frame.png";
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CGameBackGround::CGameBackGround()
{
	m_fAngle = 0.0f;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CGameBackGround::Init()
{
	// �T�C�Y�m��
	m_Polygons.resize(GameNotmoveTextureMax);
	m_TextureFades.resize(GameNotmoveTextureMax);

	// �e�t�F�[�h���l��1��
	for(int i = 0;i < GameNotmoveTextureMax; i++)
	m_TextureFades[i].SetAlpha(1.0f);

	for (int i = 0; i < GameNotmoveTextureMax; i++)
		m_Polygons[i].SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_Polygons[eOperation].LoadTexture(GameOperation);
	m_Polygons[eBackGroundFrame].LoadTexture(BackGroundFrame);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CGameBackGround::Uninit()
{
	m_Polygons.clear();
	m_TextureFades.clear();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CGameBackGround::Update()
{
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CGameBackGround::Draw()
{
	// UI�`��
	for (int i = 0; i < GameNotmoveTextureMax; i++)
		m_Polygons[i].Draw();
}

//=============================================================================
// 
// �t�F�[�h�A�E�g
// 
//=============================================================================
void CGameBackGround::FadeOut()
{
	for (int i = 0; i < GameNotmoveTextureMax; i++)
		m_TextureFades[i].FadeOut(m_Polygons[i]);
}