//=============================================================================
// StageSelectScene.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/SceneManager.h>
#include <Renderer/Polygon/CPolygon.h>
#include <Scene/StageSelect/SelectTexture/StageSelectTexture.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CStageSelectScene : public CScene
{
public:
	CStageSelectScene();
	~CStageSelectScene() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

private:
	CStageSelectTexture m_StageSelectTexture;
};

