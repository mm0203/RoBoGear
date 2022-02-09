//=============================================================================
// TitleFrame.h
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
class CTitleFrame : public CBaseTexture
{
public:
	CTitleFrame() = default;
	~CTitleFrame() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};