//=============================================================================
// TimeLeapTexture.h
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
class CTimeLeapTexture : public CBaseTexture
{
public:
	CTimeLeapTexture();
	~CTimeLeapTexture() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};