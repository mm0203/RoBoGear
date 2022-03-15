//=============================================================================
// Editor.h
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
	// マップの最大サイズ
	const int HeightMax = 8;
	const int WidthMax = 11;

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

	// 表示用モデル
	std::unique_ptr<CRenderer> m_pModel;
	// モデル情報
	CTransform m_Trans;
	// モード選択
	CModeSelect m_ModeSelect;
	// ステップやナンバー表示
	CNumber m_Number;
	// カーソルモデル
	CCursor m_ModelCursor;
	// UI表示
	CEditOperationUI m_pEditOperationUI;

	// ステージ番号
	int m_nCurrentStage;
	// 歩数
	int m_nStepCount;
	// 現在のモード
	int m_nCurrentMode;
	// 点滅用判定
	bool m_bDisp;
	//オブジェクトの種類
	int m_type;
	// ステージ編集用変数
	int m_nMap[HeightMax][WidthMax];
	// マップチップサイズ
	int m_nChipsize;
};