//=============================================================================
// CPlayer.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "Player.h"
#include <Manager/GameManager.h>
#include <Manager/StageManager.h>
#include <Renderer/Effect/Effect.h>

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
	m_Dir = PlayerDir::eNone;
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
			m_Dir = PlayerDir::eNone;

			if (GetKeyTrigger(VK_W))// ��
			{
				m_Dir = PlayerDir::eUp;
				m_Rot.y = DirRoationBack;
			}
			if (GetKeyTrigger(VK_S))// ��
			{
				m_Dir = PlayerDir::eDown;
				m_Rot.y = DirRoationFront;
			}
			if (GetKeyTrigger(VK_A))// ��
			{
				m_Dir = PlayerDir::eLeft;
				m_Rot.y = DirRoationLeft;
			}
			if (GetKeyTrigger(VK_D))// �E
			{
				m_Dir = PlayerDir::eRight;
				m_Rot.y = DirRoationRight;
			}
			// ���������͂��ꂽ��ړ�
			if (m_Dir != PlayerDir::eNone)
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

		m_Dir = PlayerDir::eNone;

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
}

//=============================================================================
// 
// �v���C���[�A�j���[�V����
// 
//=============================================================================
void CPlayer::PlayerAnimetion()
{
	// �ړ����̃A�j������
	if (m_Dir != PlayerDir::eNone)
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
void CPlayer::MoveObject(PlayerDir& dir, int& step)
{
	// �v���C���[�̌��ݒn���擾
	XMINT2 currentPlayerPos = m_Coord;

	// �v���C���[�̈ړ���ʒu��ݒ�
	XMINT2 nextPlayerPos = GetNextPosition(dir, m_Coord);
	
	// �ړ��悪�ǂȂ�ړ��ł��Ȃ�
	if (CObjectManager::IsObject(TagWall,nextPlayerPos) || CObjectManager::IsObject(TagGimic, nextPlayerPos))
		// �v���C���[�̍��W�����ݒn�ɖ߂�
		m_Coord = currentPlayerPos;

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
			// �L���[�u�ړ���
			CSound::Play(SE_CUBE_MOVE);

			// �v���C���[�ƃL���[�u�̈ʒu���W���X�V
			m_Coord = nextPlayerPos;
			Cube.lock()->SetCoord(nextCubepos);

			// �v���C���[�ƃL���[�u���ړ�
			GetNextMove(dir, m_Move);
			GetNextMove(dir, Cube.lock()->GetMove());

			// �L���[�u�������Ƃ��̃G�t�F�N�g����
			XMFLOAT3 CubePos = Cube.lock()->GetPos();
			GetNextMove(dir, CubePos);
			CEffectManager::CreateEffect(Effect_CubeMove, CubePos);

			// �v���C���[�̕������J�E���g����
			StepCalc(nextPlayerPos, step);
		}
	}
	// �v���C���[�̈ړ��悪����������
	else if (CObjectManager::IsObject(TagKey, nextPlayerPos))
	{
		// ���擾
		CSound::Play(SE_KEY_GIMIC);

		// �v���C���[�̍��W���ʒu���X�V
		m_Coord = nextPlayerPos;
		GetNextMove(dir, m_Move);

		// �v���C���[�̕������J�E���g����
		StepCalc(nextPlayerPos, step);

		// ���ƃM�~�b�N�̃G�t�F�N�g����
		const auto& key = CObjectManager::SearchObjectTag(TagKey);
		const auto& Gimic = CObjectManager::SearchObjectTag(TagGimic);
		XMFLOAT3 keyPos = key.lock()->GetPos();
		XMFLOAT3 GimicPos = Gimic.lock()->GetPos();

		// �M�~�b�N�j�󎞂ɃY�[������
		//CCamera::GetInstance().ZoomTarget(GimicPos);

		CEffectManager::CreateEffect(Effect_KeyBreak, keyPos);
		CEffectManager::CreateEffect(Effect_GimicBreak, GimicPos);

		// �I�u�W�F�N�g������
		CObjectManager::DestroyObject(TagKey);
		CObjectManager::DestroyObject(TagGimic);
	}
	// �v���C���[�̈ړ���ɃL���[�u�����݂��Ȃ��ꍇ
	else
	{
		// �v���C���[�̍��W���X�V
		m_Coord = nextPlayerPos;
		GetNextMove(dir, m_Move);

		// �v���C���[�̕������J�E���g����
		StepCalc(nextPlayerPos, step);

		// �v���C���[�ƃN���A�̍��W����v������
		if (CObjectManager::IsObject(TagClear, nextPlayerPos))
		{
			CSound::Play(SE_CLEAR);
			CGameManager::SetState(GameState::eClear);
		}
	}

	// �ړ���
	//CSound::SetVolume(1.5f);
	CSound::Play(SE_PLAYER_MOVE);

	// �ړ����̃G�t�F�N�g
	if (m_Coord == nextPlayerPos)
	{
		CEffectManager::CreateEffect(Effect_PlayerMove, m_Pos);
	}
}

//=============================================================================
// 
// �ړ��ɂ����W�X�V
// 
//=============================================================================
XMINT2 CPlayer::GetNextPosition(PlayerDir dir, XMINT2 Coord)
{
	switch (dir)
	{
		// ��
	case(PlayerDir::eUp):
		Coord.y -= 1;
		break;
		// ��
	case(PlayerDir::eDown):
		Coord.y += 1;
		break;
		// ��
	case(PlayerDir::eLeft):
		Coord.x -= 1;
		break;
		// �E
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
// �I�u�W�F�N�g���ړ�������
// 
//=============================================================================
void CPlayer::GetNextMove(PlayerDir dir, XMFLOAT3& move)
{
	// �ړ���
	constexpr float MoveObject = 10.0f;

	switch (dir)
	{
		// ��
	case(PlayerDir::eUp):
		move.z += MoveObject;
		break;
		// ��
	case(PlayerDir::eDown):
		move.z -= MoveObject;
		break;
		// ��
	case(PlayerDir::eLeft):
		move.x -= MoveObject;
		break;
		// �E
	case(PlayerDir::eRight):
		move.x += MoveObject;
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
	// �ړ���Ƀg�Q������Ȃ�
	if (CObjectManager::IsObject(TagTrap, pos))
	{
		// �g���b�v���ʉ�
		CSound::Play(SE_TRAP);
		step -= 2;
	}
	// �ړ���Ƀg�Q���Ȃ��Ȃ�
	else
		step--;
}
