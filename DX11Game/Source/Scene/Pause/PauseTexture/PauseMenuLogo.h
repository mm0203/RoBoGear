//=============================================================================
// CPauseMenuLogo.h
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
class CPauseMenuLogo : public CBaseTexture
{
public:
	CPauseMenuLogo();
	~CPauseMenuLogo() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};