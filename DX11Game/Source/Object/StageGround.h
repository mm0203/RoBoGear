//=============================================================================
// meshfield.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/Object.h>
#include <Renderer/Mesh/mesh.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
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
	CMesh m_MeshField;
};

