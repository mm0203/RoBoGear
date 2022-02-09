//=============================================================================
// CTitlePlayerObj.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/ObjectManager.h>
#include <Object/Caterpillar.h>
#include <Object/Gear.h>
#include <Object/Gear.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CTitlePlayerObj : public Object
{
public:
	CTitlePlayerObj();
	~CTitlePlayerObj() = default;

	void Init();
	void Update();

private:
	obj_shared m_Caterpillar;
	obj_shared m_Gear;
	obj_shared m_Generare;
};