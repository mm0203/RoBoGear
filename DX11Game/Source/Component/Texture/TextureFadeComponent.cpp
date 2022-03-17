//=============================================================================
// CTextureFadeComponent.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TextureFadeComponent.h"

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
namespace
{
	// 60/60��1�t���[�� 1/60��1�b
	constexpr float FadeInSpeed = 1.2f / 60.0f;
	constexpr float FadeOutSpeed = 1.8f / 60.0f;
	float FadeKeep = 2.0f;	// �b

}
//=============================================================================
// 
// �R���X�g���N�^
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
// �e�N�X�`���t�F�[�h�C��
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
// �e�N�X�`���t�F�[�h�C��
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
// �e�N�X�`���t�F�[�h�A�E�g
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
// �e�N�X�`���t�F�[�h�A�E�g
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
// �e�N�X�`���t�F�[�h�C���A�E�g
// 
//=============================================================================
void CTextureFadeComponent::FadeInOut(CPolygon& polygon)
{
	switch (m_CurrentFade)
	{
	case (FadeState::eNone): // �������
		m_CurrentFade = FadeState::eFadeIn;
		break;

	case (FadeState::eFadeIn): // �t�F�[�h�C��
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

	case (FadeState::eFadeKeep):	// �t�F�[�h�ҋ@
		m_nFedeCount++;

		// 2�b�𒴂�����
		if (m_nFedeCount >= (Second * 2))
		{
			m_CurrentFade = FadeState::eFadeOut;
			m_nFedeCount = 0;
		}
		break;
	case (FadeState::eFadeOut): // �t�F�[�h�A�E�g
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
// �e�N�X�`���t�F�[�h�C���A�E�g
// 
//=============================================================================
void CTextureFadeComponent::FadeInOut(std::shared_ptr<CPolygon>& polygon, float FadeKeep)
{
	switch (m_CurrentFade)
	{
	case (FadeState::eNone): // �������
		m_CurrentFade = FadeState::eFadeIn;
		break;

	case (FadeState::eFadeIn): // �t�F�[�h�C��
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

	case (FadeState::eFadeKeep):	// �t�F�[�h�ҋ@
		m_nFedeCount++;

		// 2�b�𒴂�����
		if (m_nFedeCount >= (FadeKeep))
		{
			m_CurrentFade = FadeState::eFadeOut;
			m_nFedeCount = 0;
		}
		break;
	case (FadeState::eFadeOut): // �t�F�[�h�A�E�g
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