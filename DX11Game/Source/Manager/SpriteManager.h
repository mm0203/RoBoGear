//=============================================================================
// SpriteManager.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "Sprite.h"
#include "GameManager.h"

#include <vector>
#include <memory>
#include <string>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================

// �O���錾
class CSprite;

// �^��`
typedef std::shared_ptr<CSprite> sprite_shared;
typedef std::weak_ptr<CSprite> sprite_weak;

class CSpriteManager
{
public:
	CSpriteManager() = default;
	~CSpriteManager() = default;

	// �X�v���C�g����
	template<class T>
	static sprite_shared CreateSprite()
	{
		sprite_shared ptr;
		ptr.reset(new T());

		// �X�v���C�g���X�g�ɒǉ�
		AddSpriteList(ptr);
		return ptr;
	}

	// �I�u�W�F�N�g���X�g�ɒǉ�
	static void AddSpriteList(const sprite_shared& pObj)
	{
		m_pSpriteList.emplace_back(pObj);
	}

	static void InitAll();	 // �S������
	static void UninitAll(); // �S�I��
	static void UpdateAll(GameState state); // �S�X�V
	static void DrawAll(GameState state);	// �S�`��


private:
	static std::vector<sprite_shared> m_pSpriteList; // �C���X�^���X�i�[�p���X�g

};