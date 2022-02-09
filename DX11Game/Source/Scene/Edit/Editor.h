//=============================================================================
// CEditor.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/ObjectManager.h>
#include <Manager/StageManager.h>
#include <Renderer/Polygon/CPolygon.h>
#include <Component/Transform.h>
#include <Component/DrawNumber.h>
#include "Cursor.h"
#include "ModeSelect.h"
#include "EditOperationUI.h"

#include <memory>
#include <string>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	constexpr int HeightMax = 8;
	constexpr int WidthMax = 11;

}

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CEditor
{
public:
	CEditor();
	~CEditor() = default;

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// マップ初期化
	void MapInitialize();
	// ステージセレクト
	void MenuIndexChange(int& index, int min, int max);
	// オブジェクト生成
	void Create();
	// 削除
	void Delete();
	// オブジェクト変更
	void ChangeObject();
	// オブジェクト移動
	void Move();
	// ステップ設定
	void SetStep();
	// ステージ保存
	void SaveStage();
	// ステージ読み込み
	void LoadStage();
	// タイトル
	void LoadTitle();
	// ゲームスタート
	void LoadGame();
	// ステージ番号更新
	void StageNumberUpdate();
private:

	enum EditMode
	{
		eMode_Create,
		eMode_Delete,
		eMode_Step,
		eMode_Save,
		eMode_Load,
		eMode_Title,
		eMode_Game,
		eMode_Max
	};
private:

	std::unique_ptr<CRenderer> m_pModel; // 表示用モデル
	CTransform m_Trans;	// モデル情報
	CModeSelect m_ModeSelect; // モード選択
	CNumber m_Number;	// ステップやナンバー表示
	CCursor m_ModelCursor; // カーソルモデル
	CEditOperationUI m_pEditOperationUI; // UI表示

	int m_nCurrentStage; // ステージ番号
	int m_nStepCount;	 // 歩数
	int m_nCurrentMode;	// 現在のモード
	bool m_bDisp;		// 点滅用判定
	int m_type;		//オブジェクトの種類
	int m_nMap[HeightMax][WidthMax];	// ステージ編集用変数
	int m_nChipsize;	// マップチップサイズ
};