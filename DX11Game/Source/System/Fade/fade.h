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
enum FadeMode
{
	eFadeNone = 0, // �������Ă��Ȃ�
	eFadeIn,	   // �t�F�[�h�C������
	eFadeOut,	   // �t�F�[�h�A�E�g����
	MAX_FADE
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CScene;	// �O���錾

class CFade : public CSingleton<CFade>
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetFadeOut(CScene* sceneNext);
	void EndFade();

private:
	// �V���O���g���݂̂ŃC���X�^���X����������
	friend class CSingleton;
	CFade();
	~CFade() = default;

	// �s�����x
	float m_fAlpha;
	// �t�F�[�h���
	int m_nFade;
	// �ǂݍ��ރV�[��
	CScene* m_pNextScene; 
	// �t�F�[�h�|���S��
	CPolygon m_FadePolygon;
	// �t�F�[�h���̃e�N�X�`��
	CFadeTexture m_FadeTexture;
};
