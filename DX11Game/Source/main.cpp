//=============================================================================
// main.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
// Log:
// 
// 2021/10/16　制作開始
// 2021/10/19　DirectXの初期化
// 2021/10/20　レンダーターゲット 深度バッファ ポリゴン作成
//             ウィンドウ表示まで成功
// 2021/10/22  3D描画対応
// 2021/10/24  入力処理実装
// 2021/10/25  ライティング、カメラ実装
// 2021/10/26  テクスチャ読み込みの生成
// 2021/10/28  デバックメッセージ生成
// 2021/10/29  メッシュ作成 地面を表示できるように
// 2021/11/06  コリジョン作成(6面の当たり判定)
// 2021/11/14  オブジェクトを基底クラスとしたオブジェクト指向に変更
// 2021/11/16  オブジェクトマネージャー作成
//             オブジェクトの生成方法をテンプレート化に
// 2021/11/20  各オブジェクトのクラス生成(プレイヤー　キューブ　クリア　ギミック　ウォール　トラップ　キー)
// 2022/11/24  シーンマネージャクラス生成
// 2021/11/25  ゲームシーン実装
// 2021/11/28  ステージマネージャー生成
// 2021/11/30  ステージ読み込みと書き込みをCSVに
// 2021/11/31  シングルトンクラス実装
// 2021/12/04  モデル用のレンダラークラス作成
//               モデル表示をレンダラークラスから行えるように
// 2021/12/08  レンダラークラスからアニメーションも付加できるようにした
// 2021/12/11  テクスチャ生成を簡易化するためCPolygonクラス作成
//            　 テクスチャ基底クラス作成
// 2021/12/13  テクスチャのコンポーネント作成
// 2021/12/16  ビルボード実装
// 2021/12/18  スプライトマネージャー実装
// 2021/12/23  エフェクトクラス及びエフェクトマネージャー生成
// 2021/12/24  状態を管理するためのゲームマネージャ作成
// 2021/12/26  ポーズ実装
// 2021/12/28  ゲームクリア　ゲームオーバー実装
// 2022/01/01  タイトルシーン実装
// 2022/01/04  ステージセレクトシーン実装
// 2022/01/06  チュートリアル実装
// 2022/01/14  バンプマップ実装
// 2022/01/19  トゥーンシェーダ実装
//               アウトラインシェーダ実装
// 2022/01/23  環境マップ実装(地面に対して)
// 2022/01/28　Edit機能実装開始
// 2022/01/30  メッセージ表示機能実装
// 2022/02/06  Edit機能完成
// 2022/02/07　仮で作成したタイトルやUI等のテクスチャ差し替え完了
//             BGMとSEの実装
// 2020/02/10  デバッグモード実装(フリーカメラ　シェーダー切り替え)
// 2022/02/11  仮完成
//
//=============================================================================

#include <main.h>

// システム
#include <System/Singleton/singleton.h>
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Sound/Sound.h>
#include <System/Fade/fade.h>
#include <System/Camera/Camera.h>
#include <System/Light/Light.h>

// レンダー
#include <Renderer/Assimp/AssimpModel.h>
#include <Renderer/Graphics/Graphics.h>
#include <Renderer/Shader/Script/ShaderList.h>
#include <Renderer/Mesh/mesh.h>
#include <Renderer/Polygon/polygon.h>

// シーン
#include <Manager/SceneManager.h>
#include <Scene/Title/TitleScene.h>
#include <Scene/Game/GameScene.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Edit/EditScene.h>

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;
	// DirectX初期化
	InitDX(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	// 初期化
	Singleton<Graphics>::GetInstance().Init();
	// ポリゴン表示初期化
	InitPolygon(GetDevice());
	// 入力処理初期化
	InitInput();
	// デバッグ文字列表示初期化
	InitDebugProc();
	// シェーダリスト初期化
	InitShaderResource();
	// メッシュ初期化
	CMesh::Init();
	// ステージ情報初期化
	StageManager::Init();
	// ライト
	Singleton<CLight>::GetInstance().Init();
	// フェード初期化
	Singleton<Fade>::GetInstance().Init();

	// タイトルシーン設定 -> タイトルシーン初期化
	//Singleton<SceneManager>::GetInstance().EndFade(new TitleScene());
	Singleton<SceneManager>::GetInstance().EndFade(new GameScene());
	//Singleton<SceneManager>::GetInstance().EndFade(new StageSelectScene());
	//Singleton<SceneManager>::GetInstance().EndFade(new EditScene());

	SceneManager::GetInstance().ChangeNextScene();
	// サウンドの初期化
	CSound::Init();

	return hr;
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void Uninit()
{
	// サウンドの終了処理
	CSound::Fin();
	// シーンの終了処理
	Singleton<SceneManager>::GetInstance().Uninit();
	// フェード終了処理
	Singleton<Fade>::GetInstance().Uninit();
	// メッシュ終了処理
	CMesh::Uninit();
	// シェーダリスト解放
	UninitShaderResource();
	// デバッグ文字列表示終了処理
	UninitDebugProc();
	// 入力処理終了処理
	UninitInput();
	// ポリゴン表示終了処理
	UninitPolygon();
	// DirectX解放
	Singleton<Graphics>::GetInstance().Uninit();
	// シングルトンリスト解放
	SingletonFinalizer::finalize();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void Update()
{
	// 入力処理更新
	UpdateInput();
	// デバッグ文字列表示更新
	UpdateDebugProc();
	// デバッグ文字列設定
	StartDebugProc();
	//PrintDebugProc("FPS:%d\n\n", g_nCountFPS);
	// ポリゴン表示更新
	UpdatePolygon();
	// カメラ更新
	Singleton<CCamera>::GetInstance().Update();
	// ライト更新
	Singleton<CLight>::GetInstance().Update();
	// シーン更新
	Singleton<SceneManager>::GetInstance().Update();
	// フェード更新
	Singleton<Fade>::GetInstance().Update();
	// サウンド更新
	CSound::Update();
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void Draw()
{
	// レンダーターゲット&深度バッファ クリア
	Singleton<Graphics>::GetInstance().BeginDraw();
	// アルファブレンド無効
	SetBlendState(BS_NONE);
	// シーン描画
	Singleton<SceneManager>::GetInstance().Draw();

	// デバッグ文字列表示
#ifdef _DEBUG
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	//DrawDebugProc();
#endif

	// 深度バッファ
	Singleton<Graphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_ON);
	// アルファブレンド有効
	SetBlendState(BS_ALPHABLEND);
	// フェード描画
	Singleton<Fade>::GetInstance().Draw();
	// バックバッファとフロントバッファの入れ替え
	Singleton<Graphics>::GetInstance().EndDraw();
}