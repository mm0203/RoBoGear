//=============================================================================
// GameBackGround.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CGameBackGround : public CBaseTexture
{
public:
	CGameBackGround();
	~CGameBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

	void FadeOut();

private:
	enum GameNotmoveTexture
	{
		eBackGroundFrame,
		eOperation,
		GameNotmoveTextureMax
	};

private:
	std::vector<CPolygon> m_Polygons;
	std::vector<CTextureFadeComponent> m_TextureFades;
	float m_fAngle;
};
