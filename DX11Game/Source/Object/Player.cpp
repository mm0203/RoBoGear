//=============================================================================
// CPlayer.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "Player.h"
#include <Manager/GameManager.h>
#include <Manager/StageManager.h>
#include <Renderer/Effect/Effect.h>

// システム
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Sound/Sound.h>
#include <System/Helper/XMFLOAT_Helper.h>
#include <time.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CPlayer::CPlayer()
{
	m_tag = "Player";

	// プレイヤーの情報
	m_nCount = 0;
	m_Dir = PlayerDir::eNone;
	m_Model.LoadModel(MODEL_PLAYER);
	m_bMoveCube = false;
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CPlayer::Init()
{
	// 各プレイヤーモデル生成
	m_Caterpillar = ObjectManager::CreateObject<CCaterpillar>();
	m_Gear = ObjectManager::CreateObject<CGear>();
	m_Generare = ObjectManager::CreateObject<CGenerare>();

	// アニメNo初期化
	m_Model.SetAnimeNo((int)PlayerAnime::eNone);
	m_Caterpillar->GetModel().SetAnimeNo((int)CaterpillarAnime::eNone);
	m_Gear->GetModel().SetAnimeNo((int)GearAnime::eNone);
	m_Generare->GetModel().SetAnimeNo((int)GenerareAnime::eNone);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CPlayer::Update()
{
	// 移動
	ObjectMove();

	// 歩数
	int& nStep = CGameManager::GetStep();

	// 状態
	GameState state = CGameManager::GetState();

	switch (state)
	{
	// 動ける
	case GameState::eMove:

		// デバッグモード時は操作不可
		if (!CGameManager::GetDebug())
		{
			m_Dir = PlayerDir::eNone;

			if (GetKeyTrigger(VK_W))// 上
			{
				m_Dir = PlayerDir::eUp;
				m_Rot.y = 180.0f;
			}
			if (GetKeyTrigger(VK_S))// 下
			{
				m_Dir = PlayerDir::eDown;
				m_Rot.y = 0.0f;
			}
			if (GetKeyTrigger(VK_A))// 左
			{
				m_Dir = PlayerDir::eLeft;
				m_Rot.y = 90.0f;
			}
			if (GetKeyTrigger(VK_D))// 右
			{
				m_Dir = PlayerDir::eRight;
				m_Rot.y = -90.0f;
			}
			// 方向が入力されたら移動
			if (m_Dir != PlayerDir::eNone)
			{
				MoveObject(m_Dir, nStep);
			}
		}
		// 歩数0の時にゴールしたらゲームオーバーしない
		if (nStep <= 0 && CGameManager::GetState() != GameState::eClear)
		{
			// BGM停止
			CSound::Stop(GAME);

			// ゲームオーバー音
			CSound::Play(SE_GAMEOVER_BEEP);
			CSound::Play(SE_GAMEOVER_SMOKE);

			CGameManager::SetState(GameState::eGameOver);
		}
		break;
	// クリア
	case GameState::eClear:

		m_Dir = PlayerDir::eNone;
		// プレイヤーズーム
		CCamera::GetInstance().ZoomTarget(m_Pos);

		m_nCount++;
		// クリア１秒後に
		if (m_nCount >= 60)
		{
			// 正面じゃなければ正面に向かせる
			if (m_Rot.y > 0.0f) m_Rot.y -= 2.0f;
			if (m_Rot.y < 0.0f) m_Rot.y += 2.0f;

			// 正面に向いたらアニメーションを変更
			if (m_Rot.y == 0.0f)
			{
				m_Model.SetAnimeNo((int)PlayerAnime::eClear);
			}
		}
		break;
	default:
		break;
	}

	// アニメーション更新
	PlayerAnimetion();

	PrintDebugProc("PosX%d:PosY%d:PosZ%d:\n", (int)m_Pos.x, (int)m_Pos.y, (int)m_Pos.z);
	PrintDebugProc("RotX%d:RotY%d:RotZ%d:\n", (int)m_Rot.x, (int)m_Rot.y, (int)m_Rot.z);
	PrintDebugProc("PlayerX:%d:PlayerY:%d:\n", (int)m_Coord.x, (int)m_Coord.y);
	PrintDebugProc("PlayerAnim:%d\n", (int)m_Model.GetAnimeNo());
}

//=============================================================================
// 
// プレイヤーアニメーション
// 
//=============================================================================
void CPlayer::PlayerAnimetion()
{
	// 移動時のアニメ判定
	if (m_Dir != PlayerDir::eNone)
	{
		m_Caterpillar->GetModel().SetAnimeNo((int)CaterpillarAnime::eMove);
		m_Gear->GetModel().SetAnimeNo((int)GearAnime::eMove);
		m_Generare->GetModel().SetAnimeNo((int)GenerareAnime::eMove);

		// キューブ押しアニメ判定
		if (m_bMoveCube)
		{
			m_Model.SetAnimeNo((int)PlayerAnime::ePush);
			m_bMoveCube = false;
		}
		else
		{
			// 押してないときはアニメなし
			m_Model.SetAnimeNo((int)PlayerAnime::eNone);
		}
		CRenderer::SetAnimeTime(0.0f);
	}
	CRenderer::AnimePlayTime();

	// アニメ切り替え 再生が終わったらアイドル状態に クリア時のアニメはループにしたいので切り替えなし
	if(m_Model.GetAnimeNo() != (int)PlayerAnime::eClear)
		m_Model.AnimeChange((int)PlayerAnime::eNone);

	m_Caterpillar->GetModel().AnimeChange((int)CaterpillarAnime::eNone, 2.0f);
	m_Gear->GetModel().AnimeChange((int)GearAnime::eNone, 2.0f);
	m_Generare->GetModel().AnimeChange((int)GenerareAnime::eNone, 2.0f);
}

//=============================================================================
// 
// オブジェクトの判定 & 移動
// 
//=============================================================================
void CPlayer::MoveObject(PlayerDir& dir, int& step)
{
	// プレイヤーの現在地を取得
	XMINT2 currentPlayerPos = m_Coord;

	// プレイヤーの移動先位置を設定
	XMINT2 nextPlayerPos = GetNextPosition(dir, m_Coord);
	
	// 移動先が壁なら移動できない
	if (ObjectManager::IsObject("Wall",nextPlayerPos) || ObjectManager::IsObject("Gimic", nextPlayerPos))
		// プレイヤーの座標を現在地に戻す
		m_Coord = currentPlayerPos;

	// プレイヤーの移動先にキューブが存在する場合
	else if (ObjectManager::IsObject("Cube", nextPlayerPos))
	{
		// キューブ移動のアニメーション判定
		m_bMoveCube = true;

		// 移動するキューブを取得
		const auto& Cube = ObjectManager::GetObjectAtPosition("Cube", nextPlayerPos);

		// 移動するキューブの位置を取得
		XMINT2 currentCubePos = Cube.lock()->GetCoord();

		// キューブの移動先位置を設定
		XMINT2 nextCubepos = GetNextPosition(dir, Cube.lock()->GetCoord());

		// キューブの移動先にオブジェクトが存在するなら
		if (ObjectManager::IsObject("Wall", nextCubepos)  || ObjectManager::IsObject("Cube", nextCubepos) ||
			ObjectManager::IsObject("Clear", nextCubepos) || ObjectManager::IsObject("Key", nextCubepos) ||
			ObjectManager::IsObject("Gimic", nextCubepos))
		{
			// キューブが移動できない音
			CSound::Play(SE_CUBE_MOVE_NONE);

			// プレイヤーとキューブの位置座標を現在地に戻す
			m_Coord = currentPlayerPos;
			Cube.lock()->SetCoord(currentCubePos);
		}
		// キューブの移動先にオブジェクトが存在しないなら
		else
		{
			// キューブ移動音
			CSound::Play(SE_CUBE_MOVE);

			// プレイヤーとキューブの位置座標を更新
			m_Coord = nextPlayerPos;
			Cube.lock()->SetCoord(nextCubepos);

			// プレイヤーとキューブを移動
			GetNextMove(dir, m_Move);
			GetNextMove(dir, Cube.lock()->GetMove());

			XMFLOAT3 CubePos = Cube.lock()->GetPos();
			GetNextMove(dir, CubePos);
			EffectManager::CreateEffect(Effect_CubeMove, CubePos);

			// プレイヤーの歩数をカウントする
			StepCalc(nextPlayerPos, step);
		}
	}
	// プレイヤーの移動先が鍵だったら
	else if (ObjectManager::IsObject("Key", nextPlayerPos))
	{
		// 鍵取得
		CSound::Play(SE_KEY_GIMIC);

		// プレイヤーの座標を位置を更新
		m_Coord = nextPlayerPos;
		GetNextMove(dir, m_Move);

		// プレイヤーの歩数をカウントする
		StepCalc(nextPlayerPos, step);

		// 位置を取得
		const auto& key = ObjectManager::SearchObjectTag("Key");
		const auto& Gimic = ObjectManager::SearchObjectTag("Gimic");
		XMFLOAT3 keyPos = key.lock()->GetPos();
		XMFLOAT3 GimicPos = Gimic.lock()->GetPos();

		//CCamera::GetInstance().ZoomTarget(GimicPos);

		// エフェクト発生
		EffectManager::CreateEffect(Effect_KeyBreak, keyPos);
		EffectManager::CreateEffect(Effect_GimicBreak, GimicPos);

		// オブジェクトを消去
		ObjectManager::DestroyObject("Key");
		ObjectManager::DestroyObject("Gimic");
	}
	// プレイヤーの移動先にキューブが存在しない場合
	else
	{
		// プレイヤーの座標を更新
		m_Coord = nextPlayerPos;
		GetNextMove(dir, m_Move);

		// プレイヤーの歩数をカウントする
		StepCalc(nextPlayerPos, step);

		// プレイヤーとクリアの座標が一致したら
		if (ObjectManager::IsObject("Clear", nextPlayerPos))
		{
			CSound::Play(SE_CLEAR);
			CGameManager::SetState(GameState::eClear);
		}
	}

	// 移動音
	//CSound::SetVolume(1.5f);
	CSound::Play(SE_PLAYER_MOVE);

	// 移動時のエフェクト
	if (m_Coord == nextPlayerPos)
	{
		EffectManager::CreateEffect(Effect_PlayerMove, m_Pos);
	}
}

//=============================================================================
// 
// 移動による座標更新
// 
//=============================================================================
XMINT2 CPlayer::GetNextPosition(PlayerDir dir, XMINT2 Coord)
{
	switch (dir)
	{
		// 上
	case(PlayerDir::eUp):
		Coord.y -= 1;
		break;
		// 下
	case(PlayerDir::eDown):
		Coord.y += 1;
		break;
		// 左
	case(PlayerDir::eLeft):
		Coord.x -= 1;
		break;
		// 右
	case(PlayerDir::eRight):
		Coord.x += 1;
		break;
	default:
		break;
	}
	return Coord;
}

//=============================================================================
// 
// オブジェクトを移動させる
// 
//=============================================================================
void CPlayer::GetNextMove(PlayerDir dir, XMFLOAT3& move)
{
	// 移動量
	constexpr float MoveObject = 10.0f;

	switch (dir)
	{
		// 上
	case(PlayerDir::eUp):
		move.z += MoveObject;
		break;
		// 下
	case(PlayerDir::eDown):
		move.z -= MoveObject;
		break;
		// 左
	case(PlayerDir::eLeft):
		move.x -= MoveObject;
		break;
		// 右
	case(PlayerDir::eRight):
		move.x += MoveObject;
		break;
	default:
		break;
	}
}
//=============================================================================
// 
// プレイヤーの移動で歩数カウントを減らす
// 
//=============================================================================
void CPlayer::StepCalc(XMINT2 pos, int& step)
{
	// 移動先にトゲがあるなら
	if (ObjectManager::IsObject("Trap", pos))
	{
		// トラップ効果音
		CSound::Play(SE_TRAP);
		step -= 2;
	}
	// 移動先にトゲがないなら
	else
		step--;
}
