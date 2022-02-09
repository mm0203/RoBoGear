//=============================================================================
// CTextureFadeComponent.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Renderer/Polygon/CPolygon.h>

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

	void FadeIn(CPolygon& polygon);
	void FadeIn(std::shared_ptr<CPolygon>& polygon);
	void FadeOut(CPolygon& polygon);
	void FadeOut(std::shared_ptr<CPolygon>& polygon);
	void FadeInOut(CPolygon& polygon);
	void FadeInOut(std::shared_ptr<CPolygon>& polygon);

private:
	enum class FadeState
	{
		eNone,
		eFadeIn,
		eFadeKeep,
		eFadeOut,

		eMaxState,
	};

private:
	float m_fAlpha;				// 不透明度
	int m_nFedeCount;			// フェード待機時間
	FadeState m_CurrentFade;	// フェード
	bool m_bFadeStae;

};