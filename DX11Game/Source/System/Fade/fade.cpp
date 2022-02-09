//=============================================================================
// Fade.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "fade.h"
#include <System/Sound/Sound.h>

#define FADE_RATE	0.02f

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
Fade::Fade()
{
	m_fAlpha = 0.0f;
	m_nFade = FADE_IN;
	m_pNextScene = nullptr;
	m_FadeCount = 0;
	m_nTexNo = 0;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void Fade::Init()
{
	m_FadePolygon.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_FadePolygon.SetTex(nullptr);
	m_FadePolygon.SetColor(0.0f,0.0f,0.0f);	// ��ʂ����F��

	m_FadeTexture.Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void Fade::Uninit()
{
	m_FadeTexture.Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void Fade::Update()
{
	// ���̃V�[�����ݒ肳��Ă��Ȃ���΃X�L�b�v
	if (m_nFade == FADE_NONE)	return;
	//if (!m_pNextScene)	return;

	m_FadePolygon.SetAlpha(m_fAlpha);
	m_FadeTexture.Fade(m_fAlpha);

	// �t�F�[�h�C������
	if (m_nFade == FADE_OUT) 
	{
		// ���X�Ƀt�F�[�h
		m_fAlpha += FADE_RATE;
		if (m_fAlpha >= 1.0f) 
		{
			// �t�F�[�h�C�������ɐؑ�
			m_fAlpha = 1.0f;
			m_nFade = FADE_IN;

			// �V�[���ؑ�
			SceneManager::GetInstance().EndFade(m_pNextScene);
		}
		CSound::SetVolume(1.0f - m_fAlpha);
		return;
	}

	// �t�F�[�h�A�E�g����
	m_fAlpha -= FADE_RATE;

	if (m_fAlpha <= 0.0f) 
	{
		// �t�F�[�h�����I��
		m_fAlpha = 0.0f;
		EndFade();
		m_nFade = FADE_NONE;
	}
	CSound::SetVolume(1.0f - m_fAlpha);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void Fade::Draw()
{
	m_FadePolygon.Draw();
	m_FadeTexture.Draw();
}

//=============================================================================
// 
// �t�F�[�h�A�E�g�J�n
// 
//=============================================================================
void Fade::SetFadeOut(Scene* sceneNext)
{
	if (m_nFade != FADE_OUT)
	{
		m_nFade = FADE_OUT;
		m_pNextScene = sceneNext;
	}
}

//=============================================================================
// 
// �t�F�[�h�A�E�g�J�n
// 
//=============================================================================
void Fade::EndFade()
{
	m_pNextScene = nullptr;

}