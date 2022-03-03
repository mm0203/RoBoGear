//=============================================================================
// Ceffect.h
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