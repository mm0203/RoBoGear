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
std::list<obj_shared> CObjectManager::m_ActiveList;
std::list<obj_shared> CObjectManager::m_UnusedList;

//=============================================================================
// 
// ������
// 
//=============================================================================
void CObjectManager::InitAll()
{
	for (auto& obj : m_ActiveList)
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
	for (auto it = m_ActiveList.begin(); it != m_ActiveList.end(); ++it)
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
	int objCnt = (int)m_ActiveList.size();

	// �C���X�^���X���폜
	for (int i = 0; i < objCnt; i++)
	{
		obj_shared obj;					 		   // �폜�p�|�C���^
		obj = *(m_ActiveList.begin());			   // �v�f�̃|�C���^
		obj->Uninit();							   // �v�f�̏I���������Ă�
		m_ActiveList.erase(m_ActiveList.begin());  // ���X�g����폜
	}

	// ���g�p���X�g�ɂ���C���X�^���X�̐����擾
	objCnt = (int)m_UnusedList.size();

	// ���X�g���̃C���X�^���X���폜
	for (int i = 0; i < objCnt; i++)
	{
		obj_shared obj;					 	       // �폜�p�|�C���^
		obj = *(m_UnusedList.begin());			   // �v�f�̃|�C���^
		obj->Uninit();							   // �v�f�̏I���������Ă�
		m_UnusedList.erase(m_UnusedList.begin());  // ���X�g����폜
	}
}

//=============================================================================
// 
// �`��
// 
//=============================================================================
void CObjectManager::DrawAll()
{
	for (auto& obj : m_ActiveList)
		obj->Draw();
}

//=============================================================================
// 
// �I�u�W�F�N�g�폜
// 
//=============================================================================
void CObjectManager::DestroyObject(std::string tag)
{
	for (auto it = m_ActiveList.begin(); it != m_ActiveList.end(); it++)
	{
		// �^�O�����擾
		if(it->get()->GetTag() == tag)
		{
			// �폜����I�u�W�F�N�g�𖢎g�p���X�g�Ɉڂ�
			m_UnusedList.splice(m_UnusedList.begin(), m_ActiveList, it);
			return;

			//it->get()->Uninit();		   // �v�f�̏I���������Ă�
			//it->reset();				   // �v�f�̒��g�����
			//it = m_ActiveList.erase(it); // ���X�g����폜
		}
		//else ++it;	// �C�e���[�^�̎w���ꏊ�𐳏��
	}
}

//=============================================================================
// 
// ���g�p���X�g����g�p���X�g��
// 
//=============================================================================
void CObjectManager::UnusedToActive(std::string tag)
{
	for (auto it = m_UnusedList.begin(); it != m_UnusedList.end(); it++)
	{
		// ���g�p���X�g������o��
		if (it->get()->GetTag() == tag)
		{
			// ���g�p���X�g�̃I�u�W�F�N�g���g�p���X�g�̖�����
			m_ActiveList.splice(m_ActiveList.end(), m_UnusedList, it);
			return;
		}
	}
}

//=============================================================================
// 
// �^�O�T�[�`
// 
//=============================================================================
std::weak_ptr<CObject> CObjectManager::SearchObjectTag(std::string tag)
{
	for (const auto& obj : m_ActiveList)
	{
		// �^�O�����擾
		if (obj->GetTag() == tag)
			return obj;
	}
	return std::weak_ptr<CObject>();
}

//=============================================================================
// 
// �g�p���X�g����ړ��I�u�W�F�N�g�擾
// 
//=============================================================================
std::weak_ptr<CObject> CObjectManager::GetObjectAtPosition(std::string tag, XMINT2 pos)
{
	for (const auto& obj : m_ActiveList)
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
// ���g�p���X�g����ړ��I�u�W�F�N�g�擾
// 
//=============================================================================
std::weak_ptr<CObject> CObjectManager::GetUnusedObjectAtPosition(std::string tag, XMINT2 pos)
{
	for (const auto& obj : m_UnusedList)
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
	for (const auto& obj : m_ActiveList)
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
	for (auto it = m_ActiveList.begin(); it != m_ActiveList.end();)
	{
		// �^�O�����擾
		if (it->get()->GetTag() == tag)
		{
			// �^�O���̃|�W�V�����ƈ����̃|�W�V������������������
			if (it->get()->GetCoord() == pos)
			{
				//it->get()->Uninit();		// �v�f�̏I���������Ă�
				it->reset();				// �v�f�̒��g�����
				it = m_ActiveList.erase(it);	// ���X�g����폜
				return true;
			}
			else ++it;	// �C�e���[�^�̎w���ꏊ�𐳏��
		}
		else ++it;
	}
	return false;
}