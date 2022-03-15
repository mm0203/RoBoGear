//=============================================================================
// CTitleTexture.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include "TitleMenuChoices.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "TitleFrame.h"
#include <list>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CTitleTexture
{
public:
	CTitleTexture();
	~CTitleTexture() = default;

	void Init();
	void Uninit();
	void Update(int index);
	void Draw();

private:
	// 背景
	std::shared_ptr<CTitleBackGround> m_TitleBackGround;
	// タイトルシーンの歯車画像
	std::shared_ptr<CTitleFrame> m_TitleFrame;
	// カーソル
	std::shared_ptr<CTitleMenuChoices> m_TitleMenuChoices;
	// タイトルロゴ
	std::shared_ptr<CTitleLogo> m_TitleLogo;

private:
	std::list<tex_shared> m_pTitleTextures;
};