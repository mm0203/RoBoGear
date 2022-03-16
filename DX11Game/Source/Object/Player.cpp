//=============================================================================
// CPlayer.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "Player.h"

// マネージャー
#include <Manager/GameManager.h>
#include <Manager/StageManager.h>

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

#include <Renderer/Effect/Effect.h>

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
	m_Dir = ObjectDir::eNone;
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

	// 巻き戻し用スタックに初期位置と向きを保存
	CGameManager::GetTimeLeap(eObject_Player).AddCoordStack(m_Coord);
	//CGameManager::GetTimeLeap(eObject_Player).AddRoationStackAdd(m_Rot);
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
			m_Dir = ObjectDir::eNone;

			if (GetKeyTrigger(VK_W))// 上
			{
				m_Dir = ObjectDir::eUp;
				m_Rot.y = DirRoationBack;
			}
			if (GetKeyTrigger(VK_S))// 下
			{
				m_Dir = ObjectDir::eDown;
				m_Rot.y = DirRoationFront;
			}
			if (GetKeyTrigger(VK_A))// 左
			{
				m_Dir = ObjectDir::eLeft;
				m_Rot.y = DirRoationLeft;
			}
			if (GetKeyTrigger(VK_D))// 右
			{
				m_Dir = ObjectDir::eRight;
				m_Rot.y = DirRoationRight;
			}
			// 方向が入力されたら移動
			if (m_Dir != ObjectDir::eNone)
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

		m_Dir = ObjectDir::eNone;

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

	//std::stack<XMINT2> pc = CGameManager::GetTimeLeap(eObject_Player).GetCoordStack();
	//std::stack<ObjectDir> pd = CGameManager::GetTimeLeap(eObject_Player).GetDirStack();
	//PrintDebugProc("PlayerCoordStack:%d\n", (int)pc.size());
	//PrintDebugProc("PlayerDirStack:%d\n", (int)pd.size());

	//std::stack<XMINT2> cc = CGameManager::GetTimeLeap(eObject_Cube).GetCoordStack();
	//std::stack<ObjectDir> cd = CGameManager::GetTimeLeap(eObject_Cube).GetDirStack();
	//PrintDebugProc("CubeCoordStack:%d\n", (int)cc.size());
	//PrintDebugProc("CubeDirStack:%d\n", (int)cd.size());

	//std::stack<XMINT2> kc = CGameManager::GetTimeLeap(eObject_Key).GetCoordStack();
	//PrintDebugProc("KeyCoordStack:%d\n", (int)kc.size());

}

//=============================================================================
// 
// プレイヤーアニメーション
// 
//=============================================================================
void CPlayer::PlayerAnimetion()
{
	// 移動時のアニメ判定
	if (m_Dir != ObjectDir::eNone)
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
void CPlayer::MoveObject(ObjectDir& dir, int& step)
{
	// プレイヤーの現在地を取得
	XMINT2 currentPlayerPos = m_Coord;

	// プレイヤーの移動先位置を設定
	XMINT2 nextPlayerPos = GetNextPosition(dir, m_Coord);
	
	// 移動先が壁なら移動できない
	if (CObjectManager::IsObject(TagWall, nextPlayerPos) || CObjectManager::IsObject(TagGimic, nextPlayerPos))
	{
		// プレイヤーの座標を現在地に戻す
		m_Coord = currentPlayerPos;
	}
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
			// 巻き戻し用スタックにキューブの位置と方向を保存
			CGameManager::GetTimeLeap(eObject_Cube).AddCoordStack(nextCubepos);
			//CGameManager::GetTimeLeap(eObject_Cube).AddDirStackAdd(dir);

			// 巻き戻し用スタックに空の要素を追加
			XMINT2 empty = XMINT2(-1, -1);
			CGameManager::GetTimeLeap(eObject_Key).AddCoordStack(empty);
			CGameManager::GetTimeLeap(eObject_Gimic).AddCoordStack(empty);

			// キューブ移動音
			CSound::Play(SE_CUBE_MOVE);

			// プレイヤーとキューブの位置座標を更新
			m_Coord = nextPlayerPos;
			Cube.lock()->SetCoord(nextCubepos);

			// キューブを移動
			GetNextMove(dir, Cube.lock()->GetMove());

			// キューブ押したときのエフェクト発生
			XMFLOAT3 CubePos = Cube.lock()->GetPos();
			GetNextMove(dir, CubePos);
			CEffectManager::CreateEffect(Effect_CubeMove, CubePos);
		}
	}
	// プレイヤーの移動先が鍵だったら
	else if (CObjectManager::IsObject(TagKey, nextPlayerPos))
	{
		// 鍵の音
		CSound::Play(SE_KEY_GIMIC);

		// 巻き戻し用スタックに空の要素を追加
		XMINT2 empty = XMINT2(-1, -1);
		CGameManager::GetTimeLeap(eObject_Cube).AddCoordStack(empty);
		//CGameManager::GetTimeLeap(eObject_Cube).AddDirStackAdd(dir);

		// プレイヤーの座標を位置を更新
		m_Coord = nextPlayerPos;

		// 鍵エフェクト発生
		const auto& key = CObjectManager::SearchObjectTag(TagKey);
		XMFLOAT3 keyPos = key.lock()->GetPos();
		CEffectManager::CreateEffect(Effect_KeyBreak, keyPos);

		// ギミックエフェクト発生
		const auto& Gimic = CObjectManager::SearchObjectTag(TagGimic);
		XMFLOAT3 GimicPos = Gimic.lock()->GetPos();
		CEffectManager::CreateEffect(Effect_GimicBreak, GimicPos);

		// 巻き戻し用スタックに鍵の座標を保存
		XMINT2 keyCoord = key.lock()->GetCoord();
		CGameManager::GetTimeLeap(eObject_Key).AddCoordStack(keyCoord);

		// 巻き戻し用スタックにギミックの座標を保存
		XMINT2 GimicCoord = Gimic.lock()->GetCoord();
		CGameManager::GetTimeLeap(eObject_Gimic).AddCoordStack(GimicCoord);

		// オブジェクトを消去
		CObjectManager::DestroyObject(TagKey);
		CObjectManager::DestroyObject(TagGimic);
	}
	// プレイヤーの移動先にキューブが存在しない場合
	else
	{
		// 巻き戻し用スタックに空の要素を追加
		//CGameManager::GetTimeLeap(eObject_Cube).AddDirStackAdd(dir);
		XMINT2 empty = XMINT2(-1, -1);
		CGameManager::GetTimeLeap(eObject_Cube).AddCoordStack(empty);
		CGameManager::GetTimeLeap(eObject_Key).AddCoordStack(empty);
		CGameManager::GetTimeLeap(eObject_Gimic).AddCoordStack(empty);

		// プレイヤーの座標を更新
		m_Coord = nextPlayerPos;

		// プレイヤーとクリアの座標が一致したら
		if (CObjectManager::IsObject(TagClear, nextPlayerPos))
		{
			CSound::Play(SE_CLEAR);
			CGameManager::SetState(GameState::eClear);
		}
	}

	// プレイヤーが移動できるとき
	if (m_Coord == nextPlayerPos)
	{
		// プレイヤー移動
		GetNextMove(dir, m_Move);

		// プレイヤーの歩数をカウントする
		StepCalc(nextPlayerPos, step);

		// プレイヤーの移動した座標と方向を保存
		CGameManager::GetTimeLeap(eObject_Player).AddCoordStack(m_Coord);
		CGameManager::GetTimeLeap(eObject_Player).AddDirStackAdd(dir);
		CGameManager::GetTimeLeap(eObject_Player).AddRoationStackAdd(m_Rot);

		// キューブの巻き戻し用スタックに要素を追加
		CGameManager::GetTimeLeap(eObject_Cube).AddDirStackAdd(dir);

		// エフェクト発生
		CEffectManager::CreateEffect(Effect_PlayerMove, m_Pos);
	}

	// 移動音
	CSound::Play(SE_PLAYER_MOVE);
}

//=============================================================================
// 
// 移動による座標更新
// 
//=============================================================================
XMINT2 CPlayer::GetNextPosition(ObjectDir dir, XMINT2 Coord)
{
	switch (dir)
	{
		// 上
	case(ObjectDir::eUp):
		Coord.y--;
		break;
		// 下
	case(ObjectDir::eDown):
		Coord.y++;
		break;
		// 左
	case(ObjectDir::eLeft):
		Coord.x--;
		break;
		// 右
	case(ObjectDir::eRight):
		Coord.x++;
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
void CPlayer::GetNextMove(ObjectDir dir, XMFLOAT3& move)
{
	switch (dir)
	{
		// 上
	case(ObjectDir::eUp):
		move.z += MovementObject;
		break;
		// 下
	case(ObjectDir::eDown):
		move.z -= MovementObject;
		break;
		// 左
	case(ObjectDir::eLeft):
		move.x -= MovementObject;
		break;
		// 右
	case(ObjectDir::eRight):
		move.x += MovementObject;
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
	// 移動先にトラップがあるなら
	if (CObjectManager::IsObject(TagTrap, pos))
	{
		// トラップ効果音
		CSound::Play(SE_TRAP);
		step -= 2;
	}
	// 移動先にトラップがないなら
	else
	{
		step--;
	}
}
