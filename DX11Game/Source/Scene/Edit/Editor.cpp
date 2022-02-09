//=============================================================================
// CEditor.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "Editor.h"

// �I�u�W�F�N�g
#include <Object/Player.h>
#include <Object/Caterpillar.h>
#include <Object/Gear.h>
#include <Object/Generare.h>
#include <Object/Wall.h>
#include <Object/Cube.h>
#include <Object/Clear.h>
#include <Object/Gimic.h>
#include <Object/Trap.h>
#include <Object/key.h>
#include <Object/StageGround.h>

// �}�l�[�W���[
#include <Manager/StageManager.h>

// �V�[��
#include <Scene/Game/GameScene.h>
#include <Scene/Title/TitleScene.h>
#include <Scene/StageSelect/StageSelectScene.h>

// �V�X�e��
#include <System/Input/input.h>
#include <System/Message/Message.h>
#include <System/Debug/debugproc.h>
#include <System/Singleton/singleton.h>
#include <System/Sound/Sound.h>

// �t�@�C���ǂݍ���
#include <iostream>
#include <fstream>
#include <sstream>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	// �}�b�v�����l
	constexpr XMINT2 CenterCoord = XMINT2(5, 4);
	// �I���ł��郂�[�h��
	constexpr int ModeNum = 7;
	// �X�e�[�W�̐�
	int nStagemin = 1;
	int nStagemax = 10;
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CEditor::CEditor()
{
	m_pModel = std::make_unique<CRenderer>();
	m_nStepCount = 30;
	m_nCurrentStage = 0;
	m_nCurrentMode = eMode_Create;
	m_bDisp = false;
	m_type = eObject_Wall;
}

//=============================================================================
// 
// �}�b�v������
// 
//=============================================================================
void CEditor::MapInitialize()
{
	for (int y = 0; y < HeightMax; y++)
	{
		for (int x = 0; x < WidthMax; x++)
		{
			m_nMap[y][x] = eObject_None;
		}
	}
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CEditor::Init()
{
	// �}�b�v������
	MapInitialize();
	// �}�b�v�`�b�v�T�C�Y
	m_nChipsize = MapChipSize;
	// ���b�Z�[�W������
	MessageManager::Init();
	// ���[�h�Z���N�g������
	m_nCurrentMode = eMode_Create;
	m_ModeSelect.Init();
	// �i���o�[������
	m_Number.Init();
	// ���f���J�[�\��������
	m_ModelCursor.Init();
	// �������
	m_pEditOperationUI.Init();
	// �I�u�W�F�N�g��񏉊���
	m_Trans.SetCoord(CenterCoord);	// �����l�𒆉���(���オ0,0)
	m_Trans.SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CEditor::Uninit()
{
	m_pModel->ReleaseModelAll();
	MessageManager::Uninit();
	m_Number.Uninit();
	m_ModelCursor.Uninit();
	m_ModeSelect.Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CEditor::Update()
{
	// ���[�h�ύX
	switch (m_nCurrentMode)
	{
		// ����
	case EditMode::eMode_Create:
		Move();
		ChangeObject();
		Create();
		break;
		// �폜
	case EditMode::eMode_Delete:
		Move();
		Delete();
		break;
		// �����ݒ�
	case EditMode::eMode_Step:
		SetStep();
		break;
		// �X�e�[�W�Z�[�u
	case EditMode::eMode_Save:
		SaveStage();
		break;
		// �X�e�[�W�ǂݍ���
	case EditMode::eMode_Load:
		LoadStage();
		break;
		// �^�C�g��
	case EditMode::eMode_Title:
		LoadTitle();
		break;
		// �Q�[���J�n
	case EditMode::eMode_Game:
		LoadGame();
		break;
	default:
		break;
	}

	// ���[�h�ύX
	m_ModeSelect.Update(m_nCurrentMode, ModeNum);
	// �i���o�[�X�V
	m_Number.Update();
	// ���f���J�[�\���X�V
	m_ModelCursor.Update(m_Trans.GetPos(), m_Trans.GetScale(), m_Trans.GetRot());

	// �I�u�W�F�N�g�_��
	static int nCount = 0;
	nCount++;
	if (nCount < 15) m_bDisp = true;
	if (nCount > 15) m_bDisp = false;
	if (nCount > 30) nCount = 0;

	PrintDebugProc("\PosX%d:PosY%d:PosZ%d:\n", (int)m_Trans.GetPos().x, (int)m_Trans.GetPos().y, (int)m_Trans.GetPos().z);
	PrintDebugProc("\ObjectType:%d\n", m_type);
	PrintDebugProc("\StageNo:%d\n", m_nCurrentStage);
	PrintDebugProc("\Step:%d\n", m_nStepCount);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CEditor::Draw()
{
	// �I�u�W�F�N�g�`��
	if (m_bDisp && m_nCurrentMode == eMode_Create)
		m_pModel->Draw(m_Trans.GetPos(), m_Trans.GetScale(), m_Trans.GetRot());

	// �J�[�\�����f���`��
	if (m_nCurrentMode == eMode_Create || (m_nCurrentMode == eMode_Delete))
		m_ModelCursor.Draw();

	// ���[�h�Z���N�g�J�[�\���`��
	m_ModeSelect.Draw();

	// �����`��
	XMFLOAT2 pos = XMFLOAT2(565.0f, -150.0f);
	m_Number.Draw(m_nStepCount, pos);
	// �X�e�[�WNo�`��
	XMFLOAT2 Stagepos = XMFLOAT2(565.0f, -300.0f);
	m_Number.Draw(m_nCurrentStage + 1, Stagepos);
	// ��������`��
	m_pEditOperationUI.Draw();
	// ���b�Z�[�W�`��
	MessageManager::Draw();
}

//=============================================================================
// 
// �I�����ύX
// 
//=============================================================================
void CEditor::MenuIndexChange(int& index, int min, int max)
{

	if (GetKeyTrigger(VK_Q) || GetKeyTrigger(VK_LEFT))
	{
		// �ړ��Ƃ������̉�
		CSound::Play(SE_EDIT_CREATE_CURSOR);
		index--;
	}
	if (GetKeyTrigger(VK_E) || GetKeyTrigger(VK_RIGHT))
	{
		// �ړ��Ƃ������̉�
		CSound::Play(SE_EDIT_CREATE_CURSOR);
		index++;
	}

	// �ŏ��l�����������ő�l��
	if (index < min)
		index += max;
	// �ő�l����������ŏ��l��
	if (index >= max)
		index -= max;
}

//=============================================================================
// 
// �I�u�W�F�N�g����
// 
//=============================================================================
void CEditor::Create()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		// �I�u�W�F�N�g�����ɂ������琶���ł��Ȃ�
		if (m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] != eObject_None)
		{
			// �I�u�W�F�N�g���Ȃ�
			CSound::Play(SE_CUBE_MOVE_NONE);
			return;
		}

		// �I�u�W�F�N�g����
		CSound::Play(SE_EDIT_CREATE);

		switch (m_type)
		{
		case eObject_Wall:
			ObjectManager::CreateObject<CWall>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Cube:
			ObjectManager::CreateObject<CCube>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Key:
			ObjectManager::CreateObject<CKey>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Gimic:
			ObjectManager::CreateObject<CGimic>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Player:
			ObjectManager::CreateObject<CPlayer>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Trap:
			ObjectManager::CreateObject<CTrap>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Clear:
			ObjectManager::CreateObject<CClear>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		default:
			break;
		}
		// �I�u�W�F�N�g�̈ʒu��ۑ�
		m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] = m_type;
	}

}
//=============================================================================
// 
// �I�u�W�F�N�g�폜
// 
//=============================================================================
void CEditor::Delete()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		// �I�u�W�F�N�g���Ȃ���Ή������Ȃ�
		if (m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] == eObject_None)
		{
			// �I�u�W�F�N�g�����Ȃ�
			CSound::Play(SE_CUBE_MOVE_NONE);
			return;
		}

		// �I�u�W�F�N�g�폜
		CSound::Play(SE_EDIT_DELTE);

		// �ʒu����I�u�W�F�N�g�����擾
		int ObjectType = m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x];

		std::string Tag;
		switch (ObjectType)
		{
		case eObject_Wall:
			Tag = "Wall";
			break;
		case eObject_Cube:
			Tag = "Cube";
			break;
		case eObject_Key:
			Tag = "Key";
			break;
		case eObject_Gimic:
			Tag = "Gimic";
			break;
		case eObject_Player:
			Tag = "Player";
			break;
		case eObject_Trap:
			Tag = "Trap";
			break;
		case eObject_Clear:
			Tag = "Clear";
			break;
		default:
			break;
		}
		// �I�u�W�F�N�g�폜
		ObjectManager::DestroyEditObject(Tag, m_Trans.GetCoord());

		//for (auto it = m_pObj.begin(); it != m_pObj.end();)
		//{
		//	if (ObjectManager::DestroyEditObject(it->get()->GetTag(), m_Trans.GetCoord()))
		//	{
		//		it->reset();
		//		it = m_pObj.erase(it);

		//		// �폜�����ꏊ���X�V
		//		m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] = eObject_None;
		//		return;
		//	}
		//	else ++it;
		//}

		// �폜�����ꏊ���X�V
		m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] = eObject_None;
	}
}

//=============================================================================
// 
// �I�u�W�F�N�g����
// 
//=============================================================================
void CEditor::ChangeObject()
{
	// �I�u�W�F�N�g�ύX
	if (GetKeyTrigger(VK_Q) || GetKeyTrigger(VK_LEFT))
	{
		// �ړ��Ƃ������̉�
		CSound::Play(SE_EDIT_CREATE_CURSOR);

		m_type--;
	}
	if (GetKeyTrigger(VK_E) || GetKeyTrigger(VK_RIGHT))
	{
		// �ړ��Ƃ������̉�
		CSound::Play(SE_EDIT_CREATE_CURSOR);

		m_type++;
	}
	if (m_type < eObject_None + 1)
		m_type += eObject_Max -1;

	if (m_type > eObject_Max - 1)
		m_type -= eObject_Max - 1;

	// �I�u�W�F�N�g�̌����ڕύX
	switch (m_type)
	{
	case eObject_Wall:

		m_pModel->LoadModel(MODEL_WALL);
		break;
	case eObject_Cube:
		m_pModel->LoadModel(MODEL_CUBE);
		break;
	case eObject_Key:
		XMFLOAT3 sizeKey = { 2.0f, 2.0f, 2.0f };
		m_Trans.SetScale(sizeKey);
		m_pModel->LoadModel(MODEL_KEY);
		break;
	case eObject_Gimic:
		m_pModel->LoadModel(MODEL_GIMIC);
		break;
	case eObject_Player:
		m_pModel->LoadModel(MODEL_PLAYER);
		break;
	case eObject_Trap:
		m_pModel->LoadModel(MODEL_TRAP);
		break;
	case eObject_Clear:
		m_pModel->LoadModel(MODEL_CLEAR);
		break;
	default:
		break;
	}

	if (m_type != eObject_Key)
	{
		XMFLOAT3 size = { 1.0f, 1.0f, 1.0f };
		m_Trans.SetScale(size);
	}
}

//=============================================================================
// 
// �I�u�W�F�N�g����
// 
//=============================================================================
void CEditor::Move()
{
	//�J�[�\���ʒu�ړ�
	static XMFLOAT3 pos = XMFLOAT3();
	static XMINT2 coord = CenterCoord;

	XMFLOAT3 oldpos = pos;
	XMINT2 oldcoord = coord;

	if (GetKeyTrigger(VK_W))// ��
	{
		CSound::Play(SE_EDIT_ARROW);
		pos.z += m_nChipsize;
		coord.y -= m_nChipsize / MapChipSize;
	}
	if (GetKeyTrigger(VK_S))// ��
	{
		CSound::Play(SE_EDIT_ARROW);
		pos.z -= m_nChipsize;
		coord.y += m_nChipsize / MapChipSize;
	}
	if (GetKeyTrigger(VK_A))// ��
	{
		CSound::Play(SE_EDIT_ARROW);
		pos.x -= m_nChipsize;
		coord.x -= m_nChipsize / MapChipSize;
	}
	if (GetKeyTrigger(VK_D))// �E
	{
		CSound::Play(SE_EDIT_ARROW);
		pos.x += m_nChipsize;
		coord.x += m_nChipsize / MapChipSize;
	}
	
	// �}�b�v�͈̓`�F�b�N
	if (coord.x < 0 || coord.x >= WidthMax || coord.y < 0 || coord.y >= HeightMax)
	{
		pos = oldpos;
		coord = oldcoord;
	}
	
	// �ړ������J�[�\�����Z�b�g
	m_Trans.SetPos(pos);
	m_Trans.SetCoord(coord);
}

//=============================================================================
// 
// �����ݒ�
// 
//=============================================================================
void CEditor::SetStep()
{
	int nStepmin = 2;
	int nStepmax = 99;

	MenuIndexChange(m_nStepCount, nStepmin, nStepmax);
}

//=============================================================================
// 
// �Z�[�u
// 
//=============================================================================
void CEditor::SaveStage()
{
	// �I�����ύX
	MenuIndexChange(m_nCurrentStage, nStagemin, nStagemax);

	if (GetKeyTrigger(VK_RETURN))
	{
		CSound::Play(SE_EIDT_SAVE);

		// �X�e�[�W�ԍ��X�V
		StageNumberUpdate();

		// �X�e�[�W�ǂݍ���
		std::string StageFile = StageManager::LoadStage();

		//�t�@�C���̏o��
		std::ofstream ofs(StageFile);

		for (int i = 0; i < HeightMax; i++)
		{
			for (int j = 0; j < WidthMax; j++)
			{
				ofs << (int)m_nMap[i][j] << ",";
			}
			// ���s
			ofs << std::endl;
		}
		ofs.close();

		// �����X�V
		auto& Info = StageManager::GetStageInfo(m_nCurrentStage);
		std::get<eStageStep>(Info) = m_nStepCount;
	}
}

//=============================================================================
// 
// ���[�h
// 
//=============================================================================
void CEditor::LoadStage()
{
	// �I�����ύX
	MenuIndexChange(m_nCurrentStage, nStagemin, nStagemax);

	if (GetKeyTrigger(VK_RETURN))
	{
		CSound::Play(SE_EIDT_LOAD);

		// �}�b�v������
		MapInitialize();

		//���ݐ�������Ă���I�u�W�F�N�g������
		ObjectManager::UninitAll();

		// �X�e�[�W�ԍ��X�V
		StageNumberUpdate();

		std::string StageFile = StageManager::LoadStage();

		// �X�e�[�W�i�[�p�ϐ�
		std::vector<std::vector<int>> nMap;

		// CSV�ǂݍ���
		StageManager::ReadCSV(StageFile, nMap);

		// �X�e�[�W����
		StageManager::StageCreate(StageFile);

		// �G�f�B�b�g�p�ϐ��Ɋi�[
		for (int y = 0; y < HeightMax; y++)
		{
			for (int x = 0; x < WidthMax; x++)
			{
				m_nMap[y][x] = nMap[y][x];
			}
		}
		// ���������l�ǂݍ���
		auto& Info = StageManager::GetStageInfo(m_nCurrentStage);
		m_nStepCount = std::get<eStageStep>(Info);

		m_type = eObject_Wall;
	}
}
//=============================================================================
// 
// �^�C�g���ǂݍ���
// 
//=============================================================================
void CEditor::LoadTitle()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		CSound::Play(SE_CHOISE);
		Singleton<SceneManager>::GetInstance().SetNextScene(new TitleScene());
	}
}


//=============================================================================
// 
// �Q�[���ǂݍ���
// 
//=============================================================================
void CEditor::LoadGame()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		CSound::Play(SE_CHOISE);

		// �X�e�[�W�ԍ��X�V
		StageNumberUpdate();

		Singleton<SceneManager>::GetInstance().SetNextScene(new GameScene());
	}
}

//=============================================================================
// 
// �X�e�[�W�ԍ��X�V
// 
//=============================================================================
void CEditor::StageNumberUpdate()
{
	int& nMenuIndex = CGameManager::GetStageMenu();
	nMenuIndex = m_nCurrentStage;
}
