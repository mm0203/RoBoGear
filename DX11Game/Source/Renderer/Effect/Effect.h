//=============================================================================
// Ceffect.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <main.h>
#include <Manager/Sprite.h>
#include <Renderer/Billboard/BillBorad.h>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================
enum EffectID
{
	Effect_GimicBreak,
	Effect_KeyBreak,
	Effect_PlayerMove,
	Effect_CubeMove,
	Effect_Trap,
	Effect_MAX
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class Effect : public BillBoard
{
	friend class EffectManager;
public:
	Effect() = default;
	~Effect() = default;

	// setter 
	void SetFrameNum(XMINT2 frame) { m_FrameNum = frame; }
	void SetFrameNum(int u, int v) { m_FrameNum = XMINT2(u, v); }
	void SetMaxAnimNum(int max) { m_MaxAnimNum = max; }
	void SetSpeed(int spd) { m_Speed = spd; }

	void Init();
	void Update();
	void Uninit();
	void Draw();

private:
	XMINT2 m_FrameNum;		//フレーム数
	int m_MaxAnimNum;
	int m_CurrentAnimNum;
	int m_Speed;
	int m_SpeedCount;
};

class EffectManager : public Sprite
{
public:
	EffectManager() = default;
	~EffectManager() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

	static void CreateEffect(EffectID ID, XMFLOAT3 pos);
	static void DeleteObject(Effect*);
	std::vector<Effect*> GetActiveList() { return m_ActiveList; }

private:
	static void AddObject(Effect);
	static void CreateObject(int num = 10);
	static void UpdateObject();

private:
	static std::vector<Effect*> m_UnusedList;
	static std::vector<Effect*> m_ActiveList;
	static std::vector<Effect*> m_DeleteList;
};