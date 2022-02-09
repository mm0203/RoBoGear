//=============================================================================
// GameStep.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Component/Texture/TextureFadeComponent.h>
#include <Component/DrawNumber.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CGameStep : public CBaseTexture
{
public:
	CGameStep();
	~CGameStep() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

	void FadeOut();

private:
	enum GameStep
	{
		eGameStep,
		eGameStepFrame,
		eGameStepMax
	};
private:
	CNumber m_Number;
	float m_fAngle;
	std::vector<CTextureFadeComponent> m_TextureFades;
};