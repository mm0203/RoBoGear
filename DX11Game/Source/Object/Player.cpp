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
#include <System/Camera/Camera.h>
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Sound/Sound.h>
#include <System/Helper/XMFLOAT_Helper.h>
#include <time.h>

// オブジェクト
#include <Object/Cube.h>
#include <Object/Gimic.h>
#include <Object/Key.h>
#include <Object/Wall.h>
#include <Object/Trap.h>
#include <Object/Clear.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	// モデルが向いている方向
	const float DirRoationFront = 0.0f;		// 正面
	const float DirRoationBack  = 180.0f;	// 背面
	const float DirRoationLeft  = 90.0f;	// 左
	const float DirRoationRight = -90.0f;	// 右

	const float AnimeSpeed = 2.0f;	// アニメ再生速度
	const float RotateSpeed = 2.0f; // クリア時のプレイヤー回転速度
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CPlayer::CPlayer()
{
	// プレイヤーの情報
	m_tag = TagPlayer;
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
	m_Caterpillar = CObjectManager::CreateObject<CCaterpillar>();
	m_Gear = CObjectManager::CreateObject<CGear>();
	m_Generare = CObjectManager::CreateObject<CGenerare>();

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

	// 歩数取得
	int& nStep = CGameManager::GetStep();

	// 状態取得
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
				m_Rot.y = DirRoationBack;
			}
			if (GetKeyTrigger(VK_S))// 下
			{
				m_Dir = PlayerDir::eDown;
				m_Rot.y = DirRoationFront;
			}
			if (GetKeyTrigger(VK_A))// 左
			{
				m_Dir = PlayerDir::eLeft;
				m_Rot.y = DirRoationLeft;
			}
			if (GetKeyTrigger(VK_D))// 右
			{
				m_Dir = PlayerDir::eRight;
				m_Rot.y = DirRoationRight;
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

		// プレイヤーにズーム
		CCamera::GetInstance().ZoomTarget(m_Pos);

		m_nCount++;

		// 正面を向いてないかつ1秒経過したら
		if (m_Rot.y >= DirRoationFront && m_nCount >= Second * 1)
		{
			// 正面向くまで回転させる
			m_Rot.y -= RotateSpeed;
		}
		// 正面に向いたら
		else if (m_Rot.y <= DirRoationFront)
		{
			// クリア時のアニメに変更
			m_Model.SetAnimeNo((int)PlayerAnime::eClear);
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
		// アニメ時間を初期化
		CRenderer::SetAnimeTime(0.0f);
	}
	// アニメ再生時間取得
	CRenderer::AnimePlayTime();

	// アニメ切り替え 再生が終わったらアイドル状態に クリア時のアニメはループにしたいので切り替えなし
	if(m_Model.GetAnimeNo() != (int)PlayerAnime::eClear)
		m_Model.AnimeChange((int)PlayerAnime::eNone);

	// 再生が終わったらアイドル状態に
	m_Caterpillar->GetModel().AnimeChange((int)CaterpillarAnime::eNone, AnimeSpeed);
	m_Gear->GetModel().AnimeChange((int)GearAnime::eNone, AnimeSpeed);
	m_Generare->GetModel().AnimeChange((int)GenerareAnime::eNone, AnimeSpeed);
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
	if (CObjectManager::IsObject(TagWall,nextPlayerPos) || CObjectManager::IsObject(TagGimic, nextPlayerPos))
		// プレイヤーの座標を現在地に戻す
		m_Coord = currentPlayerPos;

	// プレイヤーの移動先にキューブが存在する場合
	else if (CObjectManager::IsObject(TagCube, nextPlayerPos))
	{
		// キューブ移動のアニメーション判定
		m_bMoveCube = true;

		// 移動するキューブを取得
		const auto& Cube = CObjectManager::GetObjectAtPosition(TagCube, nextPlayerPos);

		// 移動するキューブの位置を取得
		XMINT2 currentCubePos = Cube.lock()->GetCoord();

		// キューブの移動先位置を設定
		XMINT2 nextCubepos = GetNextPosition(dir, Cube.lock()->GetCoord());

		// キューブの移動先にオブジェクトが存在するなら
		if (CObjectManager::IsObject(TagWall, nextCubepos)  || CObjectManager::IsObject(TagCube, nextCubepos) ||
			CObjectManager::IsObject(TagClear, nextCubepos) || CObjectManager::IsObject(TagKey, nextCubepos) ||
			CObjectManager::IsObject(TagGimic, nextCubepos))
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

			// キューブ押したときのエフェクト発生
			XMFLOAT3 CubePos = Cube.lock()->GetPos();
			GetNextMove(dir, CubePos);
			CEffectManager::CreateEffect(Effect_CubeMove, CubePos);

			// プレイヤーの歩数をカウントする
			StepCalc(nextPlayerPos, step);
		}
	}
	// プレイヤーの移動先が鍵だったら
	else if (CObjectManager::IsObject(TagKey, nextPlayerPos))
	{
		// 鍵取得
		CSound::Play(SE_KEY_GIMIC);

		// プレイヤーの座標を位置を更新
		m_Coord = nextPlayerPos;
		GetNextMove(dir, m_Move);

		// プレイヤーの歩数をカウントする
		StepCalc(nextPlayerPos, step);

		// 鍵とギミックのエフェクト発生
		const auto& key = CObjectManager::SearchObjectTag(TagKey);
		const auto& Gimic = CObjectManager::SearchObjectTag(TagGimic);
		XMFLOAT3 keyPos = key.lock()->GetPos();
		XMFLOAT3 GimicPos = Gimic.lock()->GetPos();

		// ギミック破壊時にズームする
		//CCamera::GetInstance().ZoomTarget(GimicPos);

		CEffectManager::CreateEffect(Effect_KeyBreak, keyPos);
		CEffectManager::CreateEffect(Effect_GimicBreak, GimicPos);

		// オブジェクトを消去
		CObjectManager::DestroyObject(TagKey);
		CObjectManager::DestroyObject(TagGimic);
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
		if (CObjectManager::IsObject(TagClear, nextPlayerPos))
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
		CEffectManager::CreateEffect(Effect_PlayerMove, m_Pos);
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
	if (CObjectManager::IsObject(TagTrap, pos))
	{
		// トラップ効果音
		CSound::Play(SE_TRAP);
		step -= 2;
	}
	// 移動先にトゲがないなら
	else
		step--;
}
