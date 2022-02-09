//=============================================================================
// meshfield.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Object.h>
#include <Renderer/Mesh/mesh.h>

//=============================================================================
// 
// �N���X��`
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

