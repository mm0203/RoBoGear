//=============================================================================
// TimeLeap.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TimeLeap.h"

// �}�l�[�W���[
#include <Manager/ObjectManager.h>
#include <Manager/GameManager.h>

// �I�u�W�F�N�g
#include <Object/Player.h>
#include <Object/Trap.h>

//=============================================================================
// 
// �X�^�b�N���
// 
//=============================================================================
void CTimeLeap::ReleaseStack()
{
	// �X�^�b�N����ɂȂ�܂ŗv�f���폜
	while (!m_CoordStack.empty()) 
	{
		m_CoordStack.pop();
	}
	while (!m_DirStack.empty())
	{
		m_DirStack.pop();
	}
	while (!m_RoationStack.empty())
	{
		m_RoationStack.pop();
	}
}

//=============================================================================
// 
// �I�u�W�F�N�g�����߂�
// 
//=============================================================================
void CTimeLeap::RewindObject(std::string tag)
{
	// ���݂̏ꏊ���擾
	XMINT2 CurrentCoord = m_CoordStack.top();

	// �O��ړ������������擾
	ObjectDir dir = m_DirStack.top();

	// ���W����߂��I�u�W�F�N�g���擾
	const auto& obj = CObjectManager::GetObjectAtPosition(tag, CurrentCoord);

	// �߂��I�u�W�F�N�g���Ȃ�������
	if (obj.expired())
	{
		// �O��̈ړ������Əꏊ���폜
		m_CoordStack.pop();
		m_DirStack.pop();
		return;
	}
	// �߂��I�u�W�F�N�g�����݂��Ă���Ȃ�
	else if (!obj.expired())
	{
		// �I�u�W�F�N�g�̍��W�ƈړ��ʂ��擾
		XMINT2 Coord = obj.lock()->GetCoord();
		XMFLOAT3& Move = obj.lock()->GetMove();

		// �O��̈ړ���������ɏꏊ��߂�
		switch (dir)
		{
			// �O��̍s������Ȃ牺��
		case(ObjectDir::eUp):
			Move.z -= MovementObject;
			Coord.y++;
			break;
			// �O��̍s�������Ȃ���
		case(ObjectDir::eDown):
			Move.z += MovementObject;
			Coord.y--;
			break;
			// �O��̍s�������Ȃ�E��
		case(ObjectDir::eLeft):
			Move.x += MovementObject;
			Coord.x++;
			break;
			// �O��̍s�����E�Ȃ獶��
		case(ObjectDir::eRight):
			Move.x -= MovementObject;
			Coord.x--;
			break;
		default:
			break;
		}
		// �I�u�W�F�N�g�̍��W���X�V
		obj.lock()->SetCoord(Coord);
	}

	// �O��̈ړ������Əꏊ���폜
	m_CoordStack.pop();
	m_DirStack.pop();

	// �����𑝂₷
	if (tag == TagPlayer)
	IsStepCheck(TagTrap, CurrentCoord);
}

//=============================================================================
// 
// �폜�����I�u�W�F�N�g��߂�
// 
//=============================================================================
void CTimeLeap::RevivalObject(std::string tag)
{
	// ���݂̏ꏊ���擾
	XMINT2 CurrentCoord = m_CoordStack.top();

	// ���W����߂��I�u�W�F�N�g���擾
	const auto& obj = CObjectManager::GetUnusedObjectAtPosition(tag, CurrentCoord);

	// �߂��I�u�W�F�N�g���Ȃ�������
	if (obj.expired())
	{
		// �O��̏ꏊ���폜
		m_CoordStack.pop();
		return;
	}
	// �߂��I�u�W�F�N�g�����݂��Ă���Ȃ�
	else if (!obj.expired())
	{
		CObjectManager::UnusedToActive(tag);
	}

	// �O��̏ꏊ���폜
	m_CoordStack.pop();
}

//=============================================================================
// 
// �I�u�W�F�N�g�̌�����߂�
// 
//=============================================================================
void CTimeLeap::RewindRoationObject(std::string tag)
{
	// ���݂̏ꏊ���擾
	XMINT2 CurrentCoord = m_CoordStack.top();

	// ���݂̌������擾
	XMFLOAT3 CurrentRot = m_RoationStack.top();

	// ���W����߂��I�u�W�F�N�g���擾
	const auto& obj = CObjectManager::GetObjectAtPosition(tag, CurrentCoord);

	// �������X�V
	obj.lock()->SetRot(CurrentRot);

	// �O��̌������폜
	m_RoationStack.pop();
}

//=============================================================================
// 
// �v���C���[�����񂾏ꏊ���m�F
// 
//=============================================================================
void CTimeLeap::IsStepCheck(std::string tag, XMINT2& coord)
{
	int& nStep = CGameManager::GetStep();

	// �O�̏ꏊ�Ƀg���b�v������Ȃ�
	if (CObjectManager::IsObject(tag, coord))
	{
		nStep += 2;
	}
	// �O�̏ꏊ�Ƀg���b�v���Ȃ��Ȃ�
	else
	{
		nStep++;
	}
}
