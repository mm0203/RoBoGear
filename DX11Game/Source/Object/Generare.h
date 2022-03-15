//=============================================================================
// Generare.h
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
const std::string TagGenerare = "Generare";

// 歯車アニメ
enum class GenerareAnime
{
	eNone = 0,
	eMove,
	GenerareAnimeMax
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CGenerare : public CObject
{
public:
	CGenerare();
	~CGenerare() = default;

	void Init()	  override;
	void Update() override;
};