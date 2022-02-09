//=============================================================================
// CTextureFadeComponent.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// �N���X��`
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
	float m_fAlpha;				// �s�����x
	int m_nFedeCount;			// �t�F�[�h�ҋ@����
	FadeState m_CurrentFade;	// �t�F�[�h
	bool m_bFadeStae;

};