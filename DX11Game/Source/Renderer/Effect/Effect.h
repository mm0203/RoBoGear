//=============================================================================
// Effect.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <main.h>
#include <Manager/Sprite.h>
#include <Renderer/Billboard/BillBorad.h>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================
enum EffectID
{
	Effect_GimicBreak,	// �M�~�b�N�j��
	Effect_KeyBreak,	// ���������
	Effect_PlayerMove,	// �v���C���[�ړ�
	Effect_CubeMove,	// �L���[�u�ړ�
	Effect_Trap,		// �_���[�W��
	Effect_MAX
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CEffect : public CBillBoard
{
	friend class CEffectManager; // �t�����h�N���X
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
	// �t���[����
	XMINT2 m_FrameNum;
	// �G�t�F�N�g�A�j���̍ő吔
	int m_MaxAnimNum;
	// ���݂̃A�j����
	int m_CurrentAnimNum;
	// �A�j���Đ��X�s�[�h
	int m_Speed;
	// �A�j���̍Đ��J�E���g
	int m_SpeedCount;
};

// �G�t�F�N�g�}�l�[�W���[�N���X
class CEffectManager : public CSprite
{
public:
	CEffectManager() = default;
	~CEffectManager() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

	// �G�t�F�N�g����
	static void CreateEffect(EffectID ID, XMFLOAT3 pos);
	// �G�t�F�N�g�폜
	static void DeleteObject(CEffect*);
	// �G�t�F�N�g���X�g�擾
	std::vector<CEffect*> GetActiveList() { return m_ActiveList; }

private:
	// �G�t�F�N�g�ǉ�
	static void AddObject(CEffect);
	// �G�t�F�N�g�I�u�W�F�N�g����
	static void CreateObject(int num = 10);
	static void UpdateObject();

private:
	static std::vector<CEffect*> m_UnusedList;	// ���g�p���X�g
	static std::vector<CEffect*> m_ActiveList;	// �g���G�t�F�N�g
	static std::vector<CEffect*> m_DeleteList;  // �폜����G�t�F�N�g
};