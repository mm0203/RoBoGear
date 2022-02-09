//=============================================================================
// StageBackGround.h
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
class CStageSelectBackGround : public CBaseTexture
{
public:
	CStageSelectBackGround() = default;
	~CStageSelectBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};