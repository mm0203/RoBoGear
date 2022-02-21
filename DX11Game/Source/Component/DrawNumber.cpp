//=============================================================================
// Number.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "DrawNumber.h"
#include <System/Message/Message.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const auto NumberFrameX = 10; // 横フレーム数
	const auto NumberFrameY = 1;  // 縦フレーム数

	// UVを分割
	constexpr float NumberFrameSizeX = 1.0f / NumberFrameX;
	constexpr float NumberFrameSizeY = 1.0f / NumberFrameY;

	const int DigitCheck = 10;	  // 桁数の判定
	const float DigitPos = 80.0f; // 桁数の場所

	const XMFLOAT2 size = XMFLOAT2(80.0f, 110.0f); // サイズ
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CNumber::CNumber()
{
	m_nNumber = 0;
	m_Pos = XMFLOAT2();
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CNumber::Init(const wchar_t* FileName)
{
	m_Polygon.SetSize(size);
	m_Polygon.SetFrameSize(NumberFrameSizeX, NumberFrameSizeY);	// UVを10分割
	m_Polygon.LoadTexture(FileName);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CNumber::Uninit()
{
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CNumber::Update()
{
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CNumber::Draw(int Number, XMFLOAT2 pos)
{
	int nNumber = m_nNumber = Number;
	m_Pos = pos;
	for (int i = 0; i <= nNumber; ++i)
	{
		m_Polygon.SetPosition(m_Pos.x, m_Pos.y);

		// 一桁になったら中央に
		if (m_nNumber < DigitCheck)
		{
			m_Pos.x -= DigitPos / 2;
			m_Polygon.SetPosition(m_Pos.x, m_Pos.y);
		}
		// UV座標をセット
		unsigned n = nNumber % NumberFrameX;
		nNumber /= NumberFrameX;
		int u = n % NumberFrameX;
		int v = n / NumberFrameX;
		m_Polygon.SetUV(u / (float)NumberFrameX, v / (float)NumberFrameY);

		// 桁数の位置をずらす
		m_Pos.x -= DigitPos;
		m_Polygon.Draw();
	}
}