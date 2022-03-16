//=============================================================================
// CPlayer.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/Object.h>
#include <Manager/ObjectManager.h>
#include "Caterpillar.h"
#include "Gear.h"
#include "Generare.h"
#include <Scene/Game/TimeLeap/TimeLeap.h>

#include <stack>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================
// モデル
#define MODEL_PLAYER "data/model/Object/MainAnim_Blender/Main_Re_Blender.fbx"
// タグ名
const std::string TagPlayer = "Player";

// プレイヤーアニメ
enum class PlayerAnime
{
	ePush = 0,		// キューブ押した
	eSmallPush,		// 使ってない
	eClear,			// クリア時のアニメ
	eNone,			// 待機
	ePlayerAnimeMax
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer() = default;

	void Init()	  override;
	void Update() override;

private:
	// アニメ
	void PlayerAnimetion();
	// オブジェクト移動
	void MoveObject(ObjectDir& dir, int& step);
	// 次の移動座標
	XMINT2 GetNextPosition(ObjectDir dir, XMINT2 Coord);
	// 次の移動場所
	void GetNextMove(ObjectDir dir, XMFLOAT3& move);
	// 歩数計算
	void StepCalc(XMINT2 pos, int& step);



private:
	// 秒数
	int m_nCount;
	// 移動方向
	ObjectDir m_Dir;
	// キューブ押しアニメ判定
	bool m_bMoveCube;
	// 各モデルパーツのオブジェクト
	obj_shared m_Caterpillar;
	obj_shared m_Gear;
	obj_shared m_Generare;
};