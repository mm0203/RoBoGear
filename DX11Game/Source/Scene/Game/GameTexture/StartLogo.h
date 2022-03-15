//=============================================================================
// StartLogo.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Component/Texture/TextureFadeComponent.h>
#include <Component/DrawNumber.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CStartLogo : public CBaseTexture
{
public:
	CStartLogo();
	~CStartLogo() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

private:
	enum StartLogo
	{
		eStartLogo,		// ステージロゴ
		eStartNumber,	// ステージナンバー
		eStartLogoMax
	};

private:
	CNumber m_Number;
	int m_nTime;
	float m_TextMove;
	std::vector<CTextureFadeComponent> m_TextureFades;
};

