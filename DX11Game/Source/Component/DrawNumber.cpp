//=============================================================================
// Number.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "DrawNumber.h"
#include <System/Message/Message.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const auto NumberFrameX = 10; // ���t���[����
	const auto NumberFrameY = 1;  // �c�t���[����

	// UV�𕪊�
	constexpr float NumberFrameSizeX = 1.0f / NumberFrameX;
	constexpr float NumberFrameSizeY = 1.0f / NumberFrameY;

	const int DigitCheck = 10;	  // �����̔���
	const float DigitPos = 80.0f; // �����̏ꏊ

	const XMFLOAT2 size = XMFLOAT2(80.0f, 110.0f); // �T�C�Y
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CNumber::CNumber()
{
	m_nNumber = 0;
	m_Pos = XMFLOAT2();
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CNumber::Init(const wchar_t* FileName)
{
	m_Polygon.SetSize(size);
	m_Polygon.SetFrameSize(NumberFrameSizeX, NumberFrameSizeY);	// UV��10����
	m_Polygon.LoadTexture(FileName);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CNumber::Uninit()
{
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CNumber::Update()
{
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CNumber::Draw(int Number, XMFLOAT2 pos)
{
	int nNumber = m_nNumber = Number;
	m_Pos = pos;
	for (int i = 0; i <= nNumber; ++i)
	{
		m_Polygon.SetPosition(m_Pos.x, m_Pos.y);

		// �ꌅ�ɂȂ����璆����
		if (m_nNumber < DigitCheck)
		{
			m_Pos.x -= DigitPos / 2;
			m_Polygon.SetPosition(m_Pos.x, m_Pos.y);
		}
		// UV���W���Z�b�g
		unsigned n = nNumber % NumberFrameX;
		nNumber /= NumberFrameX;
		int u = n % NumberFrameX;
		int v = n / NumberFrameX;
		m_Polygon.SetUV(u / (float)NumberFrameX, v / (float)NumberFrameY);

		// �����̈ʒu�����炷
		m_Pos.x -= DigitPos;
		m_Polygon.Draw();
	}
}