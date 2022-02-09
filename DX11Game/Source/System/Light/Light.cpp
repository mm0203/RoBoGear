//=============================================================================
// Light.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Light.h"
#include <System/Input/input.h>
#include <System/Camera/Camera.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	constexpr XMFLOAT3 LightDirection = XMFLOAT3(0.0f, -1.0f, 1.0f);	 // 光の方向
	constexpr XMFLOAT4 LightDiffuse = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);	 // 拡散色 + アルファ
	constexpr XMFLOAT4 LightAmbient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);	 // 環境色
	constexpr XMFLOAT4 LightSpecular = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f); // 鏡面反射色+強度

	constexpr XMFLOAT3 LightDefPos = XMFLOAT3(200.0f, 1200.0f, -600.0f);;	 // 初期視点
	constexpr XMFLOAT3 LightDefTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);		 // 注視点初期座標
	constexpr XMFLOAT3 LightDefUpVector = XMFLOAT3(0.0f, 1.0f, 0.0f);	 // 上方ベクトル定数
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CLight::Init()
{
	XMFLOAT3 vDir = LightDirection; // 光の方向
	m_diffuse = LightDiffuse;		// 拡散色 + アルファ
	m_ambient = LightAmbient;	    // 環境色
	m_specular = LightSpecular;     // 鏡面反射色+強度
	XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&vDir)));

	// マトリックス作成
	m_vPos = LightDefPos;		// 視点
	m_vTarget = LightDefTarget;	// 注視点
	m_vUp = LightDefUpVector;	// 上方ベクトル
	m_bEnable = true;

	XMMATRIX m = XMMatrixLookAtLH(XMLoadFloat3(&m_vPos), XMLoadFloat3(&m_vTarget), XMLoadFloat3(&m_vUp));
	XMStoreFloat4x4(&m_ViewView, m);
}

//=============================================================================
// 
// 更新処理
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
	
	// ライト位置更新
	//m_vPos = CCamera::GetInstance().GetPos();

	// ライトマトリックスの更新
	XMMATRIX m = XMMatrixLookAtLH(XMLoadFloat3(&m_vPos), XMLoadFloat3(&m_vTarget), XMLoadFloat3(&m_vUp));
	XMStoreFloat4x4(&m_ViewView, m);

	// ライトベクトルの更新
	XMFLOAT3 vDir = m_vTarget;
	vDir.x -= m_vPos.x;
	vDir.y -= m_vPos.y;
	vDir.z -= m_vPos.z;
	XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&vDir)));
}