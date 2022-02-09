//=============================================================================
// GameOverBackGround.h
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
	float m_fAlpha;	 // �s�����x
};