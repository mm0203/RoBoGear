//=============================================================================
// GameOverBackGround.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CGameOverBackGround : public CBaseTexture
{
public:
	CGameOverBackGround();
	~CGameOverBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

private:
	float m_fAlpha;	 // 不透明度
};