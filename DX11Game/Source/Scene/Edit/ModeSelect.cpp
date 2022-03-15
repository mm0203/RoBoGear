//=============================================================================
// CModeSelect.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "ModeSelect.h"
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Message/Message.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const XMFLOAT3 CursorColor = XMFLOAT3(0.0f, 0.8f, 0.9f);	// �J�[�\���F
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CModeSelect::CModeSelect()
{
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CModeSelect::Init()
{
	// �|���S�������ݒ�
	m_Polygon.LoadTexture(L"data/texture/Edit/Cursor01.png");
	m_Polygon.SetPosition(400, 300);
	m_Polygon.SetSize(40, 40);
	m_Polygon.SetColor(CursorColor);

	// �e�L�X�g�`��
	CMessageManager::CreateMessage("CREATE",   XMFLOAT2(440.0f, 300.0f));
	CMessageManager::CreateMessage("DELETE",   XMFLOAT2(440.0f, 250.0f));
	CMessageManager::CreateMessage("SET STEP", XMFLOAT2(440.0f, 200.0f));
	CMessageManager::CreateMessage("SAVE",     XMFLOAT2(440.0f, 150.0f));
	CMessageManager::CreateMessage("LOAD",     XMFLOAT2(440.0f, 100.0f));
	CMessageManager::CreateMessage("TITLE",    XMFLOAT2(440.0f, 50.0f));
	CMessageManager::CreateMessage("GAME",     XMFLOAT2(440.0f, 0.0f));
	CMessageManager::CreateMessage("STEP",     XMFLOAT2(485.0f, -75.0f));
	CMessageManager::CreateMessage("STAGE NO", XMFLOAT2(435.0f, -225.0f));
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CModeSelect::Uninit()
{
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CModeSelect::Update(int& index,int ModeNum)
{
	// ��
	if (GetKeyTrigger(VK_UP))
	{
		// �J�[�\��SE
		CSound::Play(SE_CURSORMOVE);

		index--;
		// �ŏ��𒴂�����ő��
		if (index < 0) index += ModeNum;

		// ���̈ʒu��ύX
		XMFLOAT2 pos = m_Polygon.GetPos();
		pos.y = index * -50.0f + 300.0f;
		m_Polygon.SetPosition(pos);
		//CSound::Play(SE_Cursor);
	}
	// ��
	if (GetKeyTrigger(VK_DOWN))
	{
		// �J�[�\��SE
		CSound::Play(SE_CURSORMOVE);

		index++;
		// �ő�𒴂�����ŏ���
		if (index > ModeNum - 1) index -= ModeNum;

		// ���̈ʒu��ύX
		XMFLOAT2 pos = m_Polygon.GetPos();
		pos.y = index * -50.0f + 300.0f;
		m_Polygon.SetPosition(pos);
	}

	PrintDebugProc("[CurrentCursor] = %d\n", index);

	// �I�����Ă��郁�b�Z�[�W�̐F��ύX	
	int num = 0;
	std::vector<CMessage*> List = CMessageManager::GetActiveList();
	for (auto it : List)
	{
		// �������猻�݂̑I�������擾
		if (num == index)
			it->SetColor(CursorColor);
		else 
			it->SetColor({ 1.0f,1.0f,1.0f });
		num++;
		if (num == ModeNum) break;
	}
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CModeSelect::Draw()
{
	m_Polygon.Draw();
}