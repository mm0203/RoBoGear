//=============================================================================
// CCube.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/Object.h>

#define MODEL_CUBE "data/MODEL/Object/Magnet/Magnet1.fbx"

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CCube : public Object
{
public:
	CCube();
	~CCube() = default;

	void Init()	  override;
	void Update() override;

private:
	int m_nCount;
	std::string m_energyOnTexture;		// 通電時のテクスチャ
	std::string m_energyOffTexture;		// 非通電時のテクスチャ
};