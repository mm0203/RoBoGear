//=============================================================================
// BillBoard.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "BillBorad.h"

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================


//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
BillBoard::BillBoard() : m_BillMesh()
{

}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void BillBoard::Init()
{
	m_BillPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_BillSize = XMFLOAT2(1.0f, 1.0f);
	m_BillUV = XMFLOAT2(0.0f, 0.0f);
	m_BillFrameSize = XMFLOAT2(1.0f, 1.0f);
	m_BillAngleY = 0.0f;
	m_isBillInit = false;
	m_BillDiffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_isBillFrameInit = false;
	m_BillFrameNum = XMINT2(1, 1);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void BillBoard::Uninit()
{
	m_BillMesh.Release(&m_BillMesh);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void BillBoard::Update()
{
	m_BillMesh.Update(&m_BillMesh);
	//Update(&m_BillMesh);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void BillBoard::Draw(int AnimNum)
{
	// �e�N�X�`���p�}�g���b�N�X�擾
	XMFLOAT4X4& MtxWolrdTexture = m_BillMesh.GetWorldMtxTexture();
	XMFLOAT4X4& MtxTexture = m_BillMesh.GetMtxTexture();

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
		//m_pMaterial = &m_BillMaterial;
		MATERIAL* Material = &m_BillMesh.GetMaterial();
		Material = nullptr;

		// �e�N�X�`���}�g���b�N�X�̐ݒ�
		XMStoreFloat4x4(&MtxTexture, XMMatrixIdentity());

		// ���[���h�}�g���b�N�X������
		XMStoreFloat4x4(&MtxWolrdTexture, XMMatrixIdentity());

		// �v���~�e�B�u�^�C�v�ݒ�
		ePrimitiveType& Primitive = m_BillMesh.GetPrimitive();
		Primitive = PT_TRIANGLESTRIP;

		// ���_���̍쐬
		int& NumVertex = m_BillMesh.GetNumVertex();
		NumVertex = 4;

		VERTEX_3D* pVertexWk = new VERTEX_3D[NumVertex];
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

		int& NumIndex = m_BillMesh.GetNumIndex();
		NumIndex = 4;
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
	XMFLOAT3& pos = m_BillMesh.GetPos();
	pos = m_BillPos;

	// �J�����r���[�}�g���N�X�擾
	XMFLOAT4X4 mView = Singleton<CCamera>::GetInstance().GetViewMatrix();

	MtxWolrdTexture._11 = mView._11;
	MtxWolrdTexture._12 = mView._21;
	MtxWolrdTexture._13 = mView._31;
	MtxWolrdTexture._21 = mView._12;
	MtxWolrdTexture._22 = mView._22;
	MtxWolrdTexture._23 = mView._32;
	MtxWolrdTexture._31 = mView._13;
	MtxWolrdTexture._32 = mView._23;
	MtxWolrdTexture._33 = mView._33;


	// �T�C�Y�ύX
	//MtxWolrdTexture._11 *= (m_BillSize.x * 2);
	//MtxWolrdTexture._22 *= (m_BillSize.y * 2);

	XMMATRIX mScale = XMMatrixScaling(m_BillSize.x * 2, m_BillSize.y * 2, 1.0f);
	XMStoreFloat4x4(&MtxWolrdTexture, XMMatrixMultiply(mScale, XMLoadFloat4x4(&MtxWolrdTexture)));
	// �ʒu�𔽉f
	MtxWolrdTexture._41 = m_BillPos.x;
	MtxWolrdTexture._42 = m_BillPos.y;
	MtxWolrdTexture._43 = m_BillPos.z;

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
		XMStoreFloat4x4(&MtxTexture, m_MtxTexture);
	}

	// �F�K�� 
	m_BillMaterial.Diffuse = m_BillDiffuse;

	// �`��
	m_BillMesh.Draw(GetDeviceContext(), &m_BillMesh);

	SetBlendState(BS_NONE);

	// ���C�g�I��
	Singleton<CLight>::GetInstance().SetEnable();
}

//=============================================================================
// 
// �e�N�X�`�����[�h
// 
//=============================================================================
HRESULT BillBoard::LoadBillTexture(const wchar_t* FileName)
{
	HRESULT hr = S_OK;
	ID3D11ShaderResourceView* pTexture;
	//hr = CreateTextureFromFile(GetDevice(), FileName, &m_BillMesh.m_pTexture);
	hr = CreateTextureFromFile(GetDevice(), FileName, &pTexture);
	m_BillMesh.SetTexture(pTexture);
	return hr;
}

//=============================================================================
// 
// �e�N�X�`�����[�h
// 
//=============================================================================
HRESULT BillBoard::LoadBillTexture(const char* FileName)
{
	HRESULT hr = S_OK;
	ID3D11ShaderResourceView* pTexture;
	//hr = CreateTextureFromFile(GetDevice(), FileName, &m_BillMesh.m_pTexture);
	hr = CreateTextureFromFile(GetDevice(), FileName, &pTexture);
	m_BillMesh.SetTexture(pTexture);
	return hr;
}