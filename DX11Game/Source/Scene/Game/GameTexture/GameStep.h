//=============================================================================
// GameStep.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Component/Texture/TextureFadeComponent.h>
#include <Component/DrawNumber.h>

//=============================================================================
// 
// �N���X��`
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
		eGameStep,		// ����
		eGameStepFrame,	// �����̎���̎���
		eGameStepMax
	};
private:
	CNumber m_Number;
	float m_fAngle;	// ��]
	std::vector<CTextureFadeComponent> m_TextureFades;
};