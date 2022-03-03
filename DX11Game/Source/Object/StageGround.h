//=============================================================================
// meshfield.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/Object.h>
#include <Renderer/Mesh/mesh.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CStageGround : public Object
{
public:

	CStageGround();
	~CStageGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

private:
	// ステージ表示用メッシュ
	CMesh m_MeshField;
};

