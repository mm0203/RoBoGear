//=============================================================================
// camera.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once
#include <main.h>
#include <System/Singleton/singleton.h>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================

constexpr float ViewNearZ =	10.0f;		// ビュー平面のNearZ値
constexpr float ViewFarZ  = 10000.0f;	// ビュー平面のFarZ値
constexpr float FogNearZ = ViewFarZ * 0.3f;	// フォグのNearZ値
constexpr float FogFarZ  = ViewFarZ * 0.6f;	// フォグのFarZ値
constexpr float AspectRatio = (float)SCREEN_WIDTH / SCREEN_HEIGHT; // アスペクト比
const float FovY = 50.0f; //　視野角

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CCamera : public CSingleton<CCamera>
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
	// シングルトンのみでインスタンス生成を許可
	friend class CSingleton;

	CCamera() = default;
	~CCamera() = default;

	DirectX::XMFLOAT3 m_CameraPos;			// カメラ座標
	DirectX::XMFLOAT3 m_TargetPos;			// 注視点座標
	DirectX::XMFLOAT3 m_RelCameraPos;		// カメラ相対座標
	DirectX::XMFLOAT3 m_TargetRelativePos;	// 注視点相対座標
	DirectX::XMFLOAT3 m_UpVector;			// 上方ベクトル
	DirectX::XMFLOAT3 m_DirectionVector;	// 方向ベクトル
	DirectX::XMFLOAT3 m_CameraAngle;		//カメラ角度
	float m_fLengthInterval;				// カメラと注視点の距離
	float m_fInitLengthInterval;			// 初期カメラと注視点の距離

	DirectX::XMFLOAT4X4 m_WorldMatrix;		//ワールドマトリックス
	DirectX::XMFLOAT4X4 m_ViewMatrix;		//ビューマトリックス
	DirectX::XMFLOAT4X4 m_ProjectionMatrix;	//プロジェクションマトリックス

	float m_AspectRatio;	// アスペクト比
	float m_FovY;			// 視野角
	float m_NearClipZ;		// 前方クリップ距離
	float m_FarClipZ;		// 後方クリップ距離
};