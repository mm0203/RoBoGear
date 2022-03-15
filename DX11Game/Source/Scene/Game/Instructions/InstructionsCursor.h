//=============================================================================
// InstructionsCursor.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>
#include <Component/Texture/TextureMoveComponent.h>

//=============================================================================
// 
// クラス定義
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

	// カーソル移動関数
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

