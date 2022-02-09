//=============================================================================
// CTitlePlayerObj.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TitlePlayerObj.h"
#include <Object/Player.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CTitlePlayerObj::CTitlePlayerObj()
{
	m_tag = "Player";
}
//=============================================================================
// 
// ����������
// 
//=============================================================================
void CTitlePlayerObj::Init()
{
	//// ���f���ǂݍ���
	m_Model.LoadModel(MODEL_PLAYER);
	m_Caterpillar = ObjectManager::CreateObject<CCaterpillar>();
	m_Gear = ObjectManager::CreateObject<CGear>();
	m_Generare = ObjectManager::CreateObject<CGenerare>();

	//// �A�j��No������
	m_Model.SetAnimeNo((int)PlayerAnime::eNone);
	m_Caterpillar->GetModel().SetAnimeNo((int)CaterpillarAnime::eMove);
	m_Gear->GetModel().SetAnimeNo((int)GearAnime::eMove);
	m_Generare->GetModel().SetAnimeNo((int)GenerareAnime::eMove);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CTitlePlayerObj::Update()
{
	// �A�j���Đ����Ԃ��擾
	CRenderer::AnimePlayTime();
}