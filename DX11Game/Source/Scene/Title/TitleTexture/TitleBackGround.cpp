//=============================================================================
// TitleBackGround.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TitleBackGround.h"
#include <Scene/Title/TitleScene.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const int BgNum = 2; // �w�i�摜�̐�
	const auto TitleBackGround = L"data/texture/Title/TitleBackGround.png";
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CTitleBackGround::Init()
{

	m_Polygons.resize(eTitleBackGroundMax);

	// �w�i
	for (int i = 0; i < BgNum; i++)
	{
		m_Polygons[i].SetPosition(0.0f, 0.0f);
		m_Polygons[i].SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_Polygons[i].LoadTexture(TitleBackGround);
	}
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CTitleBackGround::Uninit()
{
	m_Polygons.clear();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CTitleBackGround::Update()
{
	// �w�i�摜���X�N���[��
	static float fPosX = 0.0f;
	fPosX -= 1.0f;
	for (int i = 0; i < BgNum; i++)
	{
		m_Polygons[i].SetPosition(fPosX + (i * SCREEN_WIDTH), 0.0f);
		// ���[�܂ōs������E�[����ĕ`��
		if (fPosX <= -SCREEN_WIDTH)
		{
			m_Polygons[i].SetPosition(float(i * SCREEN_WIDTH), 0.0f);
			fPosX = 0;
		}
	}
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CTitleBackGround::Draw()
{
	// �e�N�X�`���`��
	for (int i = 0; i < eTitleBackGroundMax; i++)
		m_Polygons[i].Draw();
}