//=============================================================================
// CGame.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/SceneManager.h>
#include <Manager/GameManager.h>
#include <memory>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene() = default;

	void Init()    override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;

	void CreateSpriteInstance();

private:
	GameState m_State;

};