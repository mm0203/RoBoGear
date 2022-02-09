//=============================================================================
// InstructionsBackGround.h
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
class CInstructionsBackGround : public CBaseTexture
{
public:
	CInstructionsBackGround() = default;
	~CInstructionsBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};

