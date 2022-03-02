//=============================================================================
// main.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
// Log:
// 
// 2021/10/16�@����J�n
// 2021/10/19�@DirectX�̏�����
// 2021/10/20�@�����_�[�^�[�Q�b�g �[�x�o�b�t�@ �|���S���쐬
//             �E�B���h�E�\���܂Ő���
// 2021/10/22  3D�`��Ή�
// 2021/10/24  ���͏�������
// 2021/10/25  ���C�e�B���O�A�J��������
// 2021/10/26  �e�N�X�`���ǂݍ��݂̐���
// 2021/10/28  �f�o�b�N���b�Z�[�W����
// 2021/10/29  ���b�V���쐬 �n�ʂ�\���ł���悤��
// 2021/11/06  �R���W�����쐬(6�ʂ̓����蔻��)
// 2021/11/14  �I�u�W�F�N�g�����N���X�Ƃ����I�u�W�F�N�g�w���ɕύX
// 2021/11/16  �I�u�W�F�N�g�}�l�[�W���[�쐬
//             �I�u�W�F�N�g�̐������@���e���v���[�g����
// 2021/11/20  �e�I�u�W�F�N�g�̃N���X����(�v���C���[�@�L���[�u�@�N���A�@�M�~�b�N�@�E�H�[���@�g���b�v�@�L�[)
// 2022/11/24  �V�[���}�l�[�W���N���X����
// 2021/11/25  �Q�[���V�[������
// 2021/11/28  �X�e�[�W�}�l�[�W���[����
// 2021/11/30  �X�e�[�W�ǂݍ��݂Ə������݂�CSV��
// 2021/11/31  �V���O���g���N���X����
// 2021/12/04  ���f���p�̃����_���[�N���X�쐬
//             ���f���\���������_���[�N���X����s����悤��
// 2021/12/08  �����_���[�N���X����A�j���[�V�������t���ł���悤�ɂ���
// 2021/12/11  �e�N�X�`���������ȈՉ����邽��CPolygon�N���X�쐬
//             �e�N�X�`�����N���X�쐬
// 2021/12/13  �e�N�X�`���̃R���|�[�l���g�쐬
// 2021/12/16  �r���{�[�h����
// 2021/12/18  �X�v���C�g�}�l�[�W���[����
// 2021/12/23  �G�t�F�N�g�N���X�y�уG�t�F�N�g�}�l�[�W���[����
// 2021/12/24  ��Ԃ��Ǘ����邽�߂̃Q�[���}�l�[�W���쐬
// 2021/12/26  �|�[�Y����
// 2021/12/28  �Q�[���N���A�@�Q�[���I�[�o�[����
// 2022/01/01  �^�C�g���V�[������
// 2022/01/04  �X�e�[�W�Z���N�g�V�[������
// 2022/01/06  �`���[�g���A������
// 2022/01/14  �o���v�}�b�v����
// 2022/01/19  �g�D�[���V�F�[�_����
//             �A�E�g���C���V�F�[�_����
// 2022/01/23  ���}�b�v����(�n�ʂɑ΂���)
// 2022/01/28�@Edit�@�\�����J�n
// 2022/01/30  ���b�Z�[�W�\���@�\����
// 2022/02/06  Edit�@�\����
// 2022/02/07�@���ō쐬�����^�C�g����UI���̃e�N�X�`�������ւ�����
//             BGM��SE�̎���
// 2020/02/10  �f�o�b�O���[�h����(�t���[�J�����@�V�F�[�_�[�؂�ւ�)
// 2022/02/11  ������
// 2022/02/15  ����
// 2022/03/02  �ꕔ���f���A�e�N�X�`�������ւ�
//
//=============================================================================

#include <main.h>
#include <Manager/GameManager.h>

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
	InitPolygon();
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
	if (CGameManager::GetDebug())
	{
		SetPolygonColor(1.0f, 1.0f, 1.0f);
		DrawDebugProc();
	}
	// �[�x�o�b�t�@
	Singleton<Graphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_ON);
	// �A���t�@�u�����h�L��
	SetBlendState(BS_ALPHABLEND);
	// �t�F�[�h�`��
	Singleton<Fade>::GetInstance().Draw();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	Singleton<Graphics>::GetInstance().EndDraw();
}