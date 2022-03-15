//=============================================================================
// CGameTexture.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "GameBackGround.h"
#include "StartLogo.h"
#include "ClearLogo.h"
#include "GameStep.h"
#include <Manager/Sprite.h>
#include <list>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CGameTexture : public CSprite
{
public:
	CGameTexture();
	~CGameTexture() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	// �b���o�ߗp
	int m_nCount;
	// �w�i
	std::shared_ptr<CGameBackGround> m_GameBackGround;
	// ����
	std::shared_ptr<CGameStep> m_GameStep;
	// �X�e�[�W�J�n���S
	std::shared_ptr<CStartLogo> m_Start;
	// �N���A���S
	std::shared_ptr<CClearLogo> m_Clear;

private:
	std::list<tex_shared> m_pGameTextures;
};