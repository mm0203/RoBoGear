//=============================================================================
// SceneManager.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <main.h>
#include <System/Fade/fade.h>
#include <System/Singleton/singleton.h>
#include <memory>

//=============================================================================
// 
// マクロ定義
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
// クラス定義
// 
//=============================================================================
// シーンクラス
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

// シーンマネージャー
class SceneManager : public Singleton<SceneManager>
{
public:
	// getter
	int GetSceneNo() { return m_SceneNo; }

	// setter
	void SetSceneNo(Current_Scene sceneNo) { m_SceneNo = sceneNo; }

	//各シーンの処理を呼ぶ
	const void Init();
	const void Uninit();
	const void Update();
	const void Draw();

	// 次のシーンを設定
	const void SetNextScene(Scene* Next);
	// フェードの終了をチェック
	const void EndFade(Scene* Next);
	// シーン遷移
	const bool ChangeNextScene();

private:
	// シングルトンのみでインスタンス生成を許可
	friend class Singleton;
	SceneManager();
	~SceneManager() = default;

	// 現在のシーン
	std::unique_ptr<Scene> m_pCurrentScene;
	// 次に読み込むシーン
	std::unique_ptr<Scene> m_pNextScene;
	// フェード中かどうか
	bool m_bDoSceneChange;
	// 現在のシーン状態
	Current_Scene m_SceneNo;
};