//=============================================================================
// StageManager.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <main.h>
#include <string>
#include <vector>
#include <tuple>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================

// 1マスのサイズ
const auto MapChipSize = 100;

// 各オブジェクト
enum MapObject
{
	eObject_None = 0,
	eObject_Wall,
	eObject_Cube,
	eObject_Key,
	eObject_Gimic,
	eObject_Player,
	eObject_Trap,
	eObject_Clear,
	eObject_Max
};

// ステージ番号
enum  SelectStage
{
	eStage_1 = 0,
	eStage_2,
	eStage_3,
	eStage_4,
	eStage_5,
	eStage_6,
	eStage_7,
	eStage_8,
	eStage_9,
	eStage_10,
	eTitleBack,
	Max_Stage
};

// ステージタプルの情報
enum StageInfo
{
	eStageNumber,	// ステージ番号
	eStageName,		// ステージファイル名
	eStageStep,		// 各ステージの歩数
	eStageInfo
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CStageManager
{

public:
	CStageManager() = default;
	~CStageManager() = default;

	static std::tuple<int, std::string, int>& GetStageInfo(int index) { return m_StageInfo[index]; }

	static void Init();
	// ステージ情報読み込み
	static std::string LoadStage();
	// ステージ生成
	static void StageCreate(std::string& fileName);
	// CSVファイル読み込み
	static void ReadCSV(std::string& fileName, std::vector<std::vector<int>>& map);

private:
	// ステージの各情報
	// 1.ステージ番号
	// 2.ステージファイル名
	// 3.ステージの歩数
	static std::tuple<int, std::string, int> m_StageInfo[eStage_10 + 1];
};