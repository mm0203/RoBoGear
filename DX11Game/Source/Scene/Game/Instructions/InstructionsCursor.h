//=============================================================================
// InstructionsCursor.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>
#include <Component/Texture/TextureMoveComponent.h>

//=============================================================================
// 
// �N���X��`
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

	// �J�[�\���ړ��֐�
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

