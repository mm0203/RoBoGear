//=============================================================================
// InstructionsCursor.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>
#include <Component/Texture/TextureMoveComponent.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CInstructionsCursor : public CBaseTexture
{
public:
	CInstructionsCursor() = default;
	~CInstructionsCursor() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

	void MoveCursor(int index);
private:
	std::vector<CPolygon> m_Polygons;
	std::vector<CTextureMoveComponent> m_TextureMoves;

private:
	enum eCursor
	{
		eRight,
		eLeft,
		eCursorMax
	};
};

