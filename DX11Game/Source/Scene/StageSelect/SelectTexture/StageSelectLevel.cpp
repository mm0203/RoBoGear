//=============================================================================
// StageSelectLevel.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "StageSelectLevel.h"
#include <Scene/StageSelect/StageSelectScene.h>
#include <Manager/StageManager.h>
#include <Manager/GameManager.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const auto Stage1 = L"data/texture/StageSelect/select1.png";
	const auto Stage2 = L"data/texture/StageSelect/select2.png";
	const auto Stage3 = L"data/texture/StageSelect/select3.png";
	const auto Stage4 = L"data/texture/StageSelect/select4.png";
	const auto Stage5 = L"data/texture/StageSelect/select5.png";
	const auto Stage6 = L"data/texture/StageSelect/select6.png";
	const auto Stage7 = L"data/texture/StageSelect/select7.png";
	const auto Stage8 = L"data/texture/StageSelect/select8.png";
	const auto Stage9 = L"data/texture/StageSelect/select9.png";
	const auto Stage10 = L"data/texture/StageSelect/select10.png";
	const auto TitleBack = L"data/texture/StageSelect/selectTitle.png";
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CStageSelectLevel::Init()
{
	m_Polygons.resize(Max_Stage);
	// �e�摜�̃|�W�V�����ƃT�C�Y��ݒ�
	for (int i = 0; i <= eStage_10; i++)
	{
		// ��i
		if(i <= eStage_5)
		m_Polygons[i].SetPosition(float(i * 200.0f) - 400.0f, 100.0f);
		// ���i
		if (i >= eStage_6)
		m_Polygons[i].SetPosition(float((i - 5) * 200.0f) - 400.0f, -100.0f);

		m_Polygons[i].SetSize(150.0f, 150.0f);

		// �J�[�\���p�|�W�V����
		m_LevelPos[i] = m_Polygons[i].GetPos();
		m_LevelSize[i] = m_Polygons[i].GetSize();
	}
	// �e���x���̃e�N�X�`��
	m_Polygons[eStage_1].LoadTexture(Stage1);
	m_Polygons[eStage_2].LoadTexture(Stage2);
	m_Polygons[eStage_3].LoadTexture(Stage3);
	m_Polygons[eStage_4].LoadTexture(Stage4);
	m_Polygons[eStage_5].LoadTexture(Stage5);
	m_Polygons[eStage_6].LoadTexture(Stage6);
	m_Polygons[eStage_7].LoadTexture(Stage7);
	m_Polygons[eStage_8].LoadTexture(Stage8);
	m_Polygons[eStage_9].LoadTexture(Stage9);
	m_Polygons[eStage_10].LoadTexture(Stage10);

	// �^�C�g��
	m_Polygons[eTitleBack].SetPosition(0,-280.0f);
	m_Polygons[eTitleBack].SetSize(800.0f, 150.0f);

	// �J�[�\���p�|�W�V����
	m_LevelPos[eTitleBack] = m_Polygons[eTitleBack].GetPos();
	m_LevelSize[eTitleBack] = m_Polygons[eTitleBack].GetSize();
	m_Polygons[eTitleBack].LoadTexture(TitleBack);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CStageSelectLevel::Uninit()
{
	m_Polygons.clear();
	m_LevelPos.clear();
	m_LevelSize.clear();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CStageSelectLevel::Update()
{
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CStageSelectLevel::Draw()
{
	// �X�e�[�W�`��
	for (int i = 0; i < Max_Stage; i++)
		m_Polygons[i].Draw();
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
XMFLOAT2 CStageSelectLevel::GetLevelPos()
{
	// ���x���ԍ�����|�W�V�������擾
	for (auto& it : m_LevelPos)
	{
		if (it.first == CGameManager::GetStageMenu())
			return it.second;
	}
	return XMFLOAT2();
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
XMFLOAT2 CStageSelectLevel::GetLevelSize()
{
	// ���x���ԍ�����|�W�V�������擾
	for (auto& it : m_LevelSize)
	{
		if (it.first == CGameManager::GetStageMenu())
			return it.second;
	}
	return XMFLOAT2();
}