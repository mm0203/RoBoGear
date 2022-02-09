//=============================================================================
// GameOverLogo.h
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
class CGameOverLogo : public CBaseTexture
{
public:
	CGameOverLogo();
	~CGameOverLogo() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};