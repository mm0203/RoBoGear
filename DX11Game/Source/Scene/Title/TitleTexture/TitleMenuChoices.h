//=============================================================================
// TitleMenuChoices.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>

//=============================================================================
// 
// �N���X��`
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

	void MenuChoices(int index);

private:
	std::vector<CPolygon> m_Polygons;
};