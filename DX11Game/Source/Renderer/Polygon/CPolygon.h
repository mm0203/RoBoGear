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
	// �R���X�g���N�^
	CPolygon()
	{
		Init();
	}

	// �f�X�g���N�^
	~CPolygon()
	{ 
		if (m_pTex && m_isLoadTex) SAFE_RELEASE(m_pTex); 
	}

public:
	void Init()
	{
		// �����o�ϐ�������
		m_pTex = nullptr;
		m_Pos = XMFLOAT2(0.0f, 0.0f);
		m_Size = XMFLOAT2(1.0f, 1.0f);
		m_UV = XMFLOAT2(0.0f, 0.0f);
		m_FrameSize = XMFLOAT2(1.0f, 1.0f);
		m_PolygonAngle = 0.0f;
		m_Alpha = 1.0f;
		m_Color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	}
	void Draw()
	{
		Singleton<Graphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_OFF);
		//SetZBuffer(false);
		SetBlendState(BS_ALPHABLEND);
		// �|���S�����Z�b�g
		if (m_pTex != nullptr)	SetPolygonTexture(m_pTex);
		else SetPolygonTexture(nullptr);
		SetPolygonPos(m_Pos.x, m_Pos.y);
		SetPolygonSize(m_Size.x, m_Size.y);
		SetPolygonAngle(m_PolygonAngle);
		SetPolygonUV(m_UV.x, m_UV.y);
		SetPolygonFrameSize(m_FrameSize.x, m_FrameSize.y);
		SetPolygonColor(m_Color.x, m_Color.y, m_Color.z);
		SetPolygonAlpha(m_Alpha);
		// �`��
		DrawPolygon(GetDeviceContext());
		//SetZWrite(true);
		Singleton<Graphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_ON);
		SetBlendState(BS_NONE);
	}
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
	HRESULT LoadTexture(const wchar_t* FileName)	//�e�N�X�`�����[�h
	{
		HRESULT hr = S_OK;
		hr = CreateTextureFromFile(GetDevice(), FileName, &m_pTex);
		m_isLoadTex = true;
		return hr;
	}
	HRESULT LoadTexture(const char* FileName)	//�e�N�X�`�����[�h
	{
		HRESULT hr = S_OK;
		hr = CreateTextureFromFile(GetDevice(), FileName, &m_pTex);
		m_isLoadTex = true;
		return hr;
	}

	void SetPosition(float X, float Y) { m_Pos = XMFLOAT2(X, Y); }	//���W�Z�b�g
	void SetPosition(XMFLOAT2 pos) { m_Pos = pos; }
	void SetSize(float SizeX, float SizeY) { m_Size = XMFLOAT2(SizeX, SizeY); }	//�T�C�Y�Z�b�g
	void SetSize(XMFLOAT2 size) { m_Size = size; }
	void SetAngle(float Angle) { m_PolygonAngle = Angle; }		//�p�x�Z�b�g
	void SetUV(float U, float V) { m_UV = XMFLOAT2(U, V); }		//�e�N�X�`�����W�Z�b�g
	void SetUV(XMFLOAT2 uv) { m_UV = uv; }
	void SetFrameSize(float TexSizeX, float TexSizeY) { m_FrameSize = XMFLOAT2(TexSizeX, TexSizeY); }	//�e�N�X�`���t���[���T�C�Y�Z�b�g
	void SetColor(float r, float g, float b) { m_Color = XMFLOAT3(r, g, b); }	//�F�Z�b�g
	void SetColor(XMFLOAT3 color) { m_Color = color; }
	void SetAlpha(float Alpha) { m_Alpha = Alpha; }		//�A���t�@�l�Z�b�g
	void SetRGBA(XMFLOAT4 rgba) { m_Color = XMFLOAT3(rgba.x, rgba.y, rgba.y); m_Alpha = rgba.w; }
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