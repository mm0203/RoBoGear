//=============================================================================
// CTitleCubeObj.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/ObjectManager.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CTitleCubeObj : public Object
{
public:
	CTitleCubeObj() = default;
	~CTitleCubeObj() = default;

	void Init();
	void Update();
};