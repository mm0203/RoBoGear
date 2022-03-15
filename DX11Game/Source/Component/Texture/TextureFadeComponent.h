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

	// �t�F�[�h�C��
	void FadeIn(CPolygon& polygon);
	void FadeIn(std::shared_ptr<CPolygon>& polygon);
	// �t�F�[�h�A�E�g
	void FadeOut(CPolygon& polygon);
	void FadeOut(std::shared_ptr<CPolygon>& polygon);
	// �t�F�[�h�C������A�E�g
	void FadeInOut(CPolygon& polygon);
	void FadeInOut(std::shared_ptr<CPolygon>& polygon);

private:
	// �t�F�[�h�̏��
	enum class FadeState
	{
		eNone,
		eFadeIn,	// �t�F�[�h�C��
		eFadeKeep,	// �t�F�[�h�ҋ@���
		eFadeOut,	// �t�F�[�h�A�E�g

		eMaxState,
	};

private:
	// �s�����x
	float m_fAlpha;
	// �t�F�[�h�ҋ@����
	int m_nFedeCount;
	// �t�F�[�h�̏��
	FadeState m_CurrentFade;
	// �t�F�[�h���Ă邩�ǂ���
	bool m_bFadeStae;

};