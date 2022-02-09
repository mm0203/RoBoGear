//=============================================================================
// Fade.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once
#include "FadeTexture.h"
#include <Manager/SceneManager.h>
#include <System/Singleton/singleton.h>
#include <Renderer/Polygon/CPolygon.h>


//=============================================================================
// 
// ��`
// 
//=============================================================================
enum EFade	// �t�F�[�h���
{
	FADE_NONE = 0,	// �������Ă��Ȃ�
	FADE_IN,		// �t�F�[�h�C������
	FADE_OUT,		// �t�F�[�h�A�E�g����

	MAX_FADE
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class Scene;	// �O���錾

class Fade : public Singleton<Fade>
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetFadeOut(Scene* sceneNext);
	void EndFade();

private:
	// �V���O���g���݂̂ŃC���X�^���X����������
	friend class Singleton;
	Fade();
	~Fade() = default;

	float m_fAlpha;		 // �s�����x
	int m_nFade;		 // �t�F�[�h���
	Scene* m_pNextScene; // �ǂݍ��ރV�[��
	int m_FadeCount;
	int m_nTexNo;

	CPolygon m_FadePolygon;
	CFadeTexture m_FadeTexture;
};
