//=============================================================================
// TimeLeap.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TimeLeap.h"

// マネージャー
#include <Manager/ObjectManager.h>
#include <Manager/GameManager.h>

// オブジェクト
#include <Object/Player.h>
#include <Object/Trap.h>

//=============================================================================
// 
// スタック解放
// 
//=============================================================================
void CTimeLeap::ReleaseStack()
{
	// スタックが空になるまで要素を削除
	while (!m_CoordStack.empty()) 
	{
		m_CoordStack.pop();
	}
	while (!m_DirStack.empty())
	{
		m_DirStack.pop();
	}
	while (!m_RoationStack.empty())
	{
		m_RoationStack.pop();
	}
}

//=============================================================================
// 
// オブジェクト巻き戻し
// 
//=============================================================================
void CTimeLeap::RewindObject(std::string tag)
{
	// 現在の場所を取得
	XMINT2 CurrentCoord = m_CoordStack.top();

	// 前回移動した方向を取得
	ObjectDir dir = m_DirStack.top();

	// 座標から戻すオブジェクトを取得
	const auto& obj = CObjectManager::GetObjectAtPosition(tag, CurrentCoord);

	// 戻すオブジェクトがなかったら
	if (obj.expired())
	{
		// 前回の移動方向と場所を削除
		m_CoordStack.pop();
		m_DirStack.pop();
		return;
	}
	// 戻すオブジェクトが存在しているなら
	else if (!obj.expired())
	{
		// オブジェクトの座標と移動量を取得
		XMINT2 Coord = obj.lock()->GetCoord();
		XMFLOAT3& Move = obj.lock()->GetMove();

		// 前回の移動方向を基準に場所を戻す
		switch (dir)
		{
			// 前回の行動が上なら下に
		case(ObjectDir::eUp):
			Move.z -= MovementObject;
			Coord.y++;
			break;
			// 前回の行動が下なら上に
		case(ObjectDir::eDown):
			Move.z += MovementObject;
			Coord.y--;
			break;
			// 前回の行動が左なら右に
		case(ObjectDir::eLeft):
			Move.x += MovementObject;
			Coord.x++;
			break;
			// 前回の行動が右なら左に
		case(ObjectDir::eRight):
			Move.x -= MovementObject;
			Coord.x--;
			break;
		default:
			break;
		}
		// オブジェクトの座標を更新
		obj.lock()->SetCoord(Coord);
	}

	// 前回の移動方向と場所を削除
	m_CoordStack.pop();
	m_DirStack.pop();

	// 歩数を増やす
	if (tag == TagPlayer)
	IsStepCheck(TagTrap, CurrentCoord);
}

//=============================================================================
// 
// 削除したオブジェクトを戻す
// 
//=============================================================================
void CTimeLeap::RevivalObject(std::string tag)
{
	// 現在の場所を取得
	XMINT2 CurrentCoord = m_CoordStack.top();

	// 座標から戻すオブジェクトを取得
	const auto& obj = CObjectManager::GetUnusedObjectAtPosition(tag, CurrentCoord);

	// 戻すオブジェクトがなかったら
	if (obj.expired())
	{
		// 前回の場所を削除
		m_CoordStack.pop();
		return;
	}
	// 戻すオブジェクトが存在しているなら
	else if (!obj.expired())
	{
		CObjectManager::UnusedToActive(tag);
	}

	// 前回の場所を削除
	m_CoordStack.pop();
}

//=============================================================================
// 
// オブジェクトの向きを戻す
// 
//=============================================================================
void CTimeLeap::RewindRoationObject(std::string tag)
{
	// 現在の場所を取得
	XMINT2 CurrentCoord = m_CoordStack.top();

	// 現在の向きを取得
	XMFLOAT3 CurrentRot = m_RoationStack.top();

	// 座標から戻すオブジェクトを取得
	const auto& obj = CObjectManager::GetObjectAtPosition(tag, CurrentCoord);

	// 向きを更新
	obj.lock()->SetRot(CurrentRot);

	// 前回の向きを削除
	m_RoationStack.pop();
}

//=============================================================================
// 
// プレイヤーが踏んだ場所を確認
// 
//=============================================================================
void CTimeLeap::IsStepCheck(std::string tag, XMINT2& coord)
{
	int& nStep = CGameManager::GetStep();

	// 前の場所にトラップがあるなら
	if (CObjectManager::IsObject(tag, coord))
	{
		nStep += 2;
	}
	// 前の場所にトラップがないなら
	else
	{
		nStep++;
	}
}
