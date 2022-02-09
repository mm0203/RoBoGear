//=============================================================================
// TitleMenuChoices.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TitleMenuChoices.h"
#include <Scene/Title/TitleScene.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	// �e�I�����̃e�N�X�`��
	const auto TitleMenuStart = L"data/texture/Title/Start.png";
	const auto TitleMenuEdit  = L"data/texture/Title/Edit.png";
	const auto TitleMenuExit  = L"data/texture/Title/Exit.png";
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CTitleMenuChoices::CTitleMenuChoices()
{
	m_TextureColor = std::make_unique<CTextureColorChangeComponent>();
}
//=============================================================================
// 
// ����������
// 
//=============================================================================
void CTitleMenuChoices::Init()
{

	m_Polygons.resize(eTitle_Max);

	XMFLOAT2 size = XMFLOAT2(640, 80.0f);

	for (int i = 0; i < eTitle_Max; i++)
	{
		m_Polygons[i].SetPosition(0.0f, 20.0f - (i * 90.0f));
		m_Polygons[i].SetSize(size);
	}
	// �X�^�[�g
	m_Polygons[eTitle_Start].LoadTexture(TitleMenuStart);
	m_Polygons[eTitle_Edit].LoadTexture(TitleMenuEdit);
	m_Polygons[eTitle_Exit].LoadTexture(TitleMenuExit);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CTitleMenuChoices::Uninit()
{
	m_Polygons.clear();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CTitleMenuChoices::Update()
{
}

//=============================================================================
// 
// �����t���X�V����
// 
//=============================================================================
void CTitleMenuChoices::MenuChoices(int index)
{
	// �I���e�L�X�g�F�ύX
	float color = m_TextureColor->ColorChange();

	for (int i = 0; i < eTitle_Max; i++)
	{
		if (i == index)
			m_Polygons[i].SetColor(1.0f, 1.0f, color);
		else
			m_Polygons[i].SetColor(1.0f, 1.0f, 1.0f);
	}
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CTitleMenuChoices::Draw()
{
	// �e�N�X�`���`��
	for (int i = 0; i < eTitle_Max; i++)
		m_Polygons[i].Draw();
}