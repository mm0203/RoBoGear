//=============================================================================
// CPauseMenuChoices.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CPauseMenuChoices : public CBaseTexture
{
public:
	CPauseMenuChoices();
	~CPauseMenuChoices() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	
	void ColorChange(int index);

private:
	std::vector<CPolygon> m_Polygons;
};