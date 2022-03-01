//=============================================================================
// CEditor.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Editor.h"

// オブジェクト
#include <Object/Player.h>
#include <Object/Caterpillar.h>
#include <Object/Gear.h>
#include <Object/Generare.h>
#include <Object/Wall.h>
#include <Object/Cube.h>
#include <Object/Clear.h>
#include <Object/Gimic.h>
#include <Object/Trap.h>
#include <Object/key.h>
#include <Object/StageGround.h>

// マネージャー
#include <Manager/StageManager.h>

// シーン
#include <Scene/Game/GameScene.h>
#include <Scene/Title/TitleScene.h>
#include <Scene/StageSelect/StageSelectScene.h>

// システム
#include <System/Input/input.h>
#include <System/Message/Message.h>
#include <System/Debug/debugproc.h>
#include <System/Singleton/singleton.h>
#include <System/Sound/Sound.h>

// ファイル読み込み
#include <iostream>
#include <fstream>
#include <sstream>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	// マップ中央値
	constexpr XMINT2 CenterCoord = XMINT2(5, 4);
	// 選択できるモード数
	constexpr int ModeNum = 7;
	// ステージの数
	int nStagemin = 1;
	int nStagemax = 10;
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CEditor::CEditor()
{
	m_pModel = std::make_unique<CRenderer>();
	m_nStepCount = 30;
	m_nCurrentStage = 0;
	m_nCurrentMode = eMode_Create;
	m_bDisp = false;
	m_type = eObject_Wall;
}

//=============================================================================
// 
// マップ初期化
// 
//=============================================================================
void CEditor::MapInitialize()
{
	for (int y = 0; y < HeightMax; y++)
	{
		for (int x = 0; x < WidthMax; x++)
		{
			m_nMap[y][x] = eObject_None;
		}
	}
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CEditor::Init()
{
	// マップ初期化
	MapInitialize();
	// マップチップサイズ
	m_nChipsize = MapChipSize;
	// メッセージ初期化
	MessageManager::Init();
	// モードセレクト初期化
	m_nCurrentMode = eMode_Create;
	m_ModeSelect.Init();
	// ナンバー初期化
	m_Number.Init();
	// モデルカーソル初期化
	m_ModelCursor.Init();
	// 操作説明
	m_pEditOperationUI.Init();
	// オブジェクト情報初期化
	m_Trans.SetCoord(CenterCoord);	// 初期値を中央に(左上が0,0)
	m_Trans.SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CEditor::Uninit()
{
	m_pModel->ReleaseModelAll();
	MessageManager::Uninit();
	m_Number.Uninit();
	m_ModelCursor.Uninit();
	m_ModeSelect.Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CEditor::Update()
{
	// モード変更
	switch (m_nCurrentMode)
	{
		// 生成
	case EditMode::eMode_Create:
		Move();
		ChangeObject();
		Create();
		break;
		// 削除
	case EditMode::eMode_Delete:
		Move();
		Delete();
		break;
		// 歩数設定
	case EditMode::eMode_Step:
		SetStep();
		break;
		// ステージセーブ
	case EditMode::eMode_Save:
		SaveStage();
		break;
		// ステージ読み込み
	case EditMode::eMode_Load:
		LoadStage();
		break;
		// タイトル
	case EditMode::eMode_Title:
		LoadTitle();
		break;
		// ゲーム開始
	case EditMode::eMode_Game:
		LoadGame();
		break;
	default:
		break;
	}

	// モード変更
	m_ModeSelect.Update(m_nCurrentMode, ModeNum);
	// ナンバー更新
	m_Number.Update();
	// モデルカーソル更新
	m_ModelCursor.Update(m_Trans.GetPos(), m_Trans.GetScale(), m_Trans.GetRot());

	// オブジェクト点滅
	static int nCount = 0;
	nCount++;
	if (nCount < Second / 4) m_bDisp = true;
	if (nCount > Second / 4) m_bDisp = false;
	if (nCount > Second / 2) nCount = 0;

	PrintDebugProc("PosX%d:PosY%d:PosZ%d:\n", (int)m_Trans.GetPos().x, (int)m_Trans.GetPos().y, (int)m_Trans.GetPos().z);
	PrintDebugProc("ObjectType:%d\n", m_type);
	PrintDebugProc("StageNo:%d\n", m_nCurrentStage);
	PrintDebugProc("Step:%d\n", m_nStepCount);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CEditor::Draw()
{
	// オブジェクト描画
	if (m_bDisp && m_nCurrentMode == eMode_Create)
		m_pModel->Draw(m_Trans.GetPos(), m_Trans.GetScale(), m_Trans.GetRot());

	// カーソルモデル描画
	if (m_nCurrentMode == eMode_Create || (m_nCurrentMode == eMode_Delete))
		m_ModelCursor.Draw();

	// モードセレクトカーソル描画
	m_ModeSelect.Draw();

	// 歩数描画
	XMFLOAT2 pos = XMFLOAT2(565.0f, -150.0f);
	m_Number.Draw(m_nStepCount, pos);
	// ステージNo描画
	XMFLOAT2 Stagepos = XMFLOAT2(565.0f, -300.0f);
	m_Number.Draw(m_nCurrentStage + 1, Stagepos);
	// 操作説明描画
	m_pEditOperationUI.Draw();
	// メッセージ描画
	MessageManager::Draw();
}

//=============================================================================
// 
// 選択肢変更
// 
//=============================================================================
void CEditor::MenuIndexChange(int& index, int min, int max)
{

	if (GetKeyTrigger(VK_Q) || GetKeyTrigger(VK_LEFT))
	{
		// 移動とか歩数の音
		CSound::Play(SE_EDIT_CREATE_CURSOR);
		index--;
	}
	if (GetKeyTrigger(VK_E) || GetKeyTrigger(VK_RIGHT))
	{
		// 移動とか歩数の音
		CSound::Play(SE_EDIT_CREATE_CURSOR);
		index++;
	}

	// 最小値を下回ったら最大値に
	if (index < min)
		index += max;
	// 最大値を上回ったら最小値に
	if (index >= max)
		index -= max;
}

//=============================================================================
// 
// オブジェクト生成
// 
//=============================================================================
void CEditor::Create()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		// オブジェクトが既にあったら生成できない
		if (m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] != eObject_None)
		{
			// オブジェクト作れない
			CSound::Play(SE_CUBE_MOVE_NONE);
			return;
		}

		// オブジェクト生成
		CSound::Play(SE_EDIT_CREATE);

		switch (m_type)
		{
		case eObject_Wall:
			ObjectManager::CreateObject<CWall>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Cube:
			ObjectManager::CreateObject<CCube>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Key:
			ObjectManager::CreateObject<CKey>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Gimic:
			ObjectManager::CreateObject<CGimic>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Player:
			ObjectManager::CreateObject<CPlayer>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Trap:
			ObjectManager::CreateObject<CTrap>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		case eObject_Clear:
			ObjectManager::CreateObject<CClear>(m_Trans.GetPos(), m_Trans.GetCoord(), m_Trans.GetScale());
			break;
		default:
			break;
		}
		// オブジェクトの位置を保存
		m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] = m_type;
	}

}
//=============================================================================
// 
// オブジェクト削除
// 
//=============================================================================
void CEditor::Delete()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		// オブジェクトがなければ何もしない
		if (m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] == eObject_None)
		{
			// オブジェクト消せない
			CSound::Play(SE_CUBE_MOVE_NONE);
			return;
		}

		// オブジェクト削除
		CSound::Play(SE_EDIT_DELTE);

		// 位置からオブジェクト情報を取得
		int ObjectType = m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x];

		std::string Tag;
		switch (ObjectType)
		{
		case eObject_Wall:
			Tag = "Wall";
			break;
		case eObject_Cube:
			Tag = "Cube";
			break;
		case eObject_Key:
			Tag = "Key";
			break;
		case eObject_Gimic:
			Tag = "Gimic";
			break;
		case eObject_Player:
			Tag = "Player";
			break;
		case eObject_Trap:
			Tag = "Trap";
			break;
		case eObject_Clear:
			Tag = "Clear";
			break;
		default:
			break;
		}
		// オブジェクト削除
		ObjectManager::DestroyEditObject(Tag, m_Trans.GetCoord());

		//for (auto it = m_pObj.begin(); it != m_pObj.end();)
		//{
		//	if (ObjectManager::DestroyEditObject(it->get()->GetTag(), m_Trans.GetCoord()))
		//	{
		//		it->reset();
		//		it = m_pObj.erase(it);

		//		// 削除した場所を更新
		//		m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] = eObject_None;
		//		return;
		//	}
		//	else ++it;
		//}

		// 削除した場所を更新
		m_nMap[m_Trans.GetCoord().y][m_Trans.GetCoord().x] = eObject_None;
	}
}

//=============================================================================
// 
// オブジェクト生成
// 
//=============================================================================
void CEditor::ChangeObject()
{
	// オブジェクト変更
	if (GetKeyTrigger(VK_Q) || GetKeyTrigger(VK_LEFT))
	{
		// 移動とか歩数の音
		CSound::Play(SE_EDIT_CREATE_CURSOR);

		m_type--;
	}
	if (GetKeyTrigger(VK_E) || GetKeyTrigger(VK_RIGHT))
	{
		// 移動とか歩数の音
		CSound::Play(SE_EDIT_CREATE_CURSOR);

		m_type++;
	}
	if (m_type < eObject_None + 1)
		m_type += eObject_Max -1;

	if (m_type > eObject_Max - 1)
		m_type -= eObject_Max - 1;

	// オブジェクトの見た目変更
	switch (m_type)
	{
	case eObject_Wall:

		m_pModel->LoadModel(MODEL_WALL);
		break;
	case eObject_Cube:
		m_pModel->LoadModel(MODEL_CUBE);
		break;
	case eObject_Key:
		m_pModel->LoadModel(MODEL_KEY);
		break;
	case eObject_Gimic:
		m_pModel->LoadModel(MODEL_GIMIC);
		break;
	case eObject_Player:
		m_pModel->LoadModel(MODEL_PLAYER);
		break;
	case eObject_Trap:
		m_pModel->LoadModel(MODEL_TRAP);
		break;
	case eObject_Clear:
		m_pModel->LoadModel(MODEL_CLEAR);
		break;
	default:
		break;
	}
}

//=============================================================================
// 
// オブジェクト生成
// 
//=============================================================================
void CEditor::Move()
{
	//カーソル位置移動
	static XMFLOAT3 pos = XMFLOAT3();
	static XMINT2 coord = CenterCoord;

	XMFLOAT3 oldpos = pos;
	XMINT2 oldcoord = coord;

	if (GetKeyTrigger(VK_W))// 上
	{
		CSound::Play(SE_EDIT_ARROW);
		pos.z += m_nChipsize;
		coord.y -= m_nChipsize / MapChipSize;
	}
	if (GetKeyTrigger(VK_S))// 下
	{
		CSound::Play(SE_EDIT_ARROW);
		pos.z -= m_nChipsize;
		coord.y += m_nChipsize / MapChipSize;
	}
	if (GetKeyTrigger(VK_A))// 左
	{
		CSound::Play(SE_EDIT_ARROW);
		pos.x -= m_nChipsize;
		coord.x -= m_nChipsize / MapChipSize;
	}
	if (GetKeyTrigger(VK_D))// 右
	{
		CSound::Play(SE_EDIT_ARROW);
		pos.x += m_nChipsize;
		coord.x += m_nChipsize / MapChipSize;
	}
	
	// マップ範囲チェック
	if (coord.x < 0 || coord.x >= WidthMax || coord.y < 0 || coord.y >= HeightMax)
	{
		pos = oldpos;
		coord = oldcoord;
	}
	
	// 移動したカーソルをセット
	m_Trans.SetPos(pos);
	m_Trans.SetCoord(coord);
}

//=============================================================================
// 
// 歩数設定
// 
//=============================================================================
void CEditor::SetStep()
{
	int nStepmin = 2;
	int nStepmax = 99;

	MenuIndexChange(m_nStepCount, nStepmin, nStepmax);
}

//=============================================================================
// 
// セーブ
// 
//=============================================================================
void CEditor::SaveStage()
{
	// 選択肢変更
	MenuIndexChange(m_nCurrentStage, nStagemin, nStagemax);

	if (GetKeyTrigger(VK_RETURN))
	{
		CSound::Play(SE_EIDT_SAVE);

		// ステージ番号更新
		StageNumberUpdate();

		// ステージ読み込み
		std::string StageFile = StageManager::LoadStage();

		//ファイルの出力
		std::ofstream ofs(StageFile);

		for (int i = 0; i < HeightMax; i++)
		{
			for (int j = 0; j < WidthMax; j++)
			{
				ofs << (int)m_nMap[i][j] << ",";
			}
			// 改行
			ofs << std::endl;
		}
		ofs.close();

		// 歩数更新
		auto& Info = StageManager::GetStageInfo(m_nCurrentStage);
		std::get<eStageStep>(Info) = m_nStepCount;
	}
}

//=============================================================================
// 
// ロード
// 
//=============================================================================
void CEditor::LoadStage()
{
	// 選択肢変更
	MenuIndexChange(m_nCurrentStage, nStagemin, nStagemax);

	if (GetKeyTrigger(VK_RETURN))
	{
		CSound::Play(SE_EIDT_LOAD);

		// マップ初期化
		MapInitialize();

		//現在生成されているオブジェクトを消去
		ObjectManager::UninitAll();

		// ステージ番号更新
		StageNumberUpdate();

		std::string StageFile = StageManager::LoadStage();

		// ステージ格納用変数
		std::vector<std::vector<int>> nMap;

		// CSV読み込み
		StageManager::ReadCSV(StageFile, nMap);

		// ステージ生成
		StageManager::StageCreate(StageFile);

		// エディット用変数に格納
		for (int y = 0; y < HeightMax; y++)
		{
			for (int x = 0; x < WidthMax; x++)
			{
				m_nMap[y][x] = nMap[y][x];
			}
		}
		// 歩数初期値読み込み
		auto& Info = StageManager::GetStageInfo(m_nCurrentStage);
		m_nStepCount = std::get<eStageStep>(Info);
	}
}
//=============================================================================
// 
// タイトル読み込み
// 
//=============================================================================
void CEditor::LoadTitle()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		CSound::Play(SE_CHOISE);
		Singleton<SceneManager>::GetInstance().SetNextScene(new TitleScene());
	}
}


//=============================================================================
// 
// ゲーム読み込み
// 
//=============================================================================
void CEditor::LoadGame()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		CSound::Play(SE_CHOISE);

		// ステージ番号更新
		StageNumberUpdate();

		Singleton<SceneManager>::GetInstance().SetNextScene(new GameScene());
	}
}

//=============================================================================
// 
// ステージ番号更新
// 
//=============================================================================
void CEditor::StageNumberUpdate()
{
	int& nMenuIndex = CGameManager::GetStageMenu();
	nMenuIndex = m_nCurrentStage;
}
