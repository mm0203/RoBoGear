//=============================================================================
// GameScene.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/SceneManager.h>
#include <Manager/GameManager.h>
#include <memory>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene() = default;

	void Init()    override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;

	// �e�X�v���C�g�̃C���X�^���X�����֐�
	void CreateSpriteInstance();

private:
	GameState m_State;
};