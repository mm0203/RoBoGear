//=============================================================================
// TimeLeap.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once
#include <main.h>
#include <Manager/Object.h>
#include <string>
#include <stack>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CTimeLeap
{
public:
	CTimeLeap() = default;
	~CTimeLeap() = default;

	// �X�^�b�N���
	void ReleaseStack();
	// �I�u�W�F�N�g�����߂�
	void RewindObject(std::string tag);
	// �폜�����I�u�W�F�N�g��߂�
	void RevivalObject(std::string tag);
	// �I�u�W�F�N�g�̌�����߂�
	void RewindRoationObject(std::string tag);
	// �v���C���[�̕����X�V
	void IsStepCheck(std::string tag, XMINT2& coord);

	// �X�^�b�N�ǉ�
	void AddCoordStack(XMINT2& coord)
	{
		m_CoordStack.push(coord);
	}
	void AddDirStackAdd(ObjectDir& dir)
	{
		m_DirStack.push(dir);
	}
	void AddRoationStackAdd(XMFLOAT3& rot)
	{
		m_RoationStack.push(rot);
	}

	// getter
	std::stack<XMINT2> GetCoordStack() { return m_CoordStack; }
	std::stack<ObjectDir> GetDirStack() { return m_DirStack; }

private:
	// �����߂��p�̍��W�X�^�b�N
	std::stack<XMINT2> m_CoordStack;
	// �����߂��p�̈ړ������X�^�b�N
	std::stack<ObjectDir> m_DirStack;
	// �����߂��p�̌����X�^�b�N
	std::stack<XMFLOAT3> m_RoationStack;
};