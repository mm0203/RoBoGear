//=============================================================================
// GameStep.h
//=============================================================================
// Author  ¼–ì «”V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Component/Texture/TextureFadeComponent.h>
#include <Component/DrawNumber.h>

//=============================================================================
// 
// ƒNƒ‰ƒX’è‹`
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
		eGameStep,		// •à”
		eGameStepFrame,	// •à”‚Ìü‚è‚Ì•Ô
		eGameStepMax
	};
private:
	CNumber m_Number;
	float m_fAngle;	// ‰ñ“]
	std::vector<CTextureFadeComponent> m_TextureFades;
};