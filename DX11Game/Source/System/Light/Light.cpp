//=============================================================================
// Light.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "Light.h"
#include <System/Input/input.h>
#include <System/Camera/Camera.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const XMFLOAT3 LightDirection = XMFLOAT3(0.0f, -1.0f, 1.0f);	 // ���̕���
	const XMFLOAT4 LightDiffuse = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);	 // �g�U�F + �A���t�@
	const XMFLOAT4 LightAmbient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);	 // ���F
	const XMFLOAT4 LightSpecular = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f); // ���ʔ��ːF+���x

	const XMFLOAT3 LightDefPos = XMFLOAT3(200.0f, 1200.0f, -600.0f); // �������_
	const XMFLOAT3 LightDefTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);		 // �����_�������W
	const XMFLOAT3 LightDefUpVector = XMFLOAT3(0.0f, 1.0f, 0.0f);	 // ����x�N�g���萔
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CLight::Init()
{
	XMFLOAT3 vDir = LightDirection; // ���̕���
	m_diffuse = LightDiffuse;		// �g�U�F + �A���t�@
	m_ambient = LightAmbient;	    // ���F
	m_specular = LightSpecular;     // ���ʔ��ːF+���x
	XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&vDir)));

	// �}�g���b�N�X�쐬
	m_vPos = LightDefPos;		// ���_
	m_vTarget = LightDefTarget;	// �����_
	m_vUp = LightDefUpVector;	// ����x�N�g��
	m_bEnable = true;

	XMMATRIX m = XMMatrixLookAtLH(XMLoadFloat3(&m_vPos), XMLoadFloat3(&m_vTarget), XMLoadFloat3(&m_vUp));
	XMStoreFloat4x4(&m_ViewView, m);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================

void CLight::Update()
{
	//if (GetKeyPress(VK_F))	m_vPos.x += 10.f;
	//if (GetKeyPress(VK_H))	m_vPos.x -= 10.f;
	//if (GetKeyPress(VK_I))	m_vPos.z += 10.f;
	//if (GetKeyPress(VK_K))	m_vPos.z -= 10.f;
	//if (GetKeyPress(VK_T))	m_vPos.y += 10.f;
	//if (GetKeyPress(VK_G))	m_vPos.y -= 10.f;
	
	// ���C�g�ʒu�X�V
	//m_vPos = CCamera::GetInstance().GetPos();

	// ���C�g�}�g���b�N�X�̍X�V
	XMMATRIX m = XMMatrixLookAtLH(XMLoadFloat3(&m_vPos), XMLoadFloat3(&m_vTarget), XMLoadFloat3(&m_vUp));
	XMStoreFloat4x4(&m_ViewView, m);

	// ���C�g�x�N�g���̍X�V
	XMFLOAT3 vDir = m_vTarget;
	vDir.x -= m_vPos.x;
	vDir.y -= m_vPos.y;
	vDir.z -= m_vPos.z;
	XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&vDir)));
}