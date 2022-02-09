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

using namespace DirectX;

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class BillBoard abstract
{
public:
	BillBoard(): m_BillMesh(){}
	~BillBoard() = default;

	// �e�N�X�`�����[�h
	HRESULT LoadBillTexture(const wchar_t* FileName)
	{
		HRESULT hr = S_OK;
		hr = CreateTextureFromFile(GetDevice(), FileName, &m_BillMesh.m_pTexture);
		return hr;
	}
	HRESULT LoadBillTexture(const char* FileName)
	{
		HRESULT hr = S_OK;
		hr = CreateTextureFromFile(GetDevice(), FileName, &m_BillMesh.m_pTexture);
		return hr;
	}

public:
	void InitBill()
	{
		m_BillPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_BillSize = XMFLOAT2(1.0f, 1.0f);
		m_BillUV = XMFLOAT2(0.0f, 0.0f);
		m_BillFrameSize = XMFLOAT2(1.0f, 1.0f);
		m_BillAngleY = 0.0f;
		m_isBillInit = false;

		m_isBillFrameInit = false;
		m_BillFrameNum = XMINT2(1, 1);
		m_BillDiffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void UpdateBill() { m_BillMesh.Update(&m_BillMesh); }
	void DrawBill(int AnimNum = 0)
	{
		// ����������Ă��Ȃ���΂����ŏ�����
		if (!m_isBillInit)
		{
			ID3D11Device* pDevice = GetDevice();
			HRESULT hr = S_OK;
			// �}�e���A���̏����ݒ�
			m_BillMaterial.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_BillMaterial.Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			m_BillMaterial.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			m_BillMaterial.Power = 0.0f;
			m_BillMaterial.Emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			//m_BillMesh.m_pMaterial = &m_BillMaterial;
			m_BillMesh.m_pMaterial = nullptr;

			// �e�N�X�`���}�g���b�N�X�̐ݒ�
			XMStoreFloat4x4(&m_BillMesh.m_MtxTexture, XMMatrixIdentity());

			// ���[���h�}�g���b�N�X������
			XMStoreFloat4x4(&m_BillMesh.m_MtxWorld, XMMatrixIdentity());

			// �v���~�e�B�u�^�C�v�ݒ�
			m_BillMesh.m_PrimitiveType = PT_TRIANGLESTRIP;

			// ���_���̍쐬
			m_BillMesh.m_nNumVertex = 4;
			VERTEX_3D* pVertexWk = new VERTEX_3D[m_BillMesh.m_nNumVertex];
			pVertexWk[0].vtx = XMFLOAT3(-0.5f, 0.5f, 0.0f);
			pVertexWk[1].vtx = XMFLOAT3(0.5f, 0.5f, 0.0f);
			pVertexWk[2].vtx = XMFLOAT3(-0.5f, -0.5f, 0.0f);
			pVertexWk[3].vtx = XMFLOAT3(0.5f, -0.5f, 0.0f);
			pVertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertexWk[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
			pVertexWk[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
			pVertexWk[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
			pVertexWk[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
			pVertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
			pVertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
			pVertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
			pVertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);
			m_BillMesh.m_nNumIndex = 4;
			int* pIndexWk = new int[4];
			pIndexWk[0] = 0;
			pIndexWk[1] = 1;
			pIndexWk[2] = 2;
			pIndexWk[3] = 3;
			hr = m_BillMesh.MakeMeshVertex(pDevice, &m_BillMesh, pVertexWk, pIndexWk);
			delete[] pIndexWk;
			delete[] pVertexWk;

			m_isBillInit = true;
		}

		// ���C�g�I�t
		Singleton<CLight>::GetInstance().SetDisable();
		//CLight::Get()->SetDisable();

		// �A���t�@�u�����h
		SetBlendState(BS_ALPHABLEND);

		// �ʒu�X�V
		m_BillMesh.m_Pos = m_BillPos;

		// �J�����r���[�}�g���N�X�擾
		XMFLOAT4X4 mView = Singleton<CCamera>::GetInstance().GetViewMatrix();

		m_BillMesh.m_MtxWorld._11 = mView._11;
		m_BillMesh.m_MtxWorld._12 = mView._21;
		m_BillMesh.m_MtxWorld._13 = mView._31;
		m_BillMesh.m_MtxWorld._21 = mView._12;
		m_BillMesh.m_MtxWorld._22 = mView._22;
		m_BillMesh.m_MtxWorld._23 = mView._32;
		m_BillMesh.m_MtxWorld._31 = mView._13;
		m_BillMesh.m_MtxWorld._32 = mView._23;
		m_BillMesh.m_MtxWorld._33 = mView._33;


		// �T�C�Y�ύX
		//m_BillMesh.m_MtxWorld._11 *= (m_BillSize.x * 2);
		//m_BillMesh.m_MtxWorld._22 *= (m_BillSize.y * 2);

		XMMATRIX mScale = XMMatrixScaling(m_BillSize.x * 2, m_BillSize.y * 2, 1.0f);
		XMStoreFloat4x4(&m_BillMesh.m_MtxWorld, XMMatrixMultiply(mScale, XMLoadFloat4x4(&m_BillMesh.m_MtxWorld)));
		// �ʒu�𔽉f
		m_BillMesh.m_MtxWorld._41 = m_BillPos.x;
		m_BillMesh.m_MtxWorld._42 = m_BillPos.y;
		m_BillMesh.m_MtxWorld._43 = m_BillPos.z;

		// �e�N�X�`�����W�ړ� 
		if (m_isBillFrameInit)
		{
			XMMATRIX m_MtxTexture, mtxScale, mtxTranslate;

			int u = AnimNum % m_BillFrameNum.x;
			int v = AnimNum / m_BillFrameNum.y;

			// �e�N�X�`���}�g���b�N�X�̏�����
			m_MtxTexture = XMMatrixIdentity();

			// �X�P�[���𔽉f
			mtxScale = XMMatrixScaling(m_BillFrameSize.x, m_BillFrameSize.y, 1.0f);
			m_MtxTexture = XMMatrixMultiply(m_MtxTexture, mtxScale);

			// �ړ��𔽉f
			mtxTranslate = XMMatrixTranslation(m_BillFrameSize.x * u, m_BillFrameSize.y * v, 0.0f);
			m_MtxTexture = XMMatrixMultiply(m_MtxTexture, mtxTranslate);

			// �e�N�X�`���}�g���b�N�X�̐ݒ�
			XMStoreFloat4x4(&m_BillMesh.m_MtxTexture, m_MtxTexture);
		}

		// �F�K�� 
		m_BillMaterial.Diffuse = m_BillDiffuse;

		// �`��
		m_BillMesh.Draw(GetDeviceContext(), &m_BillMesh);

		SetBlendState(BS_NONE);

		// ���C�g�I��
		Singleton<CLight>::GetInstance().SetEnable();
	}
	void UninitBill()
	{ 
		m_BillMesh.Release(&m_BillMesh); 
	}

	// �Z�b�g�֐�
	void SetPosition(float X, float Y, float Z) { m_BillPos = XMFLOAT3(X, Y, Z); }		//���W�Z�b�g
	void SetPosition(XMFLOAT3 m_Pos) { m_BillPos = m_Pos; }
	void SetSize(float SizeX, float SizeY) { m_BillSize = XMFLOAT2(SizeX, SizeY); }				//�T�C�Y�Z�b�g
	void SetSize(XMFLOAT2 size) { m_BillSize = size; }
	void SetAngle(float Angle) { m_BillAngleY = Angle; }							//�p�x�Z�b�g
	void SetUV(float U, float V) { m_BillUV = XMFLOAT2(U, V); }					//�e�N�X�`�����W�Z�b�g
	void SetUV(XMFLOAT2 uv) { m_BillUV = uv; }
	void SetFrameSize(float TexSizeX, float TexSizeY) { m_BillFrameSize = XMFLOAT2(TexSizeX, TexSizeY); }	//�e�N�X�`���t���[���T�C�Y�Z�b�g
	void SetTex(ID3D11ShaderResourceView* tex) { m_BillMesh.m_pTexture = tex; }

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

	//MESH m_BillMesh;
	CMesh m_BillMesh;

private:
	// �����o�ϐ�
	MATERIAL m_BillMaterial;
	XMFLOAT3 m_BillPos;
	XMFLOAT2 m_BillSize;
	XMFLOAT2 m_BillUV;
	XMFLOAT2 m_BillFrameSize;
	float m_BillAngleY;
	bool m_isBillInit;
	XMFLOAT4 m_BillDiffuse;

	bool m_isBillFrameInit;
	XMINT2 m_BillFrameNum;

};

