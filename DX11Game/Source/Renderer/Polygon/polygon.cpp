//=============================================================================
// polygon.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "polygon.h"
#include <Renderer/Graphics/Graphics.h>
#include <System/Singleton/singleton.h>
#include <Renderer/Shader/Script/Shader.h>
#include <Renderer/Shader/Script/ShaderList.h>

//=============================================================================
// 
// �\���̒�`
// 
//=============================================================================
// �V�F�[�_�ɓn���l
struct SHADER_GLOBAL 
{
	XMMATRIX	mWorld;		// ���[���h�ϊ��s��(�]�u�s��)
	XMMATRIX	mView;		// �r���[�ϊ��s��(�]�u�s��)
	XMMATRIX	mProj;		// �ˉe�ϊ��s��(�]�u�s��)
	XMMATRIX	mTex;		// �e�N�X�`���ϊ��s��(�]�u�s��)
};

//=============================================================================
// 
// �v���g�^�C�v�錾
// 
//=============================================================================
static HRESULT MakeVertexPolygon();
static void SetVertexPolygon();

//=============================================================================
// 
// �O���[�o���ϐ�
// 
//=============================================================================
static ID3D11ShaderResourceView*	g_pTexture;		// �e�N�X�`���ւ̃|�C���^

static VERTEX_2D	g_vertexWk[NUM_VERTEX];	// ���_���i�[���[�N

static XMFLOAT3		g_posPolygon;	// �|���S���̈ړ���
static XMFLOAT3		g_rotPolygon;	// �|���S���̉�]��
static XMFLOAT3		g_sizPolygon;	// �|���S���̃T�C�Y
static XMFLOAT4		g_colPolygon;	// �|���S���̒��_�J���[
static bool			g_bInvalidate;	// ���_�f�[�^�X�V�t���O

static XMFLOAT2		g_posTexFrame;	// UV���W
static XMFLOAT2		g_sizTexFrame;	// �e�N�X�`�����o�T�C�Y

ConstantBuffer*		g_pMeshCBuffer; // �萔�o�b�t�@
DXBuffer*			g_pMeshBuffer;  // ���b�V���o�b�t�@

static XMFLOAT4X4	g_mProj;		// �ˉe�ϊ��s��
static XMFLOAT4X4	g_mView;		// �r���[�ϊ��s��
static XMFLOAT4X4	g_mWorld;		// ���[���h�ϊ��s��
static XMFLOAT4X4	g_mTex;			// �e�N�X�`���ϊ��s��

//=============================================================================
// 
// ����������
// 
//=============================================================================
HRESULT InitPolygon()
{
	HRESULT hr = S_OK;

	g_pMeshCBuffer = nullptr;
	g_pMeshBuffer = nullptr;

	// �萔�o�b�t�@����
	g_pMeshCBuffer = new ConstantBuffer;
	g_pMeshCBuffer->Create(sizeof(SHADER_GLOBAL));

	// �ϊ��s�񏉊���
	XMStoreFloat4x4(&g_mWorld, XMMatrixIdentity());
	XMStoreFloat4x4(&g_mView, XMMatrixLookAtLH(XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	XMStoreFloat4x4(&g_mProj, XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f));
	XMStoreFloat4x4(&g_mTex, XMMatrixIdentity());
	g_mTex._44 = 0.0f;

	// �e���̏�����
	g_posPolygon = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_rotPolygon = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_sizPolygon = XMFLOAT3(1.0f, 1.0f, 1.0f);
	g_colPolygon = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_bInvalidate = false;

	g_posTexFrame = XMFLOAT2(0.0f, 0.0f);
	g_sizTexFrame = XMFLOAT2(1.0f, 1.0f);

	// ���_���̍쐬
	hr = MakeVertexPolygon();

	return hr;
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void UninitPolygon()
{
	SAFE_RELEASE(g_pTexture);
	SAFE_DELETE(g_pMeshCBuffer);
	SAFE_DELETE(g_pMeshBuffer);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void UpdatePolygon()
{

}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void DrawPolygon(ID3D11DeviceContext* pDeviceContext)
{
	// �g�k
	XMMATRIX mWorld = XMMatrixScaling(g_sizPolygon.x, g_sizPolygon.y, g_sizPolygon.z);
	// ��]
	mWorld *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(g_rotPolygon.x), XMConvertToRadians(g_rotPolygon.y), XMConvertToRadians(g_rotPolygon.z));
	// �ړ�
	mWorld *= XMMatrixTranslation(g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);

	// ���[���h �}�g���b�N�X�ɐݒ�
	XMStoreFloat4x4(&g_mWorld, mWorld);

	if (g_pTexture)
	{
		// �g�k
		mWorld = XMMatrixScaling(g_sizTexFrame.x, g_sizTexFrame.y, 1.0f);
		// �ړ�
		mWorld *= XMMatrixTranslation(g_posTexFrame.x, g_posTexFrame.y, 0.0f);
		// �e�N�X�`�� �}�g���b�N�X�ɐݒ�
		XMStoreFloat4x4(&g_mTex, mWorld);
	} 
	else 
	{
		// �e�N�X�`������
		g_mTex._44 = 0.0f;
	}

	// ���_�o�b�t�@�X�V
	SetVertexPolygon();

	// �V�F�[�_�Z�b�g
	GetVertexShader(POLYGON_VS)->Bind();
	GetPixelShader(POLYGON_PS)->Bind();

	// �T���v���Z�b�g
	Singleton<Graphics>::GetInstance().SetSamplerState(SAMPLER_POINT);

	// �e�N�X�`���Z�b�g
	pDeviceContext->PSSetShaderResources(0, 1, &g_pTexture);

	SHADER_GLOBAL cb;
	cb.mProj = XMMatrixTranspose(XMLoadFloat4x4(&g_mProj));
	cb.mView = XMMatrixTranspose(XMLoadFloat4x4(&g_mView));
	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&g_mWorld));
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&g_mTex));

	// �o�b�t�@�X�V
	g_pMeshCBuffer->Write(&cb);
	g_pMeshCBuffer->BindVS(0);
	g_pMeshCBuffer->BindPS(0);

	// �|���S���`��
	g_pMeshBuffer->Draw(NUM_VERTEX);
}

//=============================================================================
// 
// ���_�̍쐬
// 
//=============================================================================
HRESULT MakeVertexPolygon()
{
	// ���_���W�̐ݒ�
	g_vertexWk[0].vtx = XMFLOAT3(-0.5f,  0.5f, 0.0f);
	g_vertexWk[1].vtx = XMFLOAT3( 0.5f,  0.5f, 0.0f);
	g_vertexWk[2].vtx = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	g_vertexWk[3].vtx = XMFLOAT3( 0.5f, -0.5f, 0.0f);

	// �g�U���ˌ��̐ݒ�
	g_vertexWk[0].diffuse = g_colPolygon;
	g_vertexWk[1].diffuse = g_colPolygon;
	g_vertexWk[2].diffuse = g_colPolygon;
	g_vertexWk[3].diffuse = g_colPolygon;

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	g_vertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	g_vertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	g_vertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	// ���_&�C���f�b�N�X�o�b�t�@ ����
	DXBuffer::Desc desc;
	desc.vtxSize = sizeof(VERTEX_2D);
	desc.vtxCount = NUM_VERTEX;
	desc.idxSize = sizeof(int);
	desc.isWrite = true;
	desc.pVtx = &g_vertexWk[0];
	desc.pIdx = nullptr;
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	g_pMeshBuffer = new DXBuffer();
	HRESULT hr = g_pMeshBuffer->Create(desc);
	if (FAILED(hr)) { return hr; }

	return hr;
}

//=============================================================================
// 
// ���_���W�̐ݒ�
// 
//=============================================================================
void SetVertexPolygon()
{
	if (g_bInvalidate) 
	{
		//���_�o�b�t�@�̒��g�𖄂߂�
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		HRESULT hr = S_OK;

		// �g�U���ˌ��̐ݒ�
		g_vertexWk[0].diffuse = g_colPolygon;
		g_vertexWk[1].diffuse = g_colPolygon;
		g_vertexWk[2].diffuse = g_colPolygon;
		g_vertexWk[3].diffuse = g_colPolygon;

		// ���_�f�[�^��������
		g_pMeshBuffer->Write(g_vertexWk);

		// �t���O���N���A
		g_bInvalidate = false;
	}
}

//=============================================================================
// 
// �e�N�X�`���̐ݒ�
// 
//=============================================================================
void SetPolygonTexture(ID3D11ShaderResourceView* pTexture)
{
	g_pTexture = pTexture;
	g_mTex._44 = (g_pTexture) ? 1.0f : 0.0f;
}

//=============================================================================
// 
// �\�����W�̐ݒ�
// 
//=============================================================================
void SetPolygonPos(float fX, float fY)
{
	g_posPolygon.x = fX;
	g_posPolygon.y = fY;
}

//=============================================================================
// 
// �\���T�C�Y�̐ݒ�
// 
//=============================================================================
void SetPolygonSize(float fScaleX, float fScaleY)
{
	g_sizPolygon.x = fScaleX;
	g_sizPolygon.y = fScaleY;
}

//=============================================================================
// 
// �\���p�x�̐ݒ�(�P��:�x)
// 
//=============================================================================
void SetPolygonAngle(float fAngle)
{
	g_rotPolygon.z = fAngle;
}

//=============================================================================
// 
// ����e�N�X�`�����W�̐ݒ� (0.0��fU��1.0, 0.0��fV��1.0)
// 
//=============================================================================
void SetPolygonUV(float fU, float fV)
{
	g_posTexFrame.x = fU;
	g_posTexFrame.y = fV;
}

//=============================================================================
// 
// �e�N�X�`���t���[���T�C�Y�̐ݒ� (0.0��fWidth��1.0, 0.0��fHeight��1.0)
// 
//=============================================================================
void SetPolygonFrameSize(float fWidth, float fHeight)
{
	g_sizTexFrame.x = fWidth;
	g_sizTexFrame.y = fHeight;
}

//=============================================================================
// 
// ���_�J���[�̐ݒ�
// 
//=============================================================================
void SetPolygonColor(float fRed, float fGreen, float fBlue)
{
	if (fRed != g_colPolygon.x || fGreen != g_colPolygon.y || fBlue != g_colPolygon.z)
	{
		g_colPolygon.x = fRed;
		g_colPolygon.y = fGreen;
		g_colPolygon.z = fBlue;
		g_bInvalidate = true;
	}
}

//=============================================================================
// 
// �s�����x�̐ݒ�
// 
//=============================================================================
void SetPolygonAlpha(float fAlpha)
{
	if (fAlpha != g_colPolygon.w)
	{
		g_colPolygon.w = fAlpha;
		g_bInvalidate = true;
	}
}