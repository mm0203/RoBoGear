//=============================================================================
// Effect.h
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
	Effect_GimicBreak,	  // ギミック破壊時
	Effect_KeyBreak,	  // 鍵を取った
	Effect_PlayerMove,	  // プレイヤー移動
	Effect_CubeMove,	  // キューブ移動
	Effect_Trap,		  // ダメージ床
	Effect_RevivalObject, // 巻き戻しでオブジェクト復活
	Effect_MAX
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CEffect : public CBillBoard
{
	friend class CEffectManager; // フレンドクラス
public:
	CEffect() = default;
	~CEffect() = default;

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
	// フレーム数
	XMINT2 m_FrameNum;
	// エフェクトアニメの最大数
	int m_MaxAnimNum;
	// 現在のアニメ数
	int m_CurrentAnimNum;
	// アニメ再生スピード
	int m_Speed;
	// アニメの再生カウント
	int m_SpeedCount;
};

// エフェクトマネージャークラス
class CEffectManager : public CSprite
{
public:
	CEffectManager() = default;
	~CEffectManager() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

	// エフェクト生成
	static void CreateEffect(EffectID ID, XMFLOAT3 pos);
	// エフェクト削除
	static void DeleteObject(CEffect*);
	// エフェクトリスト取得
	std::vector<CEffect*> GetActiveList() { return m_ActiveList; }

private:
	// エフェクト追加
	static void AddObject(CEffect);
	// エフェクトオブジェクト生成
	static void CreateObject(int num = 10);
	static void UpdateObject();

private:
	static std::vector<CEffect*> m_UnusedList;	// 未使用リスト
	static std::vector<CEffect*> m_ActiveList;	// 使うエフェクト
	static std::vector<CEffect*> m_DeleteList;  // 削除するエフェクト
};