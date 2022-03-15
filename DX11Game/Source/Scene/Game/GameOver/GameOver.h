//=============================================================================
// GameOver.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/Sprite.h>
#include "GameOverBackGround.h"
#include "GameOverLogo.h"
#include <list>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CGameOver : public CSprite
{
public:
	CGameOver();
	~CGameOver() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	std::shared_ptr<CGameOverBackGround> m_GameOverBackGround;
	std::shared_ptr<CGameOverLogo> m_GameOverLogo;

private:
	std::list<tex_shared> m_pGameOverTextures;
};