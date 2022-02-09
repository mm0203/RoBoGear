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

constexpr auto MapChipSize = 100; // 1マスのサイズ

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

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class StageManager
{

public:
	StageManager() = default;
	~StageManager() = default;

	static std::tuple<int, std::string, int>& GetStageInfo(int index) { return m_StageInfo[index]; }

	static void Init();
	// ステージ情報読み込み
	static std::string LoadStage();
	// ステージ生成
	static void StageCreate(std::string& fileName);
	// CSVファイル読み込み
	static void ReadCSV(std::string& fileName, std::vector<std::vector<int>>& map);
	
private:
	enum StageInfo
	{
		eStageNumber,
		eStageName,
		eStageStep,
		eStageInfo
	};

private:
	// ステージの各情報
	// 1.ステージ番号
	// 2.ステージファイル名
	// 3.ステージの歩数
	static std::tuple<int, std::string, int> m_StageInfo[eStage_10 + 1];
};