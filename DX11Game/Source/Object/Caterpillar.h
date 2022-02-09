//=============================================================================
// Caterpillar.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Object.h>

// �L���^�s���A�j��
enum class CaterpillarAnime
{
	eMove = 0,
	eNone,
	eCaterpillarAnimeMax
};

//=============================================================================
// 
// �N���X��`
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