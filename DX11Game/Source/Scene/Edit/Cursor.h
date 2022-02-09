//=============================================================================
// Cursor.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once
#include <main.h>
#include <Renderer/Renderer.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CCursor
{
public:
	CCursor();
	~CCursor() = default;

	void Init();
	void Update(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot);
	void Draw();
	void Uninit();

private:
	CRenderer m_Model;
	XMFLOAT3 m_Pos;
	XMFLOAT3 m_Scale;
	XMFLOAT3 m_Rot;
};



