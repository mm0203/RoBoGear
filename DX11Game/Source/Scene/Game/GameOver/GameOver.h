//=============================================================================
// GameOver.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Sprite.h>
#include "GameOverBackGround.h"
#include "GameOverLogo.h"
#include <list>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CGameOver : public Sprite
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