//=============================================================================
// ObjectManager.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "Object.h"
#include <Component/Transform.h>
#include <Renderer/Renderer.h>
#include <vector>
#include <list>
#include <memory>
#include <string>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
// �^��`
typedef std::shared_ptr<Object> obj_shared;
typedef std::weak_ptr<Object> obj_weak;

class ObjectManager
{
public:
	ObjectManager() = default;
	~ObjectManager() = default;

	// �I�u�W�F�N�g����
	template<class T>
	static obj_shared CreateObject(
		XMFLOAT3 pos = XMFLOAT3(0, 0, 0), 
		XMINT2 coord = XMINT2(0, 0),
		XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3 rot = XMFLOAT3(0, 0, 0))
	{
		obj_shared ptr;
		ptr.reset(new T());

		// �C���X�^���X�������ɏ����Z�b�g
		ptr->m_Pos = pos;
		ptr->m_Coord = coord;
		ptr->m_Scale = scale;
		ptr->m_Rot = rot;

		// �I�u�W�F�N�g���X�g�ɒǉ�
		AddObjList(ptr);
		return ptr;
	}

	// �I�u�W�F�N�g���X�g�ɒǉ�
	static void AddObjList(const obj_shared& pObj)
	{
		m_pObjList.emplace_back(pObj);
	}

	static void InitAll();	 // �S������
	static void UninitAll(); // �S�I��
	static void UpdateAll(); // �S�X�V
	static void DrawAll();	 // �S�`��

	// �I�u�W�F�N�g�폜
	static void DestroyObject(std::string tag);
	// �I�u�W�F�N�g�폜(�G�f�B�b�g�p)
	static bool DestroyEditObject(std::string tag, XMINT2 pos);
	// �^�O�T�[�`
	static std::weak_ptr<Object> SearchObjectTag(std::string tag);
	// �ړ��I�u�W�F�N�g�擾
	static std::weak_ptr<Object> GetObjectAtPosition(std::string tag ,XMINT2 pos);
	// �I�u�W�F�N�g�`�F�b�N
	static bool IsObject(std::string tag, XMINT2 pos);

private:
	//static std::vector<obj_shared> m_pObjList; // �C���X�^���X�i�[�p���X�g
	static std::list<obj_shared> m_pObjList; // �C���X�^���X�i�[�p���X�g

};