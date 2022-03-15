//=============================================================================
// StageManager.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "StageManager.h"
#include <Manager/GameManager.h>

// �I�u�W�F�N�g
#include <Object/Player.h>
#include <Object/Wall.h>
#include <Object/Cube.h>
#include <Object/Clear.h>
#include <Object/Gimic.h>
#include <Object/Trap.h>
#include <Object/key.h>
#include <Object/StageGround.h>

// �V�[��
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Edit/Editor.h>

// �t�@�C���ǂݍ���
#include <iostream>
#include <fstream>
#include <sstream>

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================
std::tuple<int, std::string, int> CStageManager::m_StageInfo[] = {};

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	// ������(0,0)�Ȃ̂Ń}�b�v�̍��[�ォ��I�u�W�F�N�g��z�u����
	const float StartPosWidth = 500.0f;
	const float StartPosHeight = 400.0f;
}

//=============================================================================
// 
// ������
// 
//=============================================================================
void CStageManager::Init()
{
	// �X�e�[�W�ԍ�������
	for (int i = 0; i < eStage_10 + 1; i++)
	{
		std::get<eStageNumber>(m_StageInfo[i]) = i;
	}

	//�X�e�[�W�t�@�C�����i�[
	std::get<eStageName>(m_StageInfo[eStage_1]) = "data/map/stage1.csv";
	std::get<eStageName>(m_StageInfo[eStage_2]) = "data/map/stage2.csv";
	std::get<eStageName>(m_StageInfo[eStage_3]) = "data/map/stage3.csv";
	std::get<eStageName>(m_StageInfo[eStage_4]) = "data/map/stage4.csv";
	std::get<eStageName>(m_StageInfo[eStage_5]) = "data/map/stage5.csv";
	std::get<eStageName>(m_StageInfo[eStage_6]) = "data/map/stage6.csv";
	std::get<eStageName>(m_StageInfo[eStage_7]) = "data/map/stage7.csv";
	std::get<eStageName>(m_StageInfo[eStage_8]) = "data/map/stage8.csv";
	std::get<eStageName>(m_StageInfo[eStage_9]) = "data/map/stage9.csv";
	std::get<eStageName>(m_StageInfo[eStage_10]) = "data/map/stage10.csv";

	// �e�X�e�[�W�̕����i�[
	std::get<eStageStep>(m_StageInfo[eStage_1])  = 22;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_2])  = 25;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_3])  = 24;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_4])  = 20;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_5])  = 20;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_6])  = 30;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_7])  = 23;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_8])  = 12;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_9])  = 17;	// �Z
	std::get<eStageStep>(m_StageInfo[eStage_10]) = 24;	// �Z
}

//=============================================================================
// 
// �X�e�[�W�ǂݍ���
// 
//=============================================================================
std::string CStageManager::LoadStage()
{
	// �X�e�[�W�ԍ��擾
	int StageNumber = CGameManager::GetStageMenu();

	for (int i = 0; i < eStage_10 + 1; i++)
	{
		// ��v����X�e�[�W�ԍ�����������
		if (StageNumber == std::get<eStageNumber>(m_StageInfo[i]))
		{
			// �������Z�b�g
			int& step = CGameManager::GetStep();
			step = std::get<eStageStep>(m_StageInfo[i]);

			// �X�e�[�W�t�@�C�������擾
			return std::get<eStageName>(m_StageInfo[i]);
		}
	}
	return "\0";
}

//=============================================================================
// 
// �X�e�[�W����
// 
//=============================================================================
void  CStageManager::StageCreate(std::string& fileName)
{
	// �}�b�v�i�[�p�ϐ�
	std::vector<std::vector<int>> nMap;

	// CSV�ǂݍ���
	ReadCSV(fileName, nMap);

	// �}�b�v�`�b�v�ԍ�
	int nChipId = 0;
	// �s��ԍ�
	XMINT2 hw = XMINT2(0, 0);

	// �X�e�[�W�̃T�C�Y��������
	for (auto& height : nMap)
	{
		// �s�ԍ��̏�����
		hw.x = 0;

		for (auto& CurrentMapChip : height)
		{
			// �}�b�v�`�b�v�ԍ��擾
			nChipId = CurrentMapChip;

			// ���݂̍��W��ۑ�
			XMINT2 Coord = { hw.x, hw.y};
			hw.x++;

			// �����Ȃ�������
			if (nChipId == eObject_None)	continue;

			// �ʒu
			XMFLOAT3 ObjectPos = { MapChipSize * Coord.x - StartPosWidth, 0.0f,  StartPosHeight - MapChipSize * Coord.y };

			// �I�u�W�F�N�g����
			switch (nChipId)
			{
				// ��	
			case(eObject_Wall): // 1
				CObjectManager::CreateObject<CWall>(ObjectPos, Coord);
				break;
				// �L���[�u
			case(eObject_Cube): // 2
				CObjectManager::CreateObject<CCube>(ObjectPos, Coord);
				break;
				// ��
			case(eObject_Key):	 // 3
				//TODO �L�[�̃T�C�Y������Ȃ��̂ő傫���I
				XMFLOAT3 keysize = XMFLOAT3(2.0f, 2.0f, 2.0f);
				CObjectManager::CreateObject<CKey>(ObjectPos, Coord, keysize);
				break;
				// �M�~�b�N
			case(eObject_Gimic): // 4
				CObjectManager::CreateObject<CGimic>(ObjectPos, Coord);
				break;
				// �v���C���[
			case(eObject_Player): // 5
				CObjectManager::CreateObject<CPlayer>(ObjectPos, Coord);
				break;
				// �g���b�v
			case(eObject_Trap): // 6
				CObjectManager::CreateObject<CTrap>(ObjectPos, Coord);
				break;
				// �S�[��
			case(eObject_Clear): // 7
				CObjectManager::CreateObject<CClear>(ObjectPos, Coord);
				break;
			}
		}
		// ��ԍ��̒ǉ�
		hw.y++;
	}
}

//=============================================================================
// 
// CSV�ǂݍ���
// 
//=============================================================================
void  CStageManager::ReadCSV(std::string& fileName,std::vector<std::vector<int>>& map)
{
	// �t�@�C���ǂݍ���
	std::ifstream csv(fileName);

	// csv����1�񕪂�ǂݍ���
	for (std::string str; std::getline(csv, str);)
	{
		// ���ǉ�
		map.emplace_back(std::vector<int>());

		// �ǂݍ��񂾗���P�������i�[�ł���悤��
		for (std::stringstream ss(str); std::getline(ss, str, ',');)
		{
			// ������int�^�ɕϊ�
			map[map.size() - 1].emplace_back(std::stoi(str.c_str()));
		}
	}
}