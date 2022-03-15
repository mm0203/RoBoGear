//=============================================================================
// Sprite.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "SpriteManager.h"
#include "GameManager.h"

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CSprite
{
public:
	CSprite() = default;
	virtual ~CSprite() = default;

	friend class CSpriteManager; // �t�����h�N���X

	virtual void Init() = 0;
	virtual void Uninit() = 0;

	// ��ԂŃX�v���C�g�̕\���E��\�����Ǘ�
	virtual void Update(GameState state) = 0;
	virtual void Draw(GameState state) = 0;
};