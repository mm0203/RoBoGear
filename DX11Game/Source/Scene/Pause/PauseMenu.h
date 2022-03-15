//=============================================================================
// PauseMenu.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Sprite.h>
#include <Scene/Pause/PauseTexture/PauseMenuTexture.h>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================
enum PauseMenu
{
	ePause_Continue,	// ������
	ePause_Retry,		// �͂��߂���
	ePause_StageSelect,	// �X�e�[�W�Z���N�g
	ePause_Title,		// �^�C�g��
	ePauseMenuMax
};
//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CPauseMenu : public CSprite
{
public:
	CPauseMenu();
	~CPauseMenu() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	CPauseMenuTexture m_PuaseMenuTexture;
	// �|�[�Y�̑I����
	int m_nMenuIndex;
};

