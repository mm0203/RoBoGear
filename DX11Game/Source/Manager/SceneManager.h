//=============================================================================
// SceneManager.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <main.h>
#include <System/Fade/fade.h>
#include <System/Singleton/singleton.h>
#include <memory>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================
enum Current_Scene
{
	eSceneNone = 0,
	eSceneTitle,
	eSceneStageSelect,
	eSceneGame,
	eSceneEdit,
	eSceneMax
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
// �V�[���N���X
class CScene
{
protected:
	//CSceneManager& _controller;

public:
	CScene(){}
	virtual ~CScene(){}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

// �V�[���}�l�[�W���[
class CSceneManager : public CSingleton<CSceneManager>
{
public:
	// getter
	int GetSceneNo() { return m_SceneNo; }

	// setter
	void SetSceneNo(Current_Scene sceneNo) { m_SceneNo = sceneNo; }

	//�e�V�[���̏������Ă�
	const void Init();
	const void Uninit();
	const void Update();
	const void Draw();

	// ���̃V�[����ݒ�
	const void SetNextScene(CScene* Next);
	// �t�F�[�h�̏I�����`�F�b�N
	const void EndFade(CScene* Next);
	// �V�[���J��
	const bool ChangeNextScene();

private:
	// �V���O���g���݂̂ŃC���X�^���X����������
	friend class CSingleton;
	CSceneManager();
	~CSceneManager() = default;

	// ���݂̃V�[��
	std::unique_ptr<CScene> m_pCurrentScene;
	// ���ɓǂݍ��ރV�[��
	std::unique_ptr<CScene> m_pNextScene;
	// �t�F�[�h�����ǂ���
	bool m_bDoSceneChange;
	// ���݂̃V�[�����
	Current_Scene m_SceneNo;
};