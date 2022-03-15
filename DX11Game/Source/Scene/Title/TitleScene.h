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
	eTitle_Start,	// �Q�[���J�n
	eTitle_Edit,	// �G�f�B�b�g���[�h��
	eTitle_Exit,	// �Q�[���I��
	eTitle_Max
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CTitleScene : public CScene
{
public:
	CTitleScene();
	~CTitleScene() = default;

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

