//=============================================================================
// CCollision.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once
#pragma warning(disable : 5208)

#include <main.h>
#include <System/Debug/debugproc.h>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================
typedef struct
{
	bool isHit;			//�������Ă��邩�ۂ�
	bool Upper;			//���
	bool Bottom;		//���
	bool RightSide;		//�E��
	bool LeftSide;		//����
	bool Foreground;	//��O
	bool Background;	//��

	//�ϐ����Z�b�g
	void Reset() 
	{	
		isHit = false;
		Upper = false;
		Bottom = false;
		RightSide = false;
		LeftSide = false;
		Foreground = false;
		Background = false;
	}
	// �f�o�b�O�\��
	void ShowColState()
	{
		PrintDebugProc("\nHit%d:Up%d:Bo%d:Ri%d:Le%d:Fo%d:Ba%d\n", isHit, Upper, Bottom, RightSide, LeftSide, Foreground, Background);
	}
}CollisionSurface;

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CCollision abstract
{
public:
	//-- �����o�ϐ� --
	bool CollisionAABB(CCollision& Target)	//�����蔻�菈��
	{
		XMFLOAT3 tPos = Target.GetColPos();
		XMFLOAT2 tDisX = Target.GetColDisX();
		XMFLOAT2 tDisY = Target.GetColDisY();
		XMFLOAT2 tDisZ = Target.GetColDisZ();

		if (m_ColPos.x - m_ColDisX.y <= tPos.x + tDisX.x && tPos.x - tDisX.y <= m_ColPos.x + m_ColDisX.x &&
			m_ColPos.y - m_ColDisY.y <= tPos.y + tDisY.x && tPos.y - tDisY.y <= m_ColPos.y + m_ColDisY.x &&
			m_ColPos.z - m_ColDisZ.y <= tPos.z + tDisZ.x && tPos.z - tDisZ.y <= m_ColPos.z + m_ColDisZ.x)
		{
			return true;
		}
		else return false;
	}

	//�ʂ̏ڂ�������
	CollisionSurface CollisiomSurface(CCollision& Target)
	{
		// ����p�ϐ�
		CollisionSurface ColState;
		ColState.Reset();

		// �S��false�̏�ԂŕԂ�
		if (!CollisionAABB(Target)) return ColState;
		else ColState.isHit = true;

		XMFLOAT3 tPos = Target.GetColPos();
		XMFLOAT2 tDisX = Target.GetColDisX();
		XMFLOAT2 tDisY = Target.GetColDisY();
		XMFLOAT2 tDisZ = Target.GetColDisZ();

		// �萔
		const float SmallDistance = 0.1f;

		// ���
		if (m_ColPos.x + m_ColDisX.x - SmallDistance >= tPos.x - tDisX.y &&
			m_ColPos.x - m_ColDisX.y + SmallDistance <= tPos.x + tDisX.x &&
			m_ColPos.z + m_ColDisZ.x - SmallDistance >= tPos.z - tDisZ.y &&
			m_ColPos.z - m_ColDisZ.y + SmallDistance <= tPos.z + tDisZ.x &&
			m_ColPos.y + m_ColDisY.x <= tPos.y + tDisY.x &&
			m_ColPos.y + m_ColDisY.x >= tPos.y - tDisY.y)
			ColState.Upper = true;
		// ���
		if (m_ColPos.x + m_ColDisX.x - SmallDistance >= tPos.x - tDisX.y &&
			m_ColPos.x - m_ColDisX.y + SmallDistance <= tPos.x + tDisX.x &&
			m_ColPos.z + m_ColDisZ.x - SmallDistance >= tPos.z - tDisZ.y &&
			m_ColPos.z - m_ColDisZ.y + SmallDistance <= tPos.z + tDisZ.x &&
			m_ColPos.y - m_ColDisY.y <= tPos.y + tDisY.x &&
			m_ColPos.y - m_ColDisY.y >= tPos.y - tDisY.y)
			ColState.Bottom = true;
		// �E��
		if (m_ColPos.y + m_ColDisY.x - SmallDistance >= tPos.y - tDisY.y &&
			m_ColPos.y - m_ColDisY.y + SmallDistance <= tPos.y + tDisY.x &&
			m_ColPos.z + m_ColDisZ.x - SmallDistance >= tPos.z - tDisZ.y &&
			m_ColPos.z - m_ColDisZ.y + SmallDistance <= tPos.z + tDisZ.x &&
			m_ColPos.x + m_ColDisX.x <= tPos.x + tDisX.x &&
			m_ColPos.x + m_ColDisX.x >= tPos.x - tDisX.y)
			ColState.RightSide = true;
		// ����
		if (m_ColPos.y + m_ColDisY.x - SmallDistance >= tPos.y - tDisY.y &&
			m_ColPos.y - m_ColDisY.y + SmallDistance <= tPos.y + tDisY.x &&
			m_ColPos.z + m_ColDisZ.x - SmallDistance >= tPos.z - tDisZ.y &&
			m_ColPos.z - m_ColDisZ.y + SmallDistance <= tPos.z + tDisZ.x &&
			m_ColPos.x - m_ColDisX.y <= tPos.x + tDisX.x &&
			m_ColPos.x - m_ColDisX.y >= tPos.x - tDisX.y)
			ColState.LeftSide = true;
		// ��O��
		if (m_ColPos.y + m_ColDisY.x - SmallDistance >= tPos.y - tDisY.y &&
			m_ColPos.y - m_ColDisY.y + SmallDistance <= tPos.y + tDisY.x &&
			m_ColPos.x + m_ColDisX.x - SmallDistance >= tPos.x - tDisX.y &&
			m_ColPos.x - m_ColDisX.y + SmallDistance <= tPos.x + tDisX.x &&
			m_ColPos.z - m_ColDisZ.y <= tPos.z + tDisZ.x &&
			m_ColPos.z - m_ColDisZ.y >= tPos.z - tDisZ.y)
			ColState.Foreground = true;
		// ����
		if (m_ColPos.y + m_ColDisY.x - SmallDistance >= tPos.y - tDisY.y &&
			m_ColPos.y - m_ColDisY.y + SmallDistance <= tPos.y + tDisY.x &&
			m_ColPos.x + m_ColDisX.x - SmallDistance >= tPos.x - tDisX.y &&
			m_ColPos.x - m_ColDisX.y + SmallDistance <= tPos.x + tDisX.x &&
			m_ColPos.z + m_ColDisZ.x <= tPos.z + tDisZ.x &&
			m_ColPos.z + m_ColDisZ.x >= tPos.z - tDisZ.y)
			ColState.Background = true;
		return ColState;
	}

	// getter
	XMFLOAT3 GetColPos() { return m_ColPos; }
	XMFLOAT2 GetColDisX() { return m_ColDisX; }
	XMFLOAT2 GetColDisY() { return m_ColDisY; }
	XMFLOAT2 GetColDisZ() { return m_ColDisZ; }

	// setter
	void SetColPos(XMFLOAT3 pos) { m_ColPos = pos; }
	void SetColPos(float x, float y, float z) { m_ColPos = XMFLOAT3(x, y, z); }
	void SetColDisX(XMFLOAT2 disx) { m_ColDisX = disx; }
	void SetColDisX(float x, float y) { m_ColDisX = XMFLOAT2(x, y); }
	void SetColDisY(XMFLOAT2 disy) { m_ColDisY = disy; }
	void SetColDisY(float x, float y) { m_ColDisY = XMFLOAT2(x, y); }
	void SetColDisZ(XMFLOAT2 disz) { m_ColDisZ = disz; }
	void SetColDisZ(float x, float y) { m_ColDisZ = XMFLOAT2(x, y); }


private:
	XMFLOAT3 m_ColPos = {0.0f,0.0f,0.0f};	//����̒��S
	XMFLOAT2 m_ColDisX = { 0.0f,0.0f };		//�����X���� x -> �v���X���� y -> �}�C�i�X����
	XMFLOAT2 m_ColDisY = { 0.0f,0.0f };		//�����Y����
	XMFLOAT2 m_ColDisZ = { 0.0f,0.0f };		//�����Z����
};
