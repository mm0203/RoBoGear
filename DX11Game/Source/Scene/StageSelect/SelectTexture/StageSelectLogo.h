//=============================================================================
// StageSelectLogo.h
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
class CStageSelectLogo : public CBaseTexture
{
public:
	CStageSelectLogo();
	~CStageSelectLogo() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};