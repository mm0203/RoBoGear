//=============================================================================
// CPlayer.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Object.h>
#include <Manager/ObjectManager.h>
#include "Caterpillar.h"
#include "Gear.h"
#include "Generare.h"

#define MODEL_PLAYER "data/model/Object/MainAnim_Blender/Main_Re_Blender.fbx"

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================

// �v���C���[����
enum class PlayerDir
{
	eNone = 0,
	eUp,
	eDown,
	eLeft,
	eRight,
	ePlayerDirMax
};

// �v���C���[�A�j��
enum class PlayerAnime
{
	ePush = 0,
	eSmallPush,
	eClear,
	eNone,
	ePlayerAnimeMax
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CPlayer : public Object
{
public:
	CPlayer();
	~CPlayer() = default;

	void Init()	  override;
	void Update() override;

private:
	// �A�j��
	void PlayerAnimetion();
	// �I�u�W�F�N�g�ړ�
	void MoveObject(PlayerDir& dir, int& step);
	// ���̈ړ����W
	XMINT2 GetNextPosition(PlayerDir dir, XMINT2 Coord);
	// ���̈ړ��ꏊ
	void GetNextMove(PlayerDir dir, XMFLOAT3& move);
	// �����v�Z
	void StepCalc(XMINT2 pos, int& step);

private:
	// �b��
	int m_nCount;
	// �ړ�����
	PlayerDir m_Dir;
	// �L���[�u�����A�j������
	bool m_bMoveCube;

	// �e���f���p�[�c�̃I�u�W�F�N�g
	obj_shared m_Caterpillar;
	obj_shared m_Gear;
	obj_shared m_Generare;
};