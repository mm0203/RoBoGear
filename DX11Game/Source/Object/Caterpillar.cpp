//=============================================================================
// Caterpillar.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "Caterpillar.h"
#include <Manager/ObjectManager.h>
#include "Player.h"

#define MODEL_CATERPILLAR "data/model/Object/MainAnim_Blender/Caterpillar_Anim.fbx"

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CCaterpillar::CCaterpillar()
{
	m_tag = TagCaterpillar;
	m_Model.LoadModel(MODEL_CATERPILLAR);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CCaterpillar::Init()
{

}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CCaterpillar::Update()
{
	// �v���C���[�̍��W�Ɠ����ꏊ��
	const auto& player = CObjectManager::SearchObjectTag(TagPlayer);
	m_Pos = player.lock()->GetPos();
	m_Scale = player.lock()->GetScale();
	m_Rot = player.lock()->GetRot();
}
