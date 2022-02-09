//=============================================================================
// CGameTexture.h
//=============================================================================
// Author  èºñÏ è´îV
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
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CGameTexture : public Sprite
{
public:
	CGameTexture();
	~CGameTexture() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	int m_nCount;
	std::shared_ptr<CGameBackGround> m_GameBackGround;
	std::shared_ptr<CGameStep> m_GameStep;
	std::shared_ptr<CStartLogo> m_Start;
	std::shared_ptr<CClearLogo> m_Clear;

private:
	std::list<tex_shared> m_pGameTextures;
};