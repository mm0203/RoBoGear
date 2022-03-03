//=============================================================================
// TitleScene.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/SceneManager.h>
#include <Renderer/Polygon/CPolygon.h>
#include <Scene/Title/TitleTexture/TitleTexture.h>
#include <vector>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================
enum TitleMenu
{
	eTitle_Start,
	eTitle_Edit,
	eTitle_Exit,
	eTitle_Max
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

private:
	// �^�C�g���Ɏg���e�N�X�`��
	CTitleTexture m_TitleTexture;
	// ���j���[�ԍ�
	int m_nMenuIndex;
	// ��������
	bool m_bButton;
};

