//=============================================================================
// main.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
// Log:
// 
// 2021/10/16�@����J�n
// 
// 2021/10/19�@DirectX�̏�����
// 2021/10/20�@�����_�[�^�[�Q�b�g �[�x�o�b�t�@ �|���S���쐬
//			   �E�B���h�E�\���܂Ő���
// 2021/10/22  3D�`��Ή�
// 2021/10/24  ���͏�������
// 2021/10/25  ���C�e�B���O�A�J��������
// 2021/10/26  �e�N�X�`���ǂݍ��݂̐���
// 2021/10/29  ���b�V���쐬 �n�ʂ�\���ł���悤��
// 2021/11/06  �R���W�����쐬(6�ʂ̓����蔻��)
// 
// 2021/11/14  �݌v�̌�����
//�@�@�@�@�@   �I�u�W�F�N�g�����N���X�Ƃ����I�u�W�F�N�g�w���ɕύX
// 2021/11/16  �I�u�W�F�N�g�}�l�[�W���[�쐬
//			   �I�u�W�F�N�g�̐������@���e���v���[�g����
// 2021/12/10  ���f���p�̃����_���[�N���X�쐬
//			   ���f���\���������_���[�N���X����s����悤��
// 2021/12/11  �����_���[�N���X����A�j���[�V�������t���ł���悤�ɂ���
// 2022/01/06  �e�N�X�`���������ȈՉ����邽��CPolygon�N���X�쐬
// 2022/01/14  ��Ԃ��Ǘ����邽�߂̃Q�[���}�l�[�W���쐬
// 2022/01/18  �V�[���}�l�[�W���N���X����(�X�e�[�g)
// 2022/01/19  �o���v�}�b�v����
// 2022/01/22  �g�D�[���V�F�[�_����
//			   �A�E�g���C���V�F�[�_����
// 2022/01/25  ���}�b�v����(���h���Ȃ����߃Q�[���g�ݍ��݌�����)
// 2022/02/04�@Edit�@�\����
// 2022/02/07�@���ō쐬�����^�C�g����UI���̃e�N�X�`�������ւ�����
//             BGM��SE�̎���
// 2022/02/11  ������

//	�J������
//
//	2020/05/30	DirectX11�̏�����
//	2020/05/31	�V�F�[�_�[�̍쐬�A�|���S���̕`��̍쐬
//	2020/06/01	3D�Ή�
//	2020/06/02	���C�e�B���O����
//	2020/06/04	�e�N�X�`���ǂݍ��݂̍쐬
//	2020/06/14	�I�u�W�F�N�g�����N���X�Ƃ���
//				�I�u�W�F�N�g�w���ɕύX
//	2020/06/16	���͏�������
//	2020/06/17	�t�F�[�h�C���E�t�F�[�h�A�E�g�̒ǉ�
//	2020/06/24	�R���W�����̒ǉ�
//	2020/07/01	��`�Ɖ~�̓����蔻��ǉ�
//	2020/07/08	�R���W�����N���X�̍쐬
//	2020/07/08	�A�j���[�^�[�N���X�̍쐬
//	2020/07/10	�A�j���[�V�����N���X�̍쐬
//	2020/07/14	�t�B�[���h�N���X�̍쐬
//	2020/07/15	���W�b�h�{�f�B�N���X�쐬
//	2020/07/16	�V�[���Ǘ��N���X�쐬
//	2020/07/17	�o���b�g�N���X�쐬
//	2020/07/18	�^�C�g���V�[���A�Q�[���V�[���̒ǉ�
//	2020/07/24	2D�����̃x�[�X���ASwitch�Ƃ̌݊���
//				�g�����X�t�H�[���ƃX�v���C�g�̍쐬
//	2020/07/31	���C���[�������N�C�b�N�\�[�g��
//	2020/08/01	�����蔻����l���؂�
//	2020/08/02	�L�����N�^�[�A�N�V�����N���X�̍쐬
//				�X�e�[�^�X�N���X�̍쐬
//	2020/08/03	�U���x�[�X�N���X�̍쐬
//	2020/08/08	������\���N���X�̍쐬
//	2020/08/12	�v���C���[�̃C���X�g�̎���
//	2020/08/13	�v���C���[�̎�̓�����J�ڂ̐���
//	2020/08/14	�E�F�|���N���X�̍쐬
//	2020/08/15	�q�b�g�X�g�b�v
//	2020/08/18	�G�l�~�[�X���C���̍쐬
//	2020/08/19	�G�l�~�[�E�B���O�̍쐬
//	2020/08/20	�G�l�~�[�����X�̍쐬
//	2020/08/23	�X�e�[�W�Ǘ��V�X�e��
//	2020/08/25	�X�e�[�W���C�J�[�N���X�̍쐬
//	2020/08/26	�����_���X�e�[�W��������
//	2020/08/29	�t���A�N���X�̍쐬	
//	2020/08/29	�X�e�[�W���C�A�E�g�̍쐬	
//	2020/09/02	����t�����i���j
//	2020/09/03	�X�e�[�W�̃��C�A�E�g����
//	2020/09/04	�~�j�}�b�v
//	2020/09/05	�{�X�����A�{�X(��)�A
//	2020/09/05	�`���[�g���A���}�b�v�A�X�^�[�g�}�b�v�A���x���A�b�v�e�L�X�g�A
//				�o���l�ʁAUI�A
//	2020/09/06	�f�J�H�X���C���A�|�X���C���A���C�g�A�t�@�C���[�A�g�Q�A�L�[
//	2020/09/07	���U���gUI�̎���
//	2020/09/08	�{�X��蒼���A�t�B�[���h�N���X�̍�蒼���A���[�r�[UI
//	2020/09/10	����̕ύX
//	2020/09/12	�o���b�g�̃e�N�X�`����ύX
//				�����I�I�i�_�O�Q�O�^�j
//	2020/10/27	���G�t�F�N�g�̕ύX
//	2020/10/28	�R���{�̒ǉ�(�e�X�g)
//	2020/11/01	�R���{�E�N���e�B�J���̒ǉ�
//	2020/11/29	U22�v���R�� CSJA�܁I�I�@���肪�Ƃ��������܂��I�I
//	2020/12/13	���J�Ɍ����ď����ҏW
//
//=============================================================================

#include "main.h"

// �V�X�e��
#include <System/Singleton/singleton.h>
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Sound/Sound.h>
#include <System/Fade/fade.h>
#include <System/Camera/Camera.h>
#include <System/Light/Light.h>

// �����_�[
#include <Renderer/Assimp/AssimpModel.h>
#include <Renderer/Graphics/Graphics.h>
#include <Renderer/Shader/Script/ShaderList.h>
#include <Renderer/Mesh/mesh.h>
#include <Renderer/Polygon/polygon.h>

// �V�[��
#include <Manager/SceneManager.h>
#include <Scene/Title/TitleScene.h>
#include <Scene/Game/GameScene.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Edit/EditScene.h>

//=============================================================================
// 
// ����������
// 
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;
	// DirectX������
	InitDX(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	// ������
	Singleton<Graphics>::GetInstance().Init();
	// �|���S���\��������
	InitPolygon(GetDevice());
	// ���͏���������
	InitInput();
	// �f�o�b�O������\��������
	InitDebugProc();
	// �V�F�[�_���X�g������
	InitShaderResource();
	// ���b�V��������
	CMesh::Init();
	// �X�e�[�W��񏉊���
	StageManager::Init();
	// ���C�g
	Singleton<CLight>::GetInstance().Init();
	// �t�F�[�h������
	Singleton<Fade>::GetInstance().Init();

	// �^�C�g���V�[���ݒ� -> �^�C�g���V�[��������
	Singleton<SceneManager>::GetInstance().EndFade(new TitleScene());
	//Singleton<SceneManager>::GetInstance().EndFade(new GameScene());
	//Singleton<SceneManager>::GetInstance().EndFade(new StageSelectScene());
	//Singleton<SceneManager>::GetInstance().EndFade(new EditScene());

	SceneManager::GetInstance().ChangeNextScene();
	// �T�E���h�̏�����
	CSound::Init();

	return hr;
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void Uninit()
{
	// �T�E���h�̏I������
	CSound::Fin();
	// �V�[���̏I������
	Singleton<SceneManager>::GetInstance().Uninit();
	// �t�F�[�h�I������
	Singleton<Fade>::GetInstance().Uninit();
	// ���b�V���I������
	CMesh::Uninit();
	// �V�F�[�_���X�g���
	UninitShaderResource();
	// �f�o�b�O������\���I������
	UninitDebugProc();
	// ���͏����I������
	UninitInput();
	// �|���S���\���I������
	UninitPolygon();
	// DirectX���
	Singleton<Graphics>::GetInstance().Uninit();
	// �V���O���g�����X�g���
	SingletonFinalizer::finalize();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void Update()
{
	// ���͏����X�V
	UpdateInput();
	// �f�o�b�O������\���X�V
	UpdateDebugProc();
	// �f�o�b�O������ݒ�
	StartDebugProc();
	//PrintDebugProc("FPS:%d\n\n", g_nCountFPS);
	// �|���S���\���X�V
	UpdatePolygon();
	// �J�����X�V
	Singleton<CCamera>::GetInstance().Update();
	// ���C�g�X�V
	Singleton<CLight>::GetInstance().Update();
	// �V�[���X�V
	Singleton<SceneManager>::GetInstance().Update();
	// �t�F�[�h�X�V
	Singleton<Fade>::GetInstance().Update();
	// �T�E���h�X�V
	CSound::Update();
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void Draw()
{
	// �����_�[�^�[�Q�b�g&�[�x�o�b�t�@ �N���A
	Singleton<Graphics>::GetInstance().BeginDraw();
	// �A���t�@�u�����h����
	SetBlendState(BS_NONE);
	// �V�[���`��
	Singleton<SceneManager>::GetInstance().Draw();

	// �f�o�b�O������\��
#ifdef _DEBUG
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	DrawDebugProc();
#endif

	// �[�x�o�b�t�@
	Singleton<Graphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_ON);
	// �A���t�@�u�����h�L��
	SetBlendState(BS_ALPHABLEND);
	// �t�F�[�h�`��
	Singleton<Fade>::GetInstance().Draw();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	Singleton<Graphics>::GetInstance().EndDraw();
}