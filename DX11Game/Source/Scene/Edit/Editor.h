//=============================================================================
// CEditor.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/ObjectManager.h>
#include <Manager/StageManager.h>
#include <Renderer/Polygon/CPolygon.h>
#include <Component/Transform.h>
#include <Component/DrawNumber.h>
#include "Cursor.h"
#include "ModeSelect.h"
#include "EditOperationUI.h"

#include <memory>
#include <string>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	constexpr int HeightMax = 8;
	constexpr int WidthMax = 11;

}

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CEditor
{
public:
	CEditor();
	~CEditor() = default;

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �}�b�v������
	void MapInitialize();
	// �X�e�[�W�Z���N�g
	void MenuIndexChange(int& index, int min, int max);
	// �I�u�W�F�N�g����
	void Create();
	// �폜
	void Delete();
	// �I�u�W�F�N�g�ύX
	void ChangeObject();
	// �I�u�W�F�N�g�ړ�
	void Move();
	// �X�e�b�v�ݒ�
	void SetStep();
	// �X�e�[�W�ۑ�
	void SaveStage();
	// �X�e�[�W�ǂݍ���
	void LoadStage();
	// �^�C�g��
	void LoadTitle();
	// �Q�[���X�^�[�g
	void LoadGame();
	// �X�e�[�W�ԍ��X�V
	void StageNumberUpdate();
private:

	enum EditMode
	{
		eMode_Create,
		eMode_Delete,
		eMode_Step,
		eMode_Save,
		eMode_Load,
		eMode_Title,
		eMode_Game,
		eMode_Max
	};
private:

	// �\���p���f��
	std::unique_ptr<CRenderer> m_pModel;
	// ���f�����
	CTransform m_Trans;
	// ���[�h�I��
	CModeSelect m_ModeSelect;
	// �X�e�b�v��i���o�[�\��
	CNumber m_Number;
	// �J�[�\�����f��
	CCursor m_ModelCursor;
	// UI�\��
	CEditOperationUI m_pEditOperationUI;

	// �X�e�[�W�ԍ�
	int m_nCurrentStage;
	// ����
	int m_nStepCount;
	// ���݂̃��[�h
	int m_nCurrentMode;
	// �_�ŗp����
	bool m_bDisp;
	//�I�u�W�F�N�g�̎��
	int m_type;
	// �X�e�[�W�ҏW�p�ϐ�
	int m_nMap[HeightMax][WidthMax];
	// �}�b�v�`�b�v�T�C�Y
	int m_nChipsize;
};