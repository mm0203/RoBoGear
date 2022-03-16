//=============================================================================
// CPlayer.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "Player.h"

// �}�l�[�W���[
#include <Manager/GameManager.h>
#include <Manager/StageManager.h>

// �V�X�e��
#include <System/Camera/Camera.h>
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Sound/Sound.h>
#include <System/Helper/XMFLOAT_Helper.h>
#include <time.h>

// �I�u�W�F�N�g
#include <Object/Cube.h>
#include <Object/Gimic.h>
#include <Object/Key.h>
#include <Object/Wall.h>
#include <Object/Trap.h>
#include <Object/Clear.h>

#include <Renderer/Effect/Effect.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	// ���f���������Ă������
	const float DirRoationFront = 0.0f;		// ����
	const float DirRoationBack  = 180.0f;	// �w��
	const float DirRoationLeft  = 90.0f;	// ��
	const float DirRoationRight = -90.0f;	// �E

	const float AnimeSpeed = 2.0f;	// �A�j���Đ����x
	const float RotateSpeed = 2.0f; // �N���A���̃v���C���[��]���x
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CPlayer::CPlayer()
{
	// �v���C���[�̏��
	m_tag = TagPlayer;
	m_nCount = 0;
	m_Dir = ObjectDir::eNone;
	m_Model.LoadModel(MODEL_PLAYER);
	m_bMoveCube = false;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CPlayer::Init()
{
	// �e�v���C���[���f������
	m_Caterpillar = CObjectManager::CreateObject<CCaterpillar>();
	m_Gear = CObjectManager::CreateObject<CGear>();
	m_Generare = CObjectManager::CreateObject<CGenerare>();

	// �A�j��No������
	m_Model.SetAnimeNo((int)PlayerAnime::eNone);
	m_Caterpillar->GetModel().SetAnimeNo((int)CaterpillarAnime::eNone);
	m_Gear->GetModel().SetAnimeNo((int)GearAnime::eNone);
	m_Generare->GetModel().SetAnimeNo((int)GenerareAnime::eNone);

	// �����߂��p�X�^�b�N�ɏ����ʒu�ƌ�����ۑ�
	CGameManager::GetTimeLeap(eObject_Player).AddCoordStack(m_Coord);
	//CGameManager::GetTimeLeap(eObject_Player).AddRoationStackAdd(m_Rot);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CPlayer::Update()
{
	// �ړ�
	ObjectMove();

	// �����擾
	int& nStep = CGameManager::GetStep();

	// ��Ԏ擾
	GameState state = CGameManager::GetState();

	switch (state)
	{
	// ������
	case GameState::eMove:

		// �f�o�b�O���[�h���͑���s��
		if (!CGameManager::GetDebug())
		{
			m_Dir = ObjectDir::eNone;

			if (GetKeyTrigger(VK_W))// ��
			{
				m_Dir = ObjectDir::eUp;
				m_Rot.y = DirRoationBack;
			}
			if (GetKeyTrigger(VK_S))// ��
			{
				m_Dir = ObjectDir::eDown;
				m_Rot.y = DirRoationFront;
			}
			if (GetKeyTrigger(VK_A))// ��
			{
				m_Dir = ObjectDir::eLeft;
				m_Rot.y = DirRoationLeft;
			}
			if (GetKeyTrigger(VK_D))// �E
			{
				m_Dir = ObjectDir::eRight;
				m_Rot.y = DirRoationRight;
			}
			// ���������͂��ꂽ��ړ�
			if (m_Dir != ObjectDir::eNone)
			{
				MoveObject(m_Dir, nStep);
			}
		}

		// ����0�̎��ɃS�[��������Q�[���I�[�o�[���Ȃ�
		if (nStep <= 0 && CGameManager::GetState() != GameState::eClear)
		{
			// BGM��~
			CSound::Stop(GAME);

			// �Q�[���I�[�o�[��
			CSound::Play(SE_GAMEOVER_BEEP);
			CSound::Play(SE_GAMEOVER_SMOKE);

			CGameManager::SetState(GameState::eGameOver);
		}
		break;
	// �N���A
	case GameState::eClear:

		m_Dir = ObjectDir::eNone;

		// �v���C���[�ɃY�[��
		CCamera::GetInstance().ZoomTarget(m_Pos);

		m_nCount++;

		// ���ʂ������ĂȂ�����1�b�o�߂�����
		if (m_Rot.y >= DirRoationFront && m_nCount >= Second * 1)
		{
			// ���ʌ����܂ŉ�]������
			m_Rot.y -= RotateSpeed;
		}
		// ���ʂɌ�������
		else if (m_Rot.y <= DirRoationFront)
		{
			// �N���A���̃A�j���ɕύX
			m_Model.SetAnimeNo((int)PlayerAnime::eClear);
		}
		break;
	default:
		break;
	}

	// �A�j���[�V�����X�V
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
// �v���C���[�A�j���[�V����
// 
//=============================================================================
void CPlayer::PlayerAnimetion()
{
	// �ړ����̃A�j������
	if (m_Dir != ObjectDir::eNone)
	{
		m_Caterpillar->GetModel().SetAnimeNo((int)CaterpillarAnime::eMove);
		m_Gear->GetModel().SetAnimeNo((int)GearAnime::eMove);
		m_Generare->GetModel().SetAnimeNo((int)GenerareAnime::eMove);

		// �L���[�u�����A�j������
		if (m_bMoveCube)
		{
			m_Model.SetAnimeNo((int)PlayerAnime::ePush);
			m_bMoveCube = false;
		}
		else
		{
			// �����ĂȂ��Ƃ��̓A�j���Ȃ�
			m_Model.SetAnimeNo((int)PlayerAnime::eNone);
		}
		// �A�j�����Ԃ�������
		CRenderer::SetAnimeTime(0.0f);
	}
	// �A�j���Đ����Ԏ擾
	CRenderer::AnimePlayTime();

	// �A�j���؂�ւ� �Đ����I�������A�C�h����Ԃ� �N���A���̃A�j���̓��[�v�ɂ������̂Ő؂�ւ��Ȃ�
	if(m_Model.GetAnimeNo() != (int)PlayerAnime::eClear)
		m_Model.AnimeChange((int)PlayerAnime::eNone);

	// �Đ����I�������A�C�h����Ԃ�
	m_Caterpillar->GetModel().AnimeChange((int)CaterpillarAnime::eNone, AnimeSpeed);
	m_Gear->GetModel().AnimeChange((int)GearAnime::eNone, AnimeSpeed);
	m_Generare->GetModel().AnimeChange((int)GenerareAnime::eNone, AnimeSpeed);
}

//=============================================================================
// 
// �I�u�W�F�N�g�̔��� & �ړ�
// 
//=============================================================================
void CPlayer::MoveObject(ObjectDir& dir, int& step)
{
	// �v���C���[�̌��ݒn���擾
	XMINT2 currentPlayerPos = m_Coord;

	// �v���C���[�̈ړ���ʒu��ݒ�
	XMINT2 nextPlayerPos = GetNextPosition(dir, m_Coord);
	
	// �ړ��悪�ǂȂ�ړ��ł��Ȃ�
	if (CObjectManager::IsObject(TagWall, nextPlayerPos) || CObjectManager::IsObject(TagGimic, nextPlayerPos))
	{
		// �v���C���[�̍��W�����ݒn�ɖ߂�
		m_Coord = currentPlayerPos;
	}
	// �v���C���[�̈ړ���ɃL���[�u�����݂���ꍇ
	else if (CObjectManager::IsObject(TagCube, nextPlayerPos))
	{
		// �L���[�u�ړ��̃A�j���[�V��������
		m_bMoveCube = true;

		// �ړ�����L���[�u���擾
		const auto& Cube = CObjectManager::GetObjectAtPosition(TagCube, nextPlayerPos);

		// �ړ�����L���[�u�̈ʒu���擾
		XMINT2 currentCubePos = Cube.lock()->GetCoord();

		// �L���[�u�̈ړ���ʒu��ݒ�
		XMINT2 nextCubepos = GetNextPosition(dir, Cube.lock()->GetCoord());

		// �L���[�u�̈ړ���ɃI�u�W�F�N�g�����݂���Ȃ�
		if (CObjectManager::IsObject(TagWall, nextCubepos)  || CObjectManager::IsObject(TagCube, nextCubepos) ||
			CObjectManager::IsObject(TagClear, nextCubepos) || CObjectManager::IsObject(TagKey, nextCubepos) ||
			CObjectManager::IsObject(TagGimic, nextCubepos))
		{
			// �L���[�u���ړ��ł��Ȃ���
			CSound::Play(SE_CUBE_MOVE_NONE);

			// �v���C���[�ƃL���[�u�̈ʒu���W�����ݒn�ɖ߂�
			m_Coord = currentPlayerPos;
			Cube.lock()->SetCoord(currentCubePos);
		}
		// �L���[�u�̈ړ���ɃI�u�W�F�N�g�����݂��Ȃ��Ȃ�
		else
		{
			// �����߂��p�X�^�b�N�ɃL���[�u�̈ʒu�ƕ�����ۑ�
			CGameManager::GetTimeLeap(eObject_Cube).AddCoordStack(nextCubepos);
			//CGameManager::GetTimeLeap(eObject_Cube).AddDirStackAdd(dir);

			// �����߂��p�X�^�b�N�ɋ�̗v�f��ǉ�
			XMINT2 empty = XMINT2(-1, -1);
			CGameManager::GetTimeLeap(eObject_Key).AddCoordStack(empty);
			CGameManager::GetTimeLeap(eObject_Gimic).AddCoordStack(empty);

			// �L���[�u�ړ���
			CSound::Play(SE_CUBE_MOVE);

			// �v���C���[�ƃL���[�u�̈ʒu���W���X�V
			m_Coord = nextPlayerPos;
			Cube.lock()->SetCoord(nextCubepos);

			// �L���[�u���ړ�
			GetNextMove(dir, Cube.lock()->GetMove());

			// �L���[�u�������Ƃ��̃G�t�F�N�g����
			XMFLOAT3 CubePos = Cube.lock()->GetPos();
			GetNextMove(dir, CubePos);
			CEffectManager::CreateEffect(Effect_CubeMove, CubePos);
		}
	}
	// �v���C���[�̈ړ��悪����������
	else if (CObjectManager::IsObject(TagKey, nextPlayerPos))
	{
		// ���̉�
		CSound::Play(SE_KEY_GIMIC);

		// �����߂��p�X�^�b�N�ɋ�̗v�f��ǉ�
		XMINT2 empty = XMINT2(-1, -1);
		CGameManager::GetTimeLeap(eObject_Cube).AddCoordStack(empty);
		//CGameManager::GetTimeLeap(eObject_Cube).AddDirStackAdd(dir);

		// �v���C���[�̍��W���ʒu���X�V
		m_Coord = nextPlayerPos;

		// ���G�t�F�N�g����
		const auto& key = CObjectManager::SearchObjectTag(TagKey);
		XMFLOAT3 keyPos = key.lock()->GetPos();
		CEffectManager::CreateEffect(Effect_KeyBreak, keyPos);

		// �M�~�b�N�G�t�F�N�g����
		const auto& Gimic = CObjectManager::SearchObjectTag(TagGimic);
		XMFLOAT3 GimicPos = Gimic.lock()->GetPos();
		CEffectManager::CreateEffect(Effect_GimicBreak, GimicPos);

		// �����߂��p�X�^�b�N�Ɍ��̍��W��ۑ�
		XMINT2 keyCoord = key.lock()->GetCoord();
		CGameManager::GetTimeLeap(eObject_Key).AddCoordStack(keyCoord);

		// �����߂��p�X�^�b�N�ɃM�~�b�N�̍��W��ۑ�
		XMINT2 GimicCoord = Gimic.lock()->GetCoord();
		CGameManager::GetTimeLeap(eObject_Gimic).AddCoordStack(GimicCoord);

		// �I�u�W�F�N�g������
		CObjectManager::DestroyObject(TagKey);
		CObjectManager::DestroyObject(TagGimic);
	}
	// �v���C���[�̈ړ���ɃL���[�u�����݂��Ȃ��ꍇ
	else
	{
		// �����߂��p�X�^�b�N�ɋ�̗v�f��ǉ�
		//CGameManager::GetTimeLeap(eObject_Cube).AddDirStackAdd(dir);
		XMINT2 empty = XMINT2(-1, -1);
		CGameManager::GetTimeLeap(eObject_Cube).AddCoordStack(empty);
		CGameManager::GetTimeLeap(eObject_Key).AddCoordStack(empty);
		CGameManager::GetTimeLeap(eObject_Gimic).AddCoordStack(empty);

		// �v���C���[�̍��W���X�V
		m_Coord = nextPlayerPos;

		// �v���C���[�ƃN���A�̍��W����v������
		if (CObjectManager::IsObject(TagClear, nextPlayerPos))
		{
			CSound::Play(SE_CLEAR);
			CGameManager::SetState(GameState::eClear);
		}
	}

	// �v���C���[���ړ��ł���Ƃ�
	if (m_Coord == nextPlayerPos)
	{
		// �v���C���[�ړ�
		GetNextMove(dir, m_Move);

		// �v���C���[�̕������J�E���g����
		StepCalc(nextPlayerPos, step);

		// �v���C���[�̈ړ��������W�ƕ�����ۑ�
		CGameManager::GetTimeLeap(eObject_Player).AddCoordStack(m_Coord);
		CGameManager::GetTimeLeap(eObject_Player).AddDirStackAdd(dir);
		CGameManager::GetTimeLeap(eObject_Player).AddRoationStackAdd(m_Rot);

		// �L���[�u�̊����߂��p�X�^�b�N�ɗv�f��ǉ�
		CGameManager::GetTimeLeap(eObject_Cube).AddDirStackAdd(dir);

		// �G�t�F�N�g����
		CEffectManager::CreateEffect(Effect_PlayerMove, m_Pos);
	}

	// �ړ���
	CSound::Play(SE_PLAYER_MOVE);
}

//=============================================================================
// 
// �ړ��ɂ����W�X�V
// 
//=============================================================================
XMINT2 CPlayer::GetNextPosition(ObjectDir dir, XMINT2 Coord)
{
	switch (dir)
	{
		// ��
	case(ObjectDir::eUp):
		Coord.y--;
		break;
		// ��
	case(ObjectDir::eDown):
		Coord.y++;
		break;
		// ��
	case(ObjectDir::eLeft):
		Coord.x--;
		break;
		// �E
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
// �I�u�W�F�N�g���ړ�������
// 
//=============================================================================
void CPlayer::GetNextMove(ObjectDir dir, XMFLOAT3& move)
{
	switch (dir)
	{
		// ��
	case(ObjectDir::eUp):
		move.z += MovementObject;
		break;
		// ��
	case(ObjectDir::eDown):
		move.z -= MovementObject;
		break;
		// ��
	case(ObjectDir::eLeft):
		move.x -= MovementObject;
		break;
		// �E
	case(ObjectDir::eRight):
		move.x += MovementObject;
		break;
	default:
		break;
	}
}
//=============================================================================
// 
// �v���C���[�̈ړ��ŕ����J�E���g�����炷
// 
//=============================================================================
void CPlayer::StepCalc(XMINT2 pos, int& step)
{
	// �ړ���Ƀg���b�v������Ȃ�
	if (CObjectManager::IsObject(TagTrap, pos))
	{
		// �g���b�v���ʉ�
		CSound::Play(SE_TRAP);
		step -= 2;
	}
	// �ړ���Ƀg���b�v���Ȃ��Ȃ�
	else
	{
		step--;
	}
}
