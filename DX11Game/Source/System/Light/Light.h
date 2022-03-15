//=============================================================================
// Light.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once
#include <main.h>
#include "../Singleton/singleton.h"
#include <System/Camera/Camera.h>
#include <System/Singleton/singleton.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CLight : public CSingleton<CLight>
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
	// 光源方向
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

	// シングルトンのみでインスタンス生成を許可
	friend class CSingleton;

	CLight() = default;
	~CLight() = default;

	XMFLOAT3 m_direction; // 光の方向
	XMFLOAT4 m_diffuse;	  // 拡散色 + アルファ
	XMFLOAT4 m_ambient;	  // 環境色
	XMFLOAT4 m_specular;  // 鏡面反射色+強度
	XMFLOAT3 m_vPos;	  // 視点
	XMFLOAT3 m_vTarget;	  // 注視点
	XMFLOAT3 m_vUp;		  // 上方ベクトル
	XMFLOAT4X4 m_ProjMatrix;	//プロジェクションマトリックス
	XMFLOAT4X4 m_ViewView; // ビューマトリックス
	bool m_bEnable;

};
