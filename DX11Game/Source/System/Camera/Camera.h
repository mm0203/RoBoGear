//=============================================================================
// camera.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once
#include <main.h>
#include <System/Singleton/singleton.h>

#define	VIEW_NEAR_Z			(50.0f)					
#define	VIEW_FAR_Z			(5000.0f)				

#define FOG_NEAR_Z	(VIEW_FAR_Z * 0.3f)
#define FOG_FAR_Z	(VIEW_FAR_Z * 0.6f)

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================

constexpr float ViewNearZ =	10.0f;		// �r���[���ʂ�NearZ�l
constexpr float ViewFarZ  = 10000.0f;	// �r���[���ʂ�FarZ�l
constexpr float FogNearZ = ViewFarZ * 0.3f;	// �t�H�O��NearZ�l
constexpr float FogFarZ  = ViewFarZ * 0.6f;	// �t�H�O��FarZ�l


//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CCamera : public Singleton<CCamera>
{
public:
	void Init();
	void Update();
	XMFLOAT4X4& CalcWorldMatrix();
	void UpdateMatrix();
	void ZoomTarget(XMFLOAT3 pos);
	void ZoomOut();

	// getter
	XMFLOAT3& GetPos() { return m_CameraPos; }
	XMFLOAT3& GetAngle() { return m_CameraAngle; }
	XMFLOAT4X4& GetWorldMatrix() { return m_WorldMatrix; }
	XMFLOAT4X4& GetViewMatrix() { return m_ViewMatrix; }
	XMFLOAT4X4& GetProjMatrix() { return m_ProjectionMatrix; }

	// setter
	void SetWorldMatrix(XMFLOAT4X4& mtxWorld);

private:
	// �V���O���g���݂̂ŃC���X�^���X����������
	friend class Singleton;

	CCamera() = default;
	~CCamera() = default;

	DirectX::XMFLOAT3 m_CameraPos;			// �J�������W
	DirectX::XMFLOAT3 m_TargetPos;			// �����_���W
	DirectX::XMFLOAT3 m_RelCameraPos;		// �J�������΍��W
	DirectX::XMFLOAT3 m_TargetRelativePos;	// �����_���΍��W
	DirectX::XMFLOAT3 m_UpVector;			// ����x�N�g��
	DirectX::XMFLOAT3 m_DirectionVector;	// �����x�N�g��
	DirectX::XMFLOAT3 m_CameraAngle;		//�J�����p�x
	float m_fLengthInterval;				// �J�����ƒ����_�̋���
	float m_fInitLengthInterval;			// �����J�����ƒ����_�̋���

	DirectX::XMFLOAT4X4 m_WorldMatrix;		//���[���h�}�g���b�N�X
	DirectX::XMFLOAT4X4 m_ViewMatrix;		//�r���[�}�g���b�N�X
	DirectX::XMFLOAT4X4 m_ProjectionMatrix;	//�v���W�F�N�V�����}�g���b�N�X

	// �萔��`
	static constexpr float m_AspectRatio= (float)SCREEN_WIDTH / SCREEN_HEIGHT;	// �A�X�y�N�g��
	static constexpr float m_FovY = 50.0f;			// ����p
	static constexpr float m_NearClipZ = 10.0f;		// �O���N���b�v����
	static constexpr float m_FarClipZ = 10000.0f;	// ����N���b�v����
};