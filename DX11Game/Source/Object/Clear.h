//=============================================================================
// CClear.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Object.h>

#define MODEL_CLEAR "data/MODEL/Object/EV/Elevator_Ainm.fbx"

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CClear : public Object
{
public:
	CClear();
	~CClear() = default;

	void Init()	  override;
	void Update() override;
};
