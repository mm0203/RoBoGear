//=============================================================================
// StageSelectCursor.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include "StageSelectLevel.h"

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CStageSelectCursor : public CBaseTexture
{
public:
	CStageSelectCursor();
	~CStageSelectCursor() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

	void TextureChage(int index);

private:
	CStageSelectLevel m_StageSelectLevel;
};