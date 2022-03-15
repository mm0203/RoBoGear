//=============================================================================
// CTitlePlayerObj.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/ObjectManager.h>
#include <Object/Caterpillar.h>
#include <Object/Gear.h>
#include <Object/Gear.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CTitlePlayerObj : public CObject
{
public:
	CTitlePlayerObj();
	~CTitlePlayerObj() = default;

	void Init();
	void Update();

private:
	// �v���C���[�p�[�c�̃C���X�^���X
	obj_shared m_Caterpillar;
	obj_shared m_Gear;
	obj_shared m_Generare;
};