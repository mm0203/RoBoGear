//=============================================================================
// GameScene.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/SceneManager.h>
#include <Manager/GameManager.h>
#include <memory>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene() = default;

	void Init()    override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;

	// 各スプライトのインスタンス生成関数
	void CreateSpriteInstance();

private:
	GameState m_State;
};