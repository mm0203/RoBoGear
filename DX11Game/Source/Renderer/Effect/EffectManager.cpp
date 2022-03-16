//=============================================================================
// CEffectManager.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "Effect.h"
#include <Manager/Object.h>
#include <System/Debug/debugproc.h>

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================
std::vector<CEffect*> CEffectManager::m_ActiveList;
std::vector<CEffect*> CEffectManager::m_UnusedList;
std::vector<CEffect*> CEffectManager::m_DeleteList;

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CEffectManager::Init()
{
	// �I�u�W�F�N�g�쐬
	CEffectManager::CreateObject(99);

}
//=============================================================================
// 
// �I������
// 
//=============================================================================
void CEffectManager::Uninit()
{
	// �e���X�g�̃I�u�W�F�N�g�폜
	int num = (int)m_ActiveList.size();

	for (int i = 0; i < num; i++)
	{
		CEffect* p;						//�폜�p�|�C���^
		p = *(m_ActiveList.begin());	//�v�f�̃|�C���^
		p->Uninit();					//�I���������Ă�
		m_ActiveList.erase(m_ActiveList.begin());	//���X�g����폜
		delete p;						//�C���X�^���X�폜
	}

	// ���g�p���X�g�̃I�u�W�F�N�g�폜
	num = (int)m_UnusedList.size();

	for (int i = 0; i < num; i++)
	{
		CEffect* p;						//�폜�p�|�C���^
		p = *(m_UnusedList.begin());	//�v�f�̃|�C���^
		p->Uninit();					//�I���������Ă�
		m_UnusedList.erase(m_UnusedList.begin());	//���X�g����폜
		delete p;						//�C���X�^���X�폜
	}
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CEffectManager::Update(GameState state)
{
	// �I�u�W�F�N�g�X�V
	for (auto it : m_ActiveList)
		it->Update();

	// ���X�g�X�V
	CEffectManager::UpdateObject();
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CEffectManager::Draw(GameState state)
{
	// �I�u�W�F�N�g�`��
	for (auto it : m_ActiveList)
		it->Draw();
}

//=============================================================================
// 
// �G�t�F�N�g����
// 
//=============================================================================
void CEffectManager::CreateEffect(EffectID ID, XMFLOAT3 pos)
{
	CEffect obj;

	// ���W��������Əグ�Č����₷���悤��
	pos.y += 50.0f;

	// �eID�ŃG�t�F�N�g��o�^
	switch (ID)
	{
	case Effect_GimicBreak:
		obj.Init();
		obj.m_FrameNum = { 5,3 };
		obj.m_MaxAnimNum = 15;
		obj.m_Speed = 5;
		obj.SetPosition(pos);
		obj.SetSize(75.0f, 75.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/GimicBreak.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case Effect_KeyBreak:
		obj.Init();
		obj.m_FrameNum = { 6,1 };
		obj.m_MaxAnimNum = 6;
		obj.m_Speed = 3;
		obj.SetPosition(pos);
		obj.SetSize(100.0f, 100.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/KeyBreak.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case Effect_PlayerMove:
		obj.Init();
		obj.m_FrameNum = { 4,1 };
		obj.m_MaxAnimNum = 4;
		obj.m_Speed = 3;
		obj.SetPosition(pos);
		obj.SetSize(50.0f, 50.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/PlayerMove.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case Effect_CubeMove:
		obj.Init();
		obj.m_FrameNum = { 8,1 };
		obj.m_MaxAnimNum = 8;
		obj.m_Speed = 2;
		obj.SetPosition(pos);
		obj.SetSize(100.0f, 100.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/CubeMove.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case Effect_Trap:
		obj.Init();
		obj.m_FrameNum = { 8,1 };
		obj.m_MaxAnimNum = 8;
		obj.m_Speed = 3;
		obj.SetPosition(pos);
		obj.SetSize(100.0f, 100.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/Trap.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;


	default:
		break;
	}

	// ������
	obj.m_CurrentAnimNum = 0;
	obj.m_SpeedCount = 0;

	CEffectManager::AddObject(obj);
}

//=============================================================================
// 
// �G�t�F�N�g�폜
// 
//=============================================================================
void CEffectManager::DeleteObject(CEffect* pObj)
{
	// DeleteList�ɓo�^
	m_DeleteList.push_back(pObj);
}

//=============================================================================
// 
// �G�t�F�N�g�̃I�u�W�F�N�g�ǉ�
// 
//=============================================================================
void CEffectManager::AddObject(CEffect obj)
{
	// �o�^�p�I�u�W�F�N�g
	CEffect* pObj;
	// ���g�p�I�u�W�F�N�g��������΃G���[
	if (m_UnusedList.empty())
	{
		MessageBoxA(GetMainWnd(), "�G�t�F�N�g�I�u�W�F�N�g������Ȃ�", "ObjectNothing", MB_OK);
		return;
	}

	// ���g�p���X�g����I�u�W�F�N�g�����o��
	pObj = *m_UnusedList.begin();

	// ���g�p���X�g�X�V
	m_UnusedList.erase(m_UnusedList.begin());

	// �I�u�W�F�N�g�̒��g���R�s�[
	*pObj = obj;
	//*pObj->m_BillMesh.m_pTexture = *obj.m_BillMesh.m_pTexture;

	// ���������G�t�F�N�g��n��
	ID3D11ShaderResourceView* pTexture = &pObj->m_BillMesh.GetTexture();
	ID3D11ShaderResourceView* pAddTexture = &obj.m_BillMesh.GetTexture();
	pTexture = pAddTexture;

	// �A�N�e�B�u���X�g�ɓo�^
	m_ActiveList.push_back(pObj);
}

//=============================================================================
// 
// �G�t�F�N�g�̃I�u�W�F�N�g�X�V
// 
//=============================================================================
void CEffectManager::UpdateObject()
{
	// ��̏ꍇ�X�L�b�v
	if (m_DeleteList.empty()) return;

	for (auto it : m_DeleteList)
	{
		int num = 0;
		// �A�N�e�B�u���X�g���猟��
		for (auto ite : m_ActiveList)
		{
			if (it == ite)
			{
				// �|�C���^���Q�b�g
				CEffect* pObj = ite;
				pObj->Uninit();
				// �A�N�e�B�u���X�g����폜
				m_ActiveList.erase(m_ActiveList.begin() + num);
				// ���g�p���X�g�ɒǉ�
				m_UnusedList.push_back(pObj);

				break;
			}
			num++;
		}
	}
	// �폜���X�g�N���A
	m_DeleteList.clear();
}

//=============================================================================
// 
// �G�t�F�N�g�̃I�u�W�F�N�g�쐬
// 
//=============================================================================
void CEffectManager::CreateObject(int num)
{
	// �I�u�W�F�N�g�쐬
	for (int i = 0; i < num; i++)
	{
		CEffect* pObj = new CEffect;
		// ���g�p���X�g�ɓo�^
		m_UnusedList.push_back(pObj);
	}
}


