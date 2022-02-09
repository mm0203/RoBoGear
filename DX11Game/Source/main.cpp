//=============================================================================
// main.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
// Log:
// 
// 2021/10/16　制作開始
// 
// 2021/10/19　DirectXの初期化
// 2021/10/20　レンダーターゲット 深度バッファ ポリゴン作成
//			   ウィンドウ表示まで成功
// 2021/10/22  3D描画対応
// 2021/10/24  入力処理実装
// 2021/10/25  ライティング、カメラ実装
// 2021/10/26  テクスチャ読み込みの生成
// 2021/10/29  メッシュ作成 地面を表示できるように
// 2021/11/06  コリジョン作成(6面の当たり判定)
// 
// 2021/11/14  設計の見直し
//　　　　　   オブジェクトを基底クラスとしたオブジェクト指向に変更
// 2021/11/16  オブジェクトマネージャー作成
//			   オブジェクトの生成方法をテンプレート化に
// 2021/12/10  モデル用のレンダラークラス作成
//			   モデル表示をレンダラークラスから行えるように
// 2021/12/11  レンダラークラスからアニメーションも付加できるようにした
// 2022/01/06  テクスチャ生成を簡易化するためCPolygonクラス作成
// 2022/01/14  状態を管理するためのゲームマネージャ作成
// 2022/01/18  シーンマネージャクラス実装(ステート)
// 2022/01/19  バンプマップ実装
// 2022/01/22  トゥーンシェーダ実装
//			   アウトラインシェーダ実装
// 2022/01/25  環境マップ実装(見栄えないためゲーム組み込み見送り)
// 2022/02/04　Edit機能実装
// 2022/02/07　仮で作成したタイトルやUI等のテクスチャ差し替え完了
//             BGMとSEの実装
// 2022/02/11  仮完成

//	開発履歴
//
//	2020/05/30	DirectX11の初期化
//	2020/05/31	シェーダーの作成、ポリゴンの描画の作成
//	2020/06/01	3D対応
//	2020/06/02	ライティング実装
//	2020/06/04	テクスチャ読み込みの作成
//	2020/06/14	オブジェクトを基底クラスとした
//				オブジェクト指向に変更
//	2020/06/16	入力処理実装
//	2020/06/17	フェードイン・フェードアウトの追加
//	2020/06/24	コリジョンの追加
//	2020/07/01	矩形と円の当たり判定追加
//	2020/07/08	コリジョンクラスの作成
//	2020/07/08	アニメータークラスの作成
//	2020/07/10	アニメーションクラスの作成
//	2020/07/14	フィールドクラスの作成
//	2020/07/15	リジッドボディクラス作成
//	2020/07/16	シーン管理クラス作成
//	2020/07/17	バレットクラス作成
//	2020/07/18	タイトルシーン、ゲームシーンの追加
//	2020/07/24	2D特化のベース作り、Switchとの互換性
//				トランスフォームとスプライトの作成
//	2020/07/31	レイヤー分けをクイックソートに
//	2020/08/01	当たり判定を四分木に
//	2020/08/02	キャラクターアクションクラスの作成
//				ステータスクラスの作成
//	2020/08/03	攻撃ベースクラスの作成
//	2020/08/08	文字列表示クラスの作成
//	2020/08/12	プレイヤーのイラストの実装
//	2020/08/13	プレイヤーの手の動きや遷移の制御
//	2020/08/14	ウェポンクラスの作成
//	2020/08/15	ヒットストップ
//	2020/08/18	エネミースライムの作成
//	2020/08/19	エネミーウィングの作成
//	2020/08/20	エネミーランスの作成
//	2020/08/23	ステージ管理システム
//	2020/08/25	ステージメイカークラスの作成
//	2020/08/26	ランダムステージ生成完成
//	2020/08/29	フロアクラスの作成	
//	2020/08/29	ステージレイアウトの作成	
//	2020/09/02	音を付けた（仮）
//	2020/09/03	ステージのレイアウト完成
//	2020/09/04	ミニマップ
//	2020/09/05	ボス部屋、ボス(仮)、
//	2020/09/05	チュートリアルマップ、スタートマップ、レベルアップテキスト、
//				経験値玉、UI、
//	2020/09/06	デカ羽スライム、弓スライム、ライト、ファイヤー、トゲ、キー
//	2020/09/07	リザルトUIの実装
//	2020/09/08	ボス作り直し、フィールドクラスの作り直し、ムービーUI
//	2020/09/10	操作の変更
//	2020/09/12	バレットのテクスチャを変更
//				完成！！（＼＾＿＾／）
//	2020/10/27	炎エフェクトの変更
//	2020/10/28	コンボの追加(テスト)
//	2020/11/01	コンボ・クリティカルの追加
//	2020/11/29	U22プロコン CSJA賞！！　ありがとうございます！！
//	2020/12/13	公開に向けて少し編集
//
//=============================================================================

#include "main.h"

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
	Singleton<SceneManager>::GetInstance().EndFade(new TitleScene());
	//Singleton<SceneManager>::GetInstance().EndFade(new GameScene());
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
	DrawDebugProc();
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