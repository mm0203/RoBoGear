//=============================================================================
// Light.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once
#include <main.h>
#include "../Singleton/singleton.h"
#include <System/Camera/Camera.h>
#include <System/Singleton/singleton.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CLight : public Singleton<CLight>
{
public:
	void Init();
	void Update();

	// getter 
	XMFLOAT4& GetDiffuse() { return m_diffuse; }
	XMFLOAT4& GetAmbient() { return m_ambient; }
	XMFLOAT4& GetSpecular() { return m_specular; }
	DirectX::XMFLOAT4X4& GetViewMatrix() { return m_ViewView; }
	DirectX::XMFLOAT4X4& GetProjMatrix() { return m_ProjMatrix; }
	// ��������
	XMFLOAT3& GetDir()
	{
		if (m_bEnable) return m_direction;
		static XMFLOAT3 off(0.0f, 0.0f, 0.0f);
		return off;
	}

	// setter
	void SetEnable(bool bEnable = true) { m_bEnable = bEnable; }
	void SetDisable(bool bDisable = true) { m_bEnable = !bDisable; }
	void SetProj(DirectX::XMFLOAT4X4& proj) { m_ProjMatrix = proj; }
	void SetView(DirectX::XMFLOAT4X4& proj) { m_ViewView = proj; }

private:

	// �V���O���g���݂̂ŃC���X�^���X����������
	friend class Singleton;

	CLight() = default;
	~CLight() = default;

	XMFLOAT3 m_direction; // ���̕���
	XMFLOAT4 m_diffuse;	  // �g�U�F + �A���t�@
	XMFLOAT4 m_ambient;	  // ���F
	XMFLOAT4 m_specular;  // ���ʔ��ːF+���x
	XMFLOAT3 m_vPos;	  // ���_
	XMFLOAT3 m_vTarget;	  // �����_
	XMFLOAT3 m_vUp;		  // ����x�N�g��
	XMFLOAT4X4 m_ProjMatrix;	//�v���W�F�N�V�����}�g���b�N�X
	XMFLOAT4X4 m_ViewView; // �r���[�}�g���b�N�X
	bool m_bEnable;

};
