//=============================================================================
// Object.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Component/Transform.h>
#include <Renderer/Renderer.h>

#include <vector>
#include <memory>
#include <string>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
// �I�u�W�F�N�g�N���X
class Object
{
public:
	Object();
	virtual ~Object() = default;

	friend class ObjectManager; // �t�����h�N���X

	virtual void Init() = 0;
	virtual void Uninit();
	virtual void Update() = 0;
	virtual void Draw();

	// getter
	//CTransform& GetTransform() { return m_Transform; }
	XMFLOAT3 GetPos() { return m_Pos; }
	XMINT2  GetCoord() { return m_Coord; }
	XMFLOAT3 GetScale() { return m_Scale; }
	XMFLOAT3 GetRot() { return m_Rot; }
	XMFLOAT3& GetMove() { return m_Move; }
	std::string GetTag() { return m_tag; }
	CRenderer& GetModel() { return m_Model; }

	// setter
	void SetPos(XMFLOAT3 pos) { m_Pos = pos; }
	void SetCoord(XMINT2 coord) { m_Coord = coord; }
	void SetScale(XMFLOAT3 scale) { m_Scale = scale; }
	void SetRot(XMFLOAT3 rot) { m_Rot = rot; }
	void SetMove(XMFLOAT3 move) { m_Move = move; }

	// �I�u�W�F�N�g�̊����ړ�
	void ObjectMove();

protected:
	// �I�u�W�F�N�g�̏��
	//CTransform m_Transform;

	XMFLOAT3 m_Pos;		// �ʒu
	XMINT2   m_Coord;	// ���W
	XMFLOAT3 m_Scale;	// �T�C�Y
	XMFLOAT3 m_Rot;		// ��]
	XMFLOAT3 m_Move;	// �ړ���
	std::string m_tag;	// �^�O��
	CRenderer m_Model;	// ���f�����
};