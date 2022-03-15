//=============================================================================
// Gear.h
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
// タグ名
const std::string TagGear = "Gear";

// ギアアニメ
enum class GearAnime
{
	eNone = 0,
	eMove,
	GearAnimeMax
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CGear : public CObject
{
public:
	CGear();
	~CGear() = default;

	void Init()	  override;
	void Update() override;
};