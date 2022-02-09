//=============================================================================
// EditOperationUI.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CEditOperationUI : public CBaseTexture
{
public:
	CEditOperationUI() = default;
	~CEditOperationUI() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};