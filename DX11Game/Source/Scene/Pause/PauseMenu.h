//=============================================================================
// PauseMenu.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/Sprite.h>
#include <Scene/Pause/PauseTexture/PauseMenuTexture.h>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================
enum PauseMenu
{
	ePause_Continue,
	ePause_Retry,
	ePause_StageSelect,
	ePause_Title,
	ePauseMenuMax
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CPauseMenu : public Sprite
{
public:
	CPauseMenu();
	~CPauseMenu() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	CPauseMenuTexture m_PuaseMenuTexture;
	int m_nMenuIndex;
};

