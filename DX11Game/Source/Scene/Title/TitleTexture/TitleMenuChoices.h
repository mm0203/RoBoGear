//=============================================================================
// TitleMenuChoices.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CTitleMenuChoices : public CBaseTexture
{
public:
	CTitleMenuChoices();
	~CTitleMenuChoices() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

	// 選択肢変更
	void MenuChoices(int index);

private:
	std::vector<CPolygon> m_Polygons;
};