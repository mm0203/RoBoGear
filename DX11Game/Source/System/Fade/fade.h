//=============================================================================
// Fade.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once
#include "FadeTexture.h"
#include <Manager/SceneManager.h>
#include <System/Singleton/singleton.h>
#include <Renderer/Polygon/CPolygon.h>


//=============================================================================
// 
// 定義
// 
//=============================================================================
enum EFade	// フェード状態
{
	FADE_NONE = 0,	// 何もしていない
	FADE_IN,		// フェードイン処理
	FADE_OUT,		// フェードアウト処理

	MAX_FADE
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class Scene;	// 前方宣言

class Fade : public Singleton<Fade>
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetFadeOut(Scene* sceneNext);
	void EndFade();

private:
	// シングルトンのみでインスタンス生成を許可
	friend class Singleton;
	Fade();
	~Fade() = default;

	float m_fAlpha;		 // 不透明度
	int m_nFade;		 // フェード状態
	Scene* m_pNextScene; // 読み込むシーン
	CPolygon m_FadePolygon;
	CFadeTexture m_FadeTexture; // フェード中のテクスチャ
};
