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
enum FadeMode
{
	eFadeNone = 0, // 何もしていない
	eFadeIn,	   // フェードイン処理
	eFadeOut,	   // フェードアウト処理
	MAX_FADE
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CScene;	// 前方宣言

class CFade : public CSingleton<CFade>
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetFadeOut(CScene* sceneNext);
	void EndFade();

private:
	// シングルトンのみでインスタンス生成を許可
	friend class CSingleton;
	CFade();
	~CFade() = default;

	// 不透明度
	float m_fAlpha;
	// フェード状態
	int m_nFade;
	// 読み込むシーン
	CScene* m_pNextScene; 
	// フェードポリゴン
	CPolygon m_FadePolygon;
	// フェード中のテクスチャ
	CFadeTexture m_FadeTexture;
};
