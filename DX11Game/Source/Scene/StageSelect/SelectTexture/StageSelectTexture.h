//=============================================================================
// StageSelectTexture.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "StageSelectBackGround.h"
#include "StageSelectLogo.h"
#include "StageSelectCursor.h"
#include "StageSelectLevel.h"
#include <list>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CStageSelectTexture
{
public:
	CStageSelectTexture();
	~CStageSelectTexture() = default;

	void Init();
	void Uninit();
	void Update(int index);
	void Draw();

private:
	// �w�i
	std::shared_ptr<CStageSelectBackGround> m_StageSelectBackGround;
	// �X�e�[�W�Z���N�g���S
	std::shared_ptr<CStageSelectLogo> m_StageSelectLogo;
	// �e�X�e�[�W�ԍ�
	std::shared_ptr<CStageSelectLevel> m_StageSelectLevel;
	// �J�[�\��(�g��)
	std::shared_ptr<CStageSelectCursor> m_StageSelectCursor;
private:
	std::list<tex_shared> m_pStageSelectTextures;
};