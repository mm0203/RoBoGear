//=============================================================================
// EditOperationUI.h
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