//=============================================================================
// meshfield.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "StageGround.h"
#include <Manager/SceneManager.h>

//=============================================================================
// 
// ��`
// 
//=============================================================================
#define SIZE_BROCK	(100.0f)
#define	TEXTURE_FILENAME	L"data/texture/field001.jpg"
#define	TEXTURE_NROMAL		L"data/texture/Bump.jpg"
#define	TEXTURE_AMBIENT		L"data/texture/Anbient001.jpg"

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	constexpr int sizeX = 21;
	constexpr int sizeY = 15;
}
//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CStageGround::CStageGround()
{
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CStageGround::Init()
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;

	// �e�N�X�`�� �}�g���b�N�X������
	XMFLOAT4X4& MtxTexture = m_MeshField.GetMtxTexture();
	XMStoreFloat4x4(&MtxTexture, XMMatrixIdentity());

	// �ʒu�A�����̏����ݒ�
	XMFLOAT3& pos = m_MeshField.GetPos();
	XMFLOAT3& rot = m_MeshField.GetRot();
	pos = XMFLOAT3(0.0f, -1.0f, 0.0f);
	rot = XMFLOAT3(0.0f, 0.0f, 0.0f);

	int SceneNo = Singleton<SceneManager>::GetInstance().GetSceneNo();

	// �e�N�X�`���ǂݍ���
	ID3D11ShaderResourceView* pTexture;

	// �t�B�[���h�p�e�N�X�`��
	hr = CreateTextureFromFile(pDevice,TEXTURE_FILENAME,&pTexture);
	m_MeshField.SetTexture(pTexture);

	// �G�f�B�b�g���[�h�͕\�����Ȃ�
	if (SceneNo != Scene_Edit)
	{
		// �o���v�}�b�v
		hr = CreateTextureFromFile(pDevice, TEXTURE_NROMAL, &pTexture);
		m_MeshField.SetNormalTexture(pTexture);

		// ���}�b�v
		hr = CreateTextureFromFile(pDevice, TEXTURE_AMBIENT, &pTexture);
		m_MeshField.SetAmbientTexture(pTexture);
	}

	// ���_���̐ݒ�
	int& NumVertex = m_MeshField.GetNumVertex();
	NumVertex = (sizeX + 1) * (sizeY + 1);

	// �C���f�b�N�X���̐ݒ�
	int& NumIndex = m_MeshField.GetNumIndex();
	NumIndex = (sizeX + 1) * 2 * sizeY + (sizeY - 1) * 2;

	// �|���S�����̐ݒ�
	int nNumPolygon = sizeX * sizeY * 2 + (sizeY - 1) * 4;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	VERTEX_3D* pVertexWk = new VERTEX_3D[NumVertex];

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	int* pIndexWk = new int[NumIndex];

	// ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D* pVtx = pVertexWk;
#if 0
	const float texSizeX = 1.0f / STAGE_SIZE;
	const float texSizeZ = 1.0f / STAGE_SIZE;
#else
	const float texSizeX = 1.0f;
	const float texSizeZ = 1.0f;
#endif

	for (int nCntVtxZ = 0; nCntVtxZ < sizeY + 1; ++nCntVtxZ)
	{
		const float ANGLE = XM_2PI / sizeX;

		for (int nCntVtxX = 0; nCntVtxX < sizeX + 1; ++nCntVtxX)
		{
			// ���_���W�̐ݒ�
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].vtx.x = -(sizeX / 2.0f) * SIZE_BROCK + nCntVtxX * SIZE_BROCK;
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].vtx.y = 0.0f;
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].vtx.z = (sizeY / 2.0f) * SIZE_BROCK - nCntVtxZ * SIZE_BROCK;

			// �@���̐ݒ�
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].nor = XMFLOAT3(0.0f, 1.0, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
	int* pIdx = pIndexWk;

	int nCntIdx = 0;
	for (int nCntVtxZ = 0; nCntVtxZ < sizeY; ++nCntVtxZ)
	{
		if (nCntVtxZ > 0) 
		{
			// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (sizeX + 1);
			++nCntIdx;
		}

		for (int nCntVtxX = 0; nCntVtxX < sizeX + 1; ++nCntVtxX)
		{
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (sizeX + 1) + nCntVtxX;
			++nCntIdx;
			pIdx[nCntIdx] = nCntVtxZ * (sizeX + 1) + nCntVtxX;
			++nCntIdx;
		}

		if (nCntVtxZ < sizeY - 1)
		{
			// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
			pIdx[nCntIdx] = nCntVtxZ * (sizeX + 1) + sizeX;
			++nCntIdx;
		}
	}

	// ���_�o�b�t�@/�C���f�b�N�X �o�b�t�@����
	hr = m_MeshField.MakeMeshVertex(pDevice, &m_MeshField, pVertexWk, pIndexWk);

	// �ꎞ�z����
	delete[] pIndexWk;
	delete[] pVertexWk;
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CStageGround::Uninit()
{
	m_MeshField.Release(&m_MeshField);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CStageGround::Update()
{
	m_MeshField.Update(&m_MeshField);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CStageGround::Draw()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	//DrawMeshShadow(pDeviceContext, &m_MeshField);
	m_MeshField.Draw(pDeviceContext, &m_MeshField);
}
