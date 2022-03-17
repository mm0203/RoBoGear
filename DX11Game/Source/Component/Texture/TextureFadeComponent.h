//=============================================================================
// CTextureFadeComponent.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Renderer/Polygon/CPolygon.h>
#include <Manager/GameManager.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CTextureFadeComponent
{
public:
	CTextureFadeComponent();
	~CTextureFadeComponent() = default;

	// getter
	bool GetFadeState() { return m_bFadeStae; }

	// setter
	void SetAlpha(float alpha) { m_fAlpha = alpha; }

	// フェードイン
	void FadeIn(CPolygon& polygon);
	void FadeIn(std::shared_ptr<CPolygon>& polygon);
	// フェードアウト
	void FadeOut(CPolygon& polygon);
	void FadeOut(std::shared_ptr<CPolygon>& polygon);
	// フェードインからアウト
	void FadeInOut(CPolygon& polygon);
	void FadeInOut(std::shared_ptr<CPolygon>& polygon, float FadeKeep = Second * 2);

private:
	// フェードの状態
	enum class FadeState
	{
		eNone,
		eFadeIn,	// フェードイン
		eFadeKeep,	// フェード待機状態
		eFadeOut,	// フェードアウト

		eMaxState,
	};

private:
	// 不透明度
	float m_fAlpha;
	// フェード待機時間
	int m_nFedeCount;
	// フェードの状態
	FadeState m_CurrentFade;
	// フェードしてるかどうか
	bool m_bFadeStae;

};