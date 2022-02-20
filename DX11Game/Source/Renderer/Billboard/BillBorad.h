//=============================================================================
// BillBoard.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <main.h>

// �V�X�e��
#include <System/Singleton/singleton.h>
#include <System/Camera/Camera.h>
#include <System/Light/Light.h>

// �����_�[
#include <Renderer/Mesh/mesh.h>
#include <Renderer/Texture/Texture.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class BillBoard
{
public:
	BillBoard();
	~BillBoard() = default;

public:
	void Init();
	void Update();
	void Draw(int AnimNum = 0);
	void Uninit();

	// �e�N�X�`�����[�h
	HRESULT LoadBillTexture(const wchar_t* FileName);
	HRESULT LoadBillTexture(const char* FileName);

	// setter 

	// ���W�Z�b�g
	void SetPosition(float X, float Y, float Z) { m_BillPos = XMFLOAT3(X, Y, Z); }	
	void SetPosition(XMFLOAT3 m_Pos) { m_BillPos = m_Pos; }
	// �T�C�Y�Z�b�g
	void SetSize(float SizeX, float SizeY) { m_BillSize = XMFLOAT2(SizeX, SizeY); }	
	void SetSize(XMFLOAT2 size) { m_BillSize = size; }
	// �p�x�Z�b�g
	void SetAngle(float Angle) { m_BillAngleY = Angle; }
	// �e�N�X�`�����W�Z�b�g
	void SetUV(float U, float V) { m_BillUV = XMFLOAT2(U, V); }
	void SetUV(XMFLOAT2 uv) { m_BillUV = uv; }
	// �e�N�X�`���t���[���T�C�Y�Z�b�g
	void SetFrameSize(float TexSizeX, float TexSizeY) { m_BillFrameSize = XMFLOAT2(TexSizeX, TexSizeY); }
	// void SetTex(ID3D11ShaderResourceView* tex) { m_BillMesh.m_pTexture = tex; }

	void SetBillFrameNum(XMINT2 frame) 
	{
		m_isBillFrameInit = true;
		m_BillFrameNum = frame;
		m_BillFrameSize.x = 1.0f / m_BillFrameNum.x;
		m_BillFrameSize.y = 1.0f / m_BillFrameNum.y;
	}
	void SetBillDiffuse(XMFLOAT4 dif) { m_BillDiffuse = dif; }

	// �Q�b�g�֐�
	XMFLOAT3 GetBillPos() { return m_BillPos; }
	XMFLOAT2 GetBillSize() { return m_BillSize; }

protected:
	CMesh m_BillMesh;			// �r���{�[�h�p���b�V��

private:
	MATERIAL m_BillMaterial;	// �}�e���A��
	XMFLOAT3 m_BillPos;			// �ʒu
	XMFLOAT2 m_BillSize;		// �T�C�Y
	XMFLOAT2 m_BillUV;			// UV���W
	XMFLOAT2 m_BillFrameSize;	// �t���[���T�C�Y
	float m_BillAngleY;			// �p�x
	bool m_isBillInit;			// ����������
	XMFLOAT4 m_BillDiffuse;		// �f�t���[�Y�J���[
	bool m_isBillFrameInit;		// �t���[������������
	XMINT2 m_BillFrameNum;		// �t���[����

};

