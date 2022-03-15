//=============================================================================
// CTitlePlayerObj.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/ObjectManager.h>
#include <Object/Caterpillar.h>
#include <Object/Gear.h>
#include <Object/Gear.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CTitlePlayerObj : public CObject
{
public:
	CTitlePlayerObj();
	~CTitlePlayerObj() = default;

	void Init();
	void Update();

private:
	// プレイヤーパーツのインスタンス
	obj_shared m_Caterpillar;
	obj_shared m_Gear;
	obj_shared m_Generare;
};