//=============================================================================
// Caterpillar.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/Object.h>

// キャタピラアニメ
enum class CaterpillarAnime
{
	eMove = 0,
	eNone,
	eCaterpillarAnimeMax
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CCaterpillar : public Object
{
public:
	CCaterpillar();
	~CCaterpillar() = default;

	void Init()	  override;
	void Update() override;
};