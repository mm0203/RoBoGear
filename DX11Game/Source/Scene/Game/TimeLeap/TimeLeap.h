//=============================================================================
// TimeLeap.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once
#include <main.h>
#include <Manager/Object.h>
#include <string>
#include <stack>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CTimeLeap
{
public:
	CTimeLeap() = default;
	~CTimeLeap() = default;

	// スタック解放
	void ReleaseStack();
	// オブジェクト巻き戻し
	void RewindObject(std::string tag);
	// 削除したオブジェクトを戻す
	void RevivalObject(std::string tag);
	// オブジェクトの向きを戻す
	void RewindRoationObject(std::string tag);
	// プレイヤーの歩数更新
	void IsStepCheck(std::string tag, XMINT2& coord);

	// スタック追加
	void AddCoordStack(XMINT2& coord)
	{
		m_CoordStack.push(coord);
	}
	void AddDirStackAdd(ObjectDir& dir)
	{
		m_DirStack.push(dir);
	}
	void AddRoationStackAdd(XMFLOAT3& rot)
	{
		m_RoationStack.push(rot);
	}

	// getter
	std::stack<XMINT2> GetCoordStack() { return m_CoordStack; }
	// setter
	std::stack<ObjectDir> GetDirStack() { return m_DirStack; }

private:
	// 巻き戻し用の座標スタック
	std::stack<XMINT2> m_CoordStack;
	// 巻き戻し用の移動方向スタック
	std::stack<ObjectDir> m_DirStack;
	// 巻き戻し用の向きスタック
	std::stack<XMFLOAT3> m_RoationStack;
};