//=============================================================================
// PauseMenuBackGround.h
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
class CPauseMenuBackGround : public CBaseTexture
{
public:
	CPauseMenuBackGround() = default;
	~CPauseMenuBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};