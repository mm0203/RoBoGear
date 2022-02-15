////=============================================================================
//// Camera.cpp
////=============================================================================
//// Author  ���� ���V
////=============================================================================
#include "Camera.h"
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <Manager/SceneManager.h>
#include <Manager/GameManager.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	// �J�����������W
	XMFLOAT3 CameraDefPos = XMFLOAT3(0.0f, 860.0f, -420.0f);
	XMFLOAT3 CameraGameStartPos = XMFLOAT3(0.0f, 440.0f, 0.0f);
	// �����_���΍��W
	XMFLOAT3 TargetRelativeTitlePos = XMFLOAT3(0.0f, 50.0f, 0.0f);
	XMFLOAT3 TargetRelativeGamePos = XMFLOAT3(0.0f, -400.0f, 0.0f);
	// �����_�������W
	XMFLOAT3 CameraDefTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);	 
	// �A���O���������W
	XMFLOAT3 CameraAnglePos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	// ����x�N�g���萔
	constexpr XMFLOAT3 CameraDefUpVector = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// ��Ɨp�ϐ�
	XMFLOAT3 Move{ 0.0f,0.0f,0.0f };		 // �J����,�����_�̈ړ���
	constexpr float CameraMoveSpeed = 8.0f;	 // �J�����̈ړ����x
	constexpr float Acc = 0.05f;			 // ����
	constexpr float XDistMax =  280.0f;		 // �J����X���ő勗��
	constexpr float XDistMin = -280.0f;		 // �J����X���ŏ�����
	constexpr float YDistMax = 860.0f;		 // �J����Y���ő勗��
	constexpr float ZDistMax = -420.0f;		 // �J����Z���ő勗��
}

//=============================================================================
// 
// ������
// 
//=============================================================================
void CCamera::Init()
{
	// �J������񏉊���
	int SceneNo = Singleton<SceneManager>::GetInstance().GetSceneNo();

	if (SceneNo == Scene_Title)
	{
		m_CameraPos = CameraDefPos;
		m_TargetRelativePos = TargetRelativeTitlePos;
	}

	if (SceneNo == Scene_Game)
	{
		m_CameraPos = CameraGameStartPos;
		m_TargetRelativePos = TargetRelativeGamePos;
	}

	if (SceneNo == Scene_Edit)
	{
		m_CameraPos = CameraDefPos;
		m_TargetRelativePos = TargetRelativeGamePos;
	}

	m_TargetPos = CameraDefTarget;	// �����_���W
	m_UpVector = CameraDefUpVector;	// ����x�N�g��
	m_CameraAngle = CameraAnglePos;	// �J�����p�x

	m_AspectRatio = AspectRatio; // �A�X�y�N�g��
	m_FovY = FovY;	// ����p
	m_NearClipZ = ViewNearZ;	// �O���N���b�v����
	m_FarClipZ = ViewFarZ;	// ����N���b�v����

	// �J�����ƒ����_�̋�����ݒ�
	float dx, dz;
	dx = CameraDefPos.x - m_TargetPos.x;
	dz = CameraDefPos.z - m_TargetPos.z;
	m_fInitLengthInterval = m_fLengthInterval = sqrtf(dx * dx + dz * dz);

	XMFLOAT3 vDir;
	XMStoreFloat3(&vDir, XMVector3Normalize
	(XMVectorSet(CameraDefPos.x - m_TargetPos.x,
				 CameraDefPos.y - m_TargetPos.y,
				 CameraDefPos.z - m_TargetPos.z, 0.0f)));

	// �J�����̑��΍��W���Z�b�g
	m_RelCameraPos.x = m_TargetPos.x + vDir.x * m_fLengthInterval;
	m_RelCameraPos.y = m_TargetPos.y + vDir.y * m_fLengthInterval;
	m_RelCameraPos.z = m_TargetPos.z + vDir.z * m_fLengthInterval;

	CalcWorldMatrix();
}

//=============================================================================
// 
// �J�����̍X�V����
// 
//=============================================================================
void CCamera::Update()
{
	// �萔��`
	constexpr float CameraRotSpeed  = 1.75f; // �J������]���x
	constexpr float Dece = 0.02f;	// ����

	// ��Ɨp�ϐ�	
	static float AngleMove = 0.0f;	// ��]��
	bool isInput = false;	// ������������

	// �f�o�b�O���[�h�ő���
	if (CGameManager::GetDebug())
	{
		// �J�����ړ�(4����)
		if (GetKeyPress(VK_W))		//�O��
		{
			Move.x += CameraMoveSpeed * CosDeg(m_CameraAngle.y) * Acc;
			Move.z += CameraMoveSpeed * SinDeg(m_CameraAngle.y) * Acc;
			isInput = true;
		}
		if (GetKeyPress(VK_S))		//���
		{
			Move.x += CameraMoveSpeed * CosDeg(m_CameraAngle.y + 180.0f) * Acc;
			Move.z += CameraMoveSpeed * SinDeg(m_CameraAngle.y + 180.0f) * Acc;
			isInput = true;
		}
		if (GetKeyPress(VK_D))		//�E
		{
			Move.x += CameraMoveSpeed * CosDeg(m_CameraAngle.y + 90.0f) * Acc;
			Move.z += CameraMoveSpeed * SinDeg(m_CameraAngle.y + 90.0f) * Acc;
			isInput = true;
		}
		if (GetKeyPress(VK_A))		//��
		{
			Move.x += CameraMoveSpeed * CosDeg(m_CameraAngle.y + 270.0f) * Acc;
			Move.z += CameraMoveSpeed * SinDeg(m_CameraAngle.y + 270.0f) * Acc;
			isInput = true;
		}

		// �J�����ړ�(�㉺)
		if (GetKeyPress(VK_SPACE))		//���
		{
			Move.y += CameraMoveSpeed * Acc;
			isInput = true;
		}
		if (GetKeyPress(VK_LCONTROL))	//����
		{
			Move.y -= CameraMoveSpeed * Acc;
			isInput = true;
		}

		// �J������]
		if (GetKeyPress(VK_L))		//�E
		{
			m_CameraAngle.y += CameraRotSpeed;
		}
		if (GetKeyPress(VK_J))		//��
		{
			m_CameraAngle.y -= CameraRotSpeed;
		}
		if (GetKeyPress(VK_I))		//���
		{
			m_TargetRelativePos.y += CameraRotSpeed * CameraRotSpeed;
		}
		if (GetKeyPress(VK_K))		//����
		{
			m_TargetRelativePos.y -= CameraRotSpeed * CameraRotSpeed;
		}
	}

	// �ړ����x����
	if (Move.x > CameraMoveSpeed || Move.x < -CameraMoveSpeed)
	{
		Move.x = (Move.x > 0) ? CameraMoveSpeed : -CameraMoveSpeed;
	}
	if (Move.z > CameraMoveSpeed || Move.z < -CameraMoveSpeed)
	{
		Move.z = (Move.z > 0) ? CameraMoveSpeed : -CameraMoveSpeed;
	}
	if (Move.y > CameraMoveSpeed || Move.y < -CameraMoveSpeed)
	{
		Move.y = (Move.y > 0) ? CameraMoveSpeed : -CameraMoveSpeed;
	}

	// �������� 
	if (!isInput)
	{
		if (Move.x)
		{
			Move.x -= (Move.x > 0) ? CameraMoveSpeed * Dece : -CameraMoveSpeed * Dece;
			if (Move.x < CameraMoveSpeed * Dece && Move.x > -CameraMoveSpeed * Dece) Move.x = 0;
		}
		if (Move.z)
		{
			Move.z -= (Move.z > 0) ? CameraMoveSpeed * Dece : -CameraMoveSpeed * Dece;
			if (Move.z < CameraMoveSpeed * Dece && Move.z > -CameraMoveSpeed * Dece) Move.z = 0;
		}
		if (Move.y)
		{
			Move.y -= (Move.y > 0) ? CameraMoveSpeed * Dece : -CameraMoveSpeed * Dece;
			if (Move.y < CameraMoveSpeed * Dece && Move.y > -CameraMoveSpeed * Dece) Move.y = 0;
		}
	}

	// �ړ��ʉ��Z
	m_CameraPos.x += Move.z;
	m_CameraPos.y += Move.y;
	m_CameraPos.z += Move.x;

	// �ړ���������
	if (m_CameraPos.y >= YDistMax)	m_CameraPos.y = YDistMax;
	if (m_CameraPos.z <= ZDistMax)	m_CameraPos.z = ZDistMax;

	// �p�x�ɑ΂����]�s����Z�o
	XMMATRIX mR = XMMatrixRotationY(XMConvertToRadians(m_CameraAngle.y));

	// ���W����]�}�g���b�N�X�ŉ�]
	XMVECTOR v = XMVectorSet(0.0f, -50.0f + m_TargetRelativePos.y, 200.0f, 1.0f);

	// ���W�ϊ�(��]����)
	v = XMVector3TransformCoord(v, mR);

	// ��]��̍��W��ۑ�
	XMStoreFloat3(&m_TargetPos, v);

	// �J�����𒆐S�ɒ����_����]
	m_TargetPos.x += m_CameraPos.x;
	m_TargetPos.y += m_CameraPos.y;
	m_TargetPos.z += m_CameraPos.z;

	// �J�����̕����x�N�g�����Z�o
	m_DirectionVector.x = m_TargetPos.x - m_CameraPos.x;
	m_DirectionVector.y = m_TargetPos.y - m_CameraPos.y;
	m_DirectionVector.z = m_TargetPos.z - m_CameraPos.z;

	XMVECTOR vec = XMVectorSet(m_DirectionVector.x, m_DirectionVector.y, m_DirectionVector.z, 1.0f);
	vec = XMVector3Normalize(vec);
	XMStoreFloat3(&m_DirectionVector, vec);	

	// �}�g���b�N�X�X�V
	UpdateMatrix();

	PrintDebugProc("CameraPos_X:%d:PosY%d:PosZ:%d:\n", (int)m_CameraPos.x, (int)m_CameraPos.y, (int)m_CameraPos.z);
	PrintDebugProc("CameraTargetPos_X:%d:PosY%d:PosZ:%d:\n", (int)m_TargetPos.x, (int)m_TargetPos.y, (int)m_TargetPos.z);
	PrintDebugProc("CameraAngle:%d\n", (int)m_CameraAngle.y);
	PrintDebugProc("RelativePos:%d\n", (int)m_TargetRelativePos.y);
}

//=============================================================================
// 
// �����_����Y�[���A�E�g
//
//=============================================================================
void CCamera::ZoomOut()
{
	Move.y += CameraMoveSpeed * Acc;
	Move.x -= CameraMoveSpeed * Acc;
}

//=============================================================================
// 
// �ΏۂɃY�[��
//
//=============================================================================
void CCamera::ZoomTarget(XMFLOAT3 pos)
{
	// �p�x�𒲐�
	m_TargetRelativePos.y += 5.0f;
	if (m_TargetRelativePos.y >= -150.0f)
		m_TargetRelativePos.y = -150.0f;

	// ���W�X�V
	m_CameraPos.x = m_CameraPos.x * 0.9f + (pos.x + m_RelCameraPos.x) * 0.1f;
	m_CameraPos.y = m_CameraPos.y * 0.9f + (pos.y + m_RelCameraPos.y) * 0.05f; // �������A�C���x����
	m_CameraPos.z = m_CameraPos.z * 0.9f + (pos.z + m_RelCameraPos.z) * 0.1f;
}

//=============================================================================
// 
// �r���[/�v���W�F�N�V���� �}�g���b�N�X�X�V
//
//=============================================================================
void CCamera::UpdateMatrix()
{
	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixLookAtLH(XMLoadFloat3(&m_CameraPos), XMLoadFloat3(&m_TargetPos), XMLoadFloat3(&m_UpVector)));
	XMStoreFloat4x4(&m_ProjectionMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(m_FovY), m_AspectRatio, m_NearClipZ, m_FarClipZ));
}
//=============================================================================
// 
// ���[���h �}�g���b�N�X�ݒ�
//
//=============================================================================
void CCamera::SetWorldMatrix(XMFLOAT4X4& mtxWorld)
{
	m_WorldMatrix = mtxWorld;
	m_CameraPos = XMFLOAT3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	m_TargetPos = XMFLOAT3(mtxWorld._41 + mtxWorld._31, mtxWorld._42 + mtxWorld._32, mtxWorld._43 + mtxWorld._33);
	m_UpVector = XMFLOAT3(mtxWorld._21, mtxWorld._22, mtxWorld._23);
}

//=============================================================================
// 
// ���_/�����_/����x�N�g�����烏�[���h �}�g���b�N�X�Z�o
//
//=============================================================================
XMFLOAT4X4& CCamera::CalcWorldMatrix()
{
	XMVECTOR vecZ = XMVectorSet(m_TargetPos.x - m_CameraPos.x, m_TargetPos.y - m_CameraPos.y, m_TargetPos.z - m_CameraPos.z, 0.0f);
	XMFLOAT3 vZ;
	XMStoreFloat3(&vZ, XMVector3Normalize(vecZ));
	XMVECTOR vecY = XMLoadFloat3(&m_UpVector);
	XMVECTOR vecX = XMVector3Normalize(XMVector3Cross(vecY, vecZ));
	XMFLOAT3 vX;
	XMStoreFloat3(&vX, vecX);
	vecY = XMVector3Normalize(XMVector3Cross(vecZ, vecX));
	XMFLOAT3 vY;
	XMStoreFloat3(&vY, vecY);

	m_WorldMatrix._11 = vX.x;
	m_WorldMatrix._12 = vX.y;
	m_WorldMatrix._13 = vX.z;
	m_WorldMatrix._14 = 0.0f;
	m_WorldMatrix._21 = vY.x;
	m_WorldMatrix._22 = vY.y;
	m_WorldMatrix._23 = vY.z;
	m_WorldMatrix._24 = 0.0f;
	m_WorldMatrix._31 = vZ.x;
	m_WorldMatrix._32 = vZ.y;
	m_WorldMatrix._33 = vZ.z;
	m_WorldMatrix._34 = 0.0f;
	m_WorldMatrix._41 = m_CameraPos.x;
	m_WorldMatrix._42 = m_CameraPos.y;
	m_WorldMatrix._43 = m_CameraPos.z;
	m_WorldMatrix._44 = 1.0f;

	return m_WorldMatrix;
}