//=============================================================================
// ObjectManager.cpp
//=============================================================================
// Author  ���� ���V
// 
//=============================================================================

#include "ObjectManager.h"

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================
std::list<obj_shared> CObjectManager::m_pObjList;

//=============================================================================
// 
// ������
// 
//=============================================================================
void CObjectManager::InitAll()
{
	for (auto& obj : m_pObjList)
		obj->Init();
}

//=============================================================================
// 
// �X�V
// 
//=============================================================================
void CObjectManager::UpdateAll()
{
	// �X�V���ɗv�f���폜����ꍇ������̂Ŕ͈�for���͎g�p�ł��Ȃ�
	for (auto it = m_pObjList.begin(); it != m_pObjList.end(); ++it)
		it->get()->Update();
}

//=============================================================================
// 
// �I��
// 
//=============================================================================
void CObjectManager::UninitAll()
{
	// �C���X�^���X�̐����擾
	int objCnt = (int)m_pObjList.size();

	// ���X�g���̃C���X�^���X���폜
	for (int i = 0; i < objCnt; i++)
	{
		obj_shared obj;						  // �폜�p�|�C���^
		obj = *(m_pObjList.begin());		  // �v�f�̃|�C���^
		obj->Uninit();						  // �v�f�̏I���������Ă�
		m_pObjList.erase(m_pObjList.begin()); // ���X�g����폜
	}
}

//=============================================================================
// 
// �`��
// 
//=============================================================================
void CObjectManager::DrawAll()
{
	for (auto& obj : m_pObjList)
		obj->Draw();
}

//=============================================================================
// 
// �I�u�W�F�N�g�폜
// 
//=============================================================================
void CObjectManager::DestroyObject(std::string tag)
{
	for (auto it = m_pObjList.begin(); it != m_pObjList.end();) 
	{
		// �^�O�����擾
		if(it->get()->GetTag() == tag)
		{
			it->get()->Uninit();		// �v�f�̏I���������Ă�
			it->reset();				// �v�f�̒��g�����
			it = m_pObjList.erase(it);	// ���X�g����폜
		}
		else ++it;	// �C�e���[�^�̎w���ꏊ�𐳏��
	}
}

//=============================================================================
// 
// �^�O�T�[�`
// 
//=============================================================================
std::weak_ptr<CObject> CObjectManager::SearchObjectTag(std::string tag)
{
	for (const auto& obj : m_pObjList)
	{
		// �^�O�����擾
		if (obj->GetTag() == tag)
			return obj;
	}
	return std::weak_ptr<CObject>();
}

//=============================================================================
// 
// �ړ��I�u�W�F�N�g�擾
// 
//=============================================================================
std::weak_ptr<CObject> CObjectManager::GetObjectAtPosition(std::string tag, XMINT2 pos)
{
	for (const auto& obj : m_pObjList)
	{
		// �^�O�����擾
		if (obj->GetTag() == tag)
		{
			// �^�O���̃|�W�V�����ƈ����̃|�W�V������������������
			if (obj->GetCoord() == pos)
				return obj;
		}
	}
	return std::weak_ptr<CObject>();
}

//=============================================================================
// 
// �I�u�W�F�N�g�`�F�b�N
// 
//=============================================================================
bool CObjectManager::IsObject(std::string tag, XMINT2 pos)
{
	for (const auto& obj : m_pObjList)
	{
		// �^�O�����擾
		if (obj->GetTag() == tag)
		{
			// �^�O���̃|�W�V�����ƈ����̃|�W�V������������������
			if (obj->GetCoord() == pos)
				return true;
		}
	}
	return false;
}

//=============================================================================
// 
// �G�f�B�b�g�폜
// 
//=============================================================================
bool CObjectManager::DestroyEditObject(std::string tag, XMINT2 pos)
{
	for (auto it = m_pObjList.begin(); it != m_pObjList.end();)
	{
		// �^�O�����擾
		if (it->get()->GetTag() == tag)
		{
			// �^�O���̃|�W�V�����ƈ����̃|�W�V������������������
			if (it->get()->GetCoord() == pos)
			{
				//it->get()->Uninit();		// �v�f�̏I���������Ă�
				it->reset();				// �v�f�̒��g�����
				it = m_pObjList.erase(it);	// ���X�g����폜
				return true;
			}
			else ++it;	// �C�e���[�^�̎w���ꏊ�𐳏��
		}
		else ++it;
	}
	return false;
}