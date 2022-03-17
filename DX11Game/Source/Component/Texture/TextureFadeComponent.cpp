//=============================================================================
// CTextureFadeComponent.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TextureFadeComponent.h"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
namespace
{
	// 60/60は1フレーム 1/60は1秒
	constexpr float FadeInSpeed = 1.2f / 60.0f;
	constexpr float FadeOutSpeed = 1.8f / 60.0f;
	float FadeKeep = 2.0f;	// 秒

}
//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CTextureFadeComponent::CTextureFadeComponent()
{
	m_fAlpha = 0.0f;
	m_nFedeCount = 0;
	m_CurrentFade = FadeState::eNone;
	m_bFadeStae = true;

}
//=============================================================================
// 
// テクスチャフェードイン
// 
//=============================================================================
void CTextureFadeComponent::FadeIn(CPolygon& polygon)
{
	m_fAlpha += FadeInSpeed;
	if (m_fAlpha >= 1.0f)
	{
		m_fAlpha = 1.0f;
		m_bFadeStae = false;
	}
	polygon.SetAlpha(m_fAlpha);
}

//=============================================================================
// 
// テクスチャフェードイン
// 
//=============================================================================
void CTextureFadeComponent::FadeIn(std::shared_ptr<CPolygon>& polygon)
{
	m_fAlpha += FadeInSpeed;
	if (m_fAlpha >= 1.0f)
	{
		m_fAlpha = 1.0f;
		m_bFadeStae = false;
	}
	polygon->SetAlpha(m_fAlpha);
}

//=============================================================================
// 
// テクスチャフェードアウト
// 
//=============================================================================
void CTextureFadeComponent::FadeOut(CPolygon& polygon)
{
	m_fAlpha -= FadeOutSpeed;
	if (m_fAlpha <= 0.0f)
	{
		m_fAlpha = 0.0f;
		m_bFadeStae = false;
	}
	polygon.SetAlpha(m_fAlpha);
}

//=============================================================================
// 
// テクスチャフェードアウト
// 
//=============================================================================
void CTextureFadeComponent::FadeOut(std::shared_ptr<CPolygon>& polygon)
{
	m_fAlpha -= FadeOutSpeed;
	if (m_fAlpha <= 0.0f)
	{
		m_fAlpha = 0.0f;
		m_bFadeStae = false;
	}
	polygon->SetAlpha(m_fAlpha);
}

//=============================================================================
// 
// テクスチャフェードインアウト
// 
//=============================================================================
void CTextureFadeComponent::FadeInOut(CPolygon& polygon)
{
	switch (m_CurrentFade)
	{
	case (FadeState::eNone): // 初期状態
		m_CurrentFade = FadeState::eFadeIn;
		break;

	case (FadeState::eFadeIn): // フェードイン
		if (m_fAlpha <= 1.0f)
		{
			m_fAlpha += FadeInSpeed;
		}
		else if (m_fAlpha >= 1.0f)
		{
			m_CurrentFade = FadeState::eFadeKeep;
		}
		polygon.SetAlpha(m_fAlpha);
		break;

	case (FadeState::eFadeKeep):	// フェード待機
		m_nFedeCount++;

		// 2秒を超えたら
		if (m_nFedeCount >= (Second * 2))
		{
			m_CurrentFade = FadeState::eFadeOut;
			m_nFedeCount = 0;
		}
		break;
	case (FadeState::eFadeOut): // フェードアウト
		if (m_fAlpha >= 0.0f)
		{
			m_fAlpha -= FadeOutSpeed;
		}
		else if (m_fAlpha <= 0.0f)
		{
			m_fAlpha = 0.0f;
			m_bFadeStae = false;
		}
		polygon.SetAlpha(m_fAlpha);
		break;
	}
}

//=============================================================================
// 
// テクスチャフェードインアウト
// 
//=============================================================================
void CTextureFadeComponent::FadeInOut(std::shared_ptr<CPolygon>& polygon, float FadeKeep)
{
	switch (m_CurrentFade)
	{
	case (FadeState::eNone): // 初期状態
		m_CurrentFade = FadeState::eFadeIn;
		break;

	case (FadeState::eFadeIn): // フェードイン
		if (m_fAlpha <= 1.0f)
		{
			m_fAlpha += FadeInSpeed;
		}
		else if (m_fAlpha >= 1.0f)
		{
			m_CurrentFade = FadeState::eFadeKeep;
		}
		polygon->SetAlpha(m_fAlpha);
		break;

	case (FadeState::eFadeKeep):	// フェード待機
		m_nFedeCount++;

		// 2秒を超えたら
		if (m_nFedeCount >= (FadeKeep))
		{
			m_CurrentFade = FadeState::eFadeOut;
			m_nFedeCount = 0;
		}
		break;
	case (FadeState::eFadeOut): // フェードアウト
		if (m_fAlpha >= 0.0f)
		{
			m_fAlpha -= FadeOutSpeed;
		}
		else if (m_fAlpha <= 0.0f)
		{
			m_fAlpha = 0.0f;
			m_bFadeStae = false;
		}
		polygon->SetAlpha(m_fAlpha);
		break;
	}
}