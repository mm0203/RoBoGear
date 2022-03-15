//=============================================================================
// StageManager.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <main.h>
#include <string>
#include <vector>
#include <tuple>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================

// 1�}�X�̃T�C�Y
const auto MapChipSize = 100;

// �e�I�u�W�F�N�g
enum MapObject
{
	eObject_None = 0,
	eObject_Wall,
	eObject_Cube,
	eObject_Key,
	eObject_Gimic,
	eObject_Player,
	eObject_Trap,
	eObject_Clear,
	eObject_Max
};

// �X�e�[�W�ԍ�
enum  SelectStage
{
	eStage_1 = 0,
	eStage_2,
	eStage_3,
	eStage_4,
	eStage_5,
	eStage_6,
	eStage_7,
	eStage_8,
	eStage_9,
	eStage_10,
	eTitleBack,
	Max_Stage
};

// �X�e�[�W�^�v���̏��
enum StageInfo
{
	eStageNumber,	// �X�e�[�W�ԍ�
	eStageName,		// �X�e�[�W�t�@�C����
	eStageStep,		// �e�X�e�[�W�̕���
	eStageInfo
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CStageManager
{

public:
	CStageManager() = default;
	~CStageManager() = default;

	static std::tuple<int, std::string, int>& GetStageInfo(int index) { return m_StageInfo[index]; }

	static void Init();
	// �X�e�[�W���ǂݍ���
	static std::string LoadStage();
	// �X�e�[�W����
	static void StageCreate(std::string& fileName);
	// CSV�t�@�C���ǂݍ���
	static void ReadCSV(std::string& fileName, std::vector<std::vector<int>>& map);

private:
	// �X�e�[�W�̊e���
	// 1.�X�e�[�W�ԍ�
	// 2.�X�e�[�W�t�@�C����
	// 3.�X�e�[�W�̕���
	static std::tuple<int, std::string, int> m_StageInfo[eStage_10 + 1];
};