//=============================================================================
// EditScene.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "Editor.h"
#include <Manager/SceneManager.h>
#include <Object/StageGround.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CEditScene : public CScene
{
public:
	CEditScene();
	~CEditScene() = default;

	void Init()    override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;

private:
	CStageGround m_Field;
	CEditor m_Editor;
};