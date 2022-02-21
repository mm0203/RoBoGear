//=============================================================================
// StageManager.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "StageManager.h"
#include <Manager/GameManager.h>

// オブジェクト
#include <Object/Player.h>
#include <Object/Wall.h>
#include <Object/Cube.h>
#include <Object/Clear.h>
#include <Object/Gimic.h>
#include <Object/Trap.h>
#include <Object/key.h>
#include <Object/StageGround.h>

// シーン
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Edit/Editor.h>

// ファイル読み込み
#include <iostream>
#include <fstream>
#include <sstream>

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
std::tuple<int, std::string, int> StageManager::m_StageInfo[] = {};

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	// 中央が(0,0)なのでマップの左端上からオブジェクトを配置する
	constexpr float StartPosWidth = 500.0f;
	constexpr float StartPosHeight = 400.0f;
}

//=============================================================================
// 
// 初期化
// 
//=============================================================================
void StageManager::Init()
{
	// ステージ番号初期化
	for (int i = 0; i < eStage_10 + 1; i++)
	{
		std::get<eStageNumber>(m_StageInfo[i]) = i;
	}

	//ステージファイル名格納
	std::get<eStageName>(m_StageInfo[eStage_1]) = "data/map/stage1.csv";
	std::get<eStageName>(m_StageInfo[eStage_2]) = "data/map/stage2.csv";
	std::get<eStageName>(m_StageInfo[eStage_3]) = "data/map/stage3.csv";
	std::get<eStageName>(m_StageInfo[eStage_4]) = "data/map/stage4.csv";
	std::get<eStageName>(m_StageInfo[eStage_5]) = "data/map/stage5.csv";
	std::get<eStageName>(m_StageInfo[eStage_6]) = "data/map/stage6.csv";
	std::get<eStageName>(m_StageInfo[eStage_7]) = "data/map/stage7.csv";
	std::get<eStageName>(m_StageInfo[eStage_8]) = "data/map/stage8.csv";
	std::get<eStageName>(m_StageInfo[eStage_9]) = "data/map/stage9.csv";
	std::get<eStageName>(m_StageInfo[eStage_10]) = "data/map/stage10.csv";

	// 各ステージの歩数格納
	std::get<eStageStep>(m_StageInfo[eStage_1])  = 22;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_2])  = 25;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_3])  = 24;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_4])  = 20;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_5])  = 20;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_6])  = 30;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_7])  = 23;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_8])  = 12;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_9])  = 17;	// 〇
	std::get<eStageStep>(m_StageInfo[eStage_10]) = 24;	// 〇
}

//=============================================================================
// 
// ステージ読み込み
// 
//=============================================================================
std::string StageManager::LoadStage()
{
	// ステージ番号取得
	int StageNumber = CGameManager::GetStageMenu();

	for (int i = 0; i < eStage_10 + 1; i++)
	{
		// 一致するステージ番号があったら
		if (StageNumber == std::get<eStageNumber>(m_StageInfo[i]))
		{
			// 歩数をセット
			int& step = CGameManager::GetStep();
			step = std::get<eStageStep>(m_StageInfo[i]);

			// ステージファイル名を取得
			return std::get<eStageName>(m_StageInfo[i]);
		}
	}
	return "\0";
}

//=============================================================================
// 
// ステージ生成
// 
//=============================================================================
void  StageManager::StageCreate(std::string& fileName)
{
	// マップ格納用変数
	std::vector<std::vector<int>> nMap;

	// CSV読み込み
	ReadCSV(fileName, nMap);

	// マップチップ番号
	int nChipId = 0;
	// 行列番号
	XMINT2 hw = XMINT2(0, 0);

	// ステージのサイズ分だけ回す
	for (auto& height : nMap)
	{
		// 行番号の初期化
		hw.x = 0;

		for (auto& CurrentMapChip : height)
		{
			// マップチップ番号取得
			nChipId = CurrentMapChip;

			// 現在の座標を保存
			XMINT2 Coord = { hw.x, hw.y};
			hw.x++;

			// 何もなかったら
			if (nChipId == eObject_None)	continue;

			// 位置
			XMFLOAT3 ObjectPos = { MapChipSize * Coord.x - StartPosWidth, 0.0f,  StartPosHeight - MapChipSize * Coord.y };

			// オブジェクト生成
			switch (nChipId)
			{
				// 壁	
			case(eObject_Wall): // 1
				ObjectManager::CreateObject<CWall>(ObjectPos, Coord);
				break;
				// キューブ
			case(eObject_Cube): // 2
				ObjectManager::CreateObject<CCube>(ObjectPos, Coord);
				break;
				// 鍵
			case(eObject_Key):	 // 3
				// TODO キーのモデルサイズが合わないため...
				XMFLOAT3 sizeKey = { 2.0f, 2.0f, 2.0f };
				ObjectManager::CreateObject<CKey>(ObjectPos, Coord, sizeKey);
				break;
				// ギミック
			case(eObject_Gimic): // 4
				ObjectManager::CreateObject<CGimic>(ObjectPos, Coord);
				break;
				// プレイヤー
			case(eObject_Player): // 5
				ObjectManager::CreateObject<CPlayer>(ObjectPos, Coord);
				break;
				// トラップ
			case(eObject_Trap): // 6
				ObjectManager::CreateObject<CTrap>(ObjectPos, Coord);
				break;
				// ゴール
			case(eObject_Clear): // 7
				ObjectManager::CreateObject<CClear>(ObjectPos, Coord);
				break;
			}
		}
		// 列番号の追加
		hw.y++;
	}
}

//=============================================================================
// 
// CSV読み込み
// 
//=============================================================================
void  StageManager::ReadCSV(std::string& fileName,std::vector<std::vector<int>>& map)
{
	// ファイル読み込み
	std::ifstream csv(fileName);

	// csvから1列分を読み込む
	for (std::string str; std::getline(csv, str);)
	{
		// 列を追加
		map.emplace_back(std::vector<int>());

		// 読み込んだ列を１文字ずつ格納できるように
		for (std::stringstream ss(str); std::getline(ss, str, ',');)
		{
			// 文字をint型に変換
			map[map.size() - 1].emplace_back(std::stoi(str.c_str()));
		}
	}
}