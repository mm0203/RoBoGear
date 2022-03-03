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
	Scene_None = 0,
	Scene_Title,
	Scene_StageSelect,
	Scene_Game,
	Scene_Edit,
	Scene_Max
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
// �V�[���N���X
class Scene
{
protected:
	//SceneManager& _controller;

public:
	Scene(){}
	virtual ~Scene(){}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

// �V�[���}�l�[�W���[
class SceneManager : public Singleton<SceneManager>
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
	const void SetNextScene(Scene* Next);
	// �t�F�[�h�̏I�����`�F�b�N
	const void EndFade(Scene* Next);
	// �V�[���J��
	const bool ChangeNextScene();

private:
	// �V���O���g���݂̂ŃC���X�^���X����������
	friend class Singleton;
	SceneManager();
	~SceneManager() = default;

	// ���݂̃V�[��
	std::unique_ptr<Scene> m_pCurrentScene;
	// ���ɓǂݍ��ރV�[��
	std::unique_ptr<Scene> m_pNextScene;
	// �t�F�[�h�����ǂ���
	bool m_bDoSceneChange;
	// ���݂̃V�[�����
	Current_Scene m_SceneNo;
};