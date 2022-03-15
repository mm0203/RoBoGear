//=============================================================================
// CClear.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/Object.h>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================
// モデル
#define MODEL_CLEAR "data/MODEL/Object/EV/Elevator_Ainm.fbx"
// タグ名
const std::string TagClear = "Clear";

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CClear : public CObject
{
public:
	CClear();
	~CClear() = default;

	void Init()	  override;
	void Update() override;
};
