//=============================================================================
// CPolygon.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "polygon.h"
#include <main.h>
#include <Renderer/Texture/Texture.h>
#include <Renderer/Graphics/Graphics.h>
#include <System/Singleton/singleton.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CPolygon
{
public:
	CPolygon();
	~CPolygon();

	void Init();
	void Draw();

	// �e�N�X�`�����[�h
	HRESULT LoadTexture(const wchar_t* FileName);
	HRESULT LoadTexture(const char* FileName);

public:
	// getter
	XMFLOAT2 GetPos() { return m_Pos; }//���W
	XMFLOAT2 GetSize() { return m_Size; }//�T�C�Y
	float GetAngle() { return m_PolygonAngle; }		// �|���S���̊p�x
	XMFLOAT2 GetUN() { return m_UV; }				// UV���W
	XMFLOAT2 GetFrameSize() { return m_FrameSize; }	// UV�T�C�Y
	XMFLOAT3 GetColor() { return m_Color; }			// �F
	float GetAlpha() { return m_Alpha; }			// ���l

	// setter
	// ���W
	void SetPosition(float X, float Y) { m_Pos = XMFLOAT2(X, Y); }
	void SetPosition(XMFLOAT2 pos) { m_Pos = pos; }
	// �T�C�Y
	void SetSize(float SizeX, float SizeY) { m_Size = XMFLOAT2(SizeX, SizeY); }
	void SetSize(XMFLOAT2 size) { m_Size = size; }
	// �p�x
	void SetAngle(float Angle) { m_PolygonAngle = Angle; }
	// �e�N�X�`�����W
	void SetUV(float U, float V) { m_UV = XMFLOAT2(U, V); }
	void SetUV(XMFLOAT2 uv) { m_UV = uv; }
	// �e�N�X�`���t���[���T�C�Y
	void SetFrameSize(float TexSizeX, float TexSizeY) { m_FrameSize = XMFLOAT2(TexSizeX, TexSizeY); }
	// �F
	void SetColor(float r, float g, float b) { m_Color = XMFLOAT3(r, g, b); }
	void SetColor(XMFLOAT3 color) { m_Color = color; }
	// �s�����x
	void SetAlpha(float Alpha) { m_Alpha = Alpha; }
	void SetRGBA(XMFLOAT4 rgba) { m_Color = XMFLOAT3(rgba.x, rgba.y, rgba.y); m_Alpha = rgba.w; }
	// �e�N�X�`��
	void SetTex(ID3D11ShaderResourceView* tex) { m_pTex = tex; }


private:
	ID3D11ShaderResourceView* m_pTex;	//�e�N�X�`��
	XMFLOAT2 m_Pos;						//���W
	XMFLOAT2 m_Size;					//�T�C�Y
	float m_PolygonAngle;				//�|���S���̊p�x
	XMFLOAT2 m_UV;						//UV���W
	XMFLOAT2 m_FrameSize;				//UV�T�C�Y
	XMFLOAT3 m_Color;					//�F
	float m_Alpha;						//���l
	bool m_isLoadTex = false;
};