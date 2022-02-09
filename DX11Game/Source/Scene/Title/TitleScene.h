//=============================================================================
// TitleScene.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/SceneManager.h>
#include <Renderer/Polygon/CPolygon.h>
#include <Scene/Title/TitleTexture/TitleTexture.h>
#include <vector>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================
enum TitleMenu
{
	eTitle_Start,
	eTitle_Edit,
	eTitle_Exit,
	eTitle_Max
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

private:
	CTitleTexture m_TitleTexture;
	int m_nMenuIndex;
	bool m_bButton;
};

