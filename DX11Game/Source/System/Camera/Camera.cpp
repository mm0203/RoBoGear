////=============================================================================
//// Camera.cpp
////=============================================================================
//// Author  松野 将之
////=============================================================================
#include "Camera.h"
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <Manager/SceneManager.h>
#include <Manager/GameManager.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	// カメラ初期座標
	XMFLOAT3 CameraDefPos = XMFLOAT3(0.0f, 860.0f, -420.0f);
	XMFLOAT3 CameraGameStartPos = XMFLOAT3(0.0f, 440.0f, 0.0f);
	// 注視点相対座標
	XMFLOAT3 TargetRelativeTitlePos = XMFLOAT3(0.0f, 50.0f, 0.0f);
	XMFLOAT3 TargetRelativeGamePos = XMFLOAT3(0.0f, -400.0f, 0.0f);
	// 注視点初期座標
	XMFLOAT3 CameraDefTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);	 
	// アングル初期座標
	XMFLOAT3 CameraAnglePos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	// 上方ベクトル定数
	const XMFLOAT3 CameraDefUpVector = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// 作業用変数
	XMFLOAT3 Move{ 0.0f,0.0f,0.0f };	 // カメラ,注視点の移動量
	const float CameraMoveSpeed = 5.0f;	 // カメラの移動速度
	const float Acc = 0.05f;			 // 慣性
	const float XDistMax =  280.0f;		 // カメラX軸最大距離
	const float XDistMin = -280.0f;		 // カメラX軸最小距離
	const float YDistMax = 860.0f;		 // カメラY軸最大距離
	const float ZDistMax = -420.0f;		 // カメラZ軸最大距離
	const float ClearRelative = -150.0f; // クリア時の角度
}

//=============================================================================
// 
// 初期化
// 
//=============================================================================
void CCamera::Init()
{
	// カメラ情報初期化
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

	m_TargetPos = CameraDefTarget;	// 注視点座標
	m_UpVector = CameraDefUpVector;	// 上方ベクトル
	m_CameraAngle = CameraAnglePos;	// カメラ角度

	m_AspectRatio = AspectRatio; // アスペクト比
	m_FovY = FovY;				 // 視野角
	m_NearClipZ = ViewNearZ;	 // 前方クリップ距離
	m_FarClipZ = ViewFarZ;		 // 後方クリップ距離

	// カメラと注視点の距離を設定
	float dx, dz;
	dx = CameraDefPos.x - m_TargetPos.x;
	dz = CameraDefPos.z - m_TargetPos.z;
	m_fInitLengthInterval = m_fLengthInterval = sqrtf(dx * dx + dz * dz);

	XMFLOAT3 vDir;
	XMStoreFloat3(&vDir, XMVector3Normalize
	(XMVectorSet(CameraDefPos.x - m_TargetPos.x,
				 CameraDefPos.y - m_TargetPos.y,
				 CameraDefPos.z - m_TargetPos.z, 0.0f)));

	// カメラの相対座標をセット
	m_RelCameraPos.x = m_TargetPos.x + vDir.x * m_fLengthInterval;
	m_RelCameraPos.y = m_TargetPos.y + vDir.y * m_fLengthInterval;
	m_RelCameraPos.z = m_TargetPos.z + vDir.z * m_fLengthInterval;

	CalcWorldMatrix();
}

//=============================================================================
// 
// カメラの更新処理
// 
//=============================================================================
void CCamera::Update()
{
	// 定数定義
	constexpr float CameraRotSpeed  = 1.75f; // カメラ回転速度
	constexpr float Dece = 0.02f;	// 減衰

	// 作業用変数	
	static float AngleMove = 0.0f;	// 回転量
	bool isInput = false;	// 減衰処理判定

	// デバッグモードで操作
	if (CGameManager::GetDebug())
	{
		// カメラ移動(4方向)
		if (GetKeyPress(VK_W))		//前方
		{
			Move.x += CameraMoveSpeed * CosDeg(m_CameraAngle.y) * Acc;
			Move.z += CameraMoveSpeed * SinDeg(m_CameraAngle.y) * Acc;
			isInput = true;
		}
		if (GetKeyPress(VK_S))		//後方
		{
			Move.x += CameraMoveSpeed * CosDeg(m_CameraAngle.y + 180.0f) * Acc;
			Move.z += CameraMoveSpeed * SinDeg(m_CameraAngle.y + 180.0f) * Acc;
			isInput = true;
		}
		if (GetKeyPress(VK_D))		//右
		{
			Move.x += CameraMoveSpeed * CosDeg(m_CameraAngle.y + 90.0f) * Acc;
			Move.z += CameraMoveSpeed * SinDeg(m_CameraAngle.y + 90.0f) * Acc;
			isInput = true;
		}
		if (GetKeyPress(VK_A))		//左
		{
			Move.x += CameraMoveSpeed * CosDeg(m_CameraAngle.y + 270.0f) * Acc;
			Move.z += CameraMoveSpeed * SinDeg(m_CameraAngle.y + 270.0f) * Acc;
			isInput = true;
		}

		// カメラ移動(上下)
		if (GetKeyPress(VK_SPACE))		//上方
		{
			Move.y += CameraMoveSpeed * Acc;
			isInput = true;
		}
		if (GetKeyPress(VK_LCONTROL))	//下方
		{
			Move.y -= CameraMoveSpeed * Acc;
			isInput = true;
		}

		// カメラ回転
		if (GetKeyPress(VK_L))		//右
		{
			m_CameraAngle.y += CameraRotSpeed;
		}
		if (GetKeyPress(VK_J))		//左
		{
			m_CameraAngle.y -= CameraRotSpeed;
		}
		if (GetKeyPress(VK_I))		//上方
		{
			m_TargetRelativePos.y += CameraRotSpeed * CameraRotSpeed;
		}
		if (GetKeyPress(VK_K))		//下方
		{
			m_TargetRelativePos.y -= CameraRotSpeed * CameraRotSpeed;
		}
	}

	// 移動速度制限
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

	// 減速処理 
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

	// 移動量加算
	m_CameraPos.x += Move.z;
	m_CameraPos.y += Move.y;
	m_CameraPos.z += Move.x;

	// 移動距離制限
	if (m_CameraPos.y >= YDistMax)	m_CameraPos.y = YDistMax;
	if (m_CameraPos.z <= ZDistMax)	m_CameraPos.z = ZDistMax;

	// 角度に対する回転行列を算出
	XMMATRIX mR = XMMatrixRotationY(XMConvertToRadians(m_CameraAngle.y));

	// 座標を回転マトリックスで回転
	XMVECTOR v = XMVectorSet(0.0f, -50.0f + m_TargetRelativePos.y, 200.0f, 1.0f);

	// 座標変換(回転処理)
	v = XMVector3TransformCoord(v, mR);

	// 回転後の座標を保存
	XMStoreFloat3(&m_TargetPos, v);

	// カメラを中心に注視点が回転
	m_TargetPos.x += m_CameraPos.x;
	m_TargetPos.y += m_CameraPos.y;
	m_TargetPos.z += m_CameraPos.z;

	// カメラの方向ベクトルを算出
	m_DirectionVector.x = m_TargetPos.x - m_CameraPos.x;
	m_DirectionVector.y = m_TargetPos.y - m_CameraPos.y;
	m_DirectionVector.z = m_TargetPos.z - m_CameraPos.z;

	XMVECTOR vec = XMVectorSet(m_DirectionVector.x, m_DirectionVector.y, m_DirectionVector.z, 1.0f);
	vec = XMVector3Normalize(vec);
	XMStoreFloat3(&m_DirectionVector, vec);	

	// マトリックス更新
	UpdateMatrix();

	PrintDebugProc("CameraPos_X:%d:PosY%d:PosZ:%d:\n", (int)m_CameraPos.x, (int)m_CameraPos.y, (int)m_CameraPos.z);
	PrintDebugProc("CameraTargetPos_X:%d:PosY%d:PosZ:%d:\n", (int)m_TargetPos.x, (int)m_TargetPos.y, (int)m_TargetPos.z);
	PrintDebugProc("CameraAngle:%d\n", (int)m_CameraAngle.y);
	PrintDebugProc("RelativePos:%d\n", (int)m_TargetRelativePos.y);
}

//=============================================================================
// 
// 注視点からズームアウト
//
//=============================================================================
void CCamera::ZoomOut()
{
	Move.y += CameraMoveSpeed * Acc;
	Move.x -= CameraMoveSpeed * Acc;
}

//=============================================================================
// 
// 対象にズーム
//
//=============================================================================
void CCamera::ZoomTarget(XMFLOAT3 pos)
{
	// ズーム時に対象の正面に来るように角度を調整
	m_TargetRelativePos.y += CameraMoveSpeed;
	if (m_TargetRelativePos.y >= ClearRelative)
		m_TargetRelativePos.y = ClearRelative;

	// 座標更新
	m_CameraPos.x = m_CameraPos.x * 0.9f + (pos.x + m_RelCameraPos.x) * 0.1f;
	m_CameraPos.y = m_CameraPos.y * 0.9f + (pos.y + m_RelCameraPos.y) * 0.05f; // 高さをアイレベルに
	m_CameraPos.z = m_CameraPos.z * 0.9f + (pos.z + m_RelCameraPos.z) * 0.1f;
}

//=============================================================================
// 
// ビュー/プロジェクション マトリックス更新
//
//=============================================================================
void CCamera::UpdateMatrix()
{
	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixLookAtLH(XMLoadFloat3(&m_CameraPos), XMLoadFloat3(&m_TargetPos), XMLoadFloat3(&m_UpVector)));
	XMStoreFloat4x4(&m_ProjectionMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(m_FovY), m_AspectRatio, m_NearClipZ, m_FarClipZ));
}
//=============================================================================
// 
// ワールド マトリックス設定
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
// 視点/注視点/上方ベクトルからワールド マトリックス算出
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