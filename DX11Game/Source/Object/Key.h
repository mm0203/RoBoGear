//=============================================================================
// CKey.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Object.h>

#define MODEL_KEY "data/MODEL/Object/Lift_Line/Gear2.fbx"	

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CKey : public Object
{
public:

	CKey();
	~CKey() = default;

	void Init()	  override;
	void Update() override;
};