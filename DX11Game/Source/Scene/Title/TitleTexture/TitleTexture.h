//=============================================================================
// CTitleTexture.h
//=============================================================================
// Author  ���� ���V
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
// �N���X��`
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
	// �w�i
	std::shared_ptr<CTitleBackGround> m_TitleBackGround;
	// �^�C�g���V�[���̎��ԉ摜
	std::shared_ptr<CTitleFrame> m_TitleFrame;
	// �J�[�\��
	std::shared_ptr<CTitleMenuChoices> m_TitleMenuChoices;
	// �^�C�g�����S
	std::shared_ptr<CTitleLogo> m_TitleLogo;

private:
	std::list<tex_shared> m_pTitleTextures;
};