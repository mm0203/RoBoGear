//=============================================================================
// CPauseMenuChoices.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "PauseMenuChoices.h"
#include <Scene/Pause/PauseMenu.h>

#define PAUSE_CONTINUE  "data/Texture/Pause/Continue.png"
#define PAUSE_RETRY		"data/texture/Pause/retry.png"
#define PAUSE_SELECT	"data/TEXTURE/Pause/Select.png"
#define PAUSE_TITLE		"data/TEXTURE/Pause/PauseTitle.png"

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const auto PauseContinue = L"data/Texture/Pause/Continue.png";
	const auto PauseRetry= L"data/texture/Pause/retry.png";
	const auto PauseSelect = L"data/TEXTURE/Pause/Select.png";
	const auto PauseTitle = L"data/TEXTURE/Pause/PauseTitle.png";
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CPauseMenuChoices::CPauseMenuChoices()
{
	m_TextureColor = std::make_shared<CTextureColorChangeComponent>();
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CPauseMenuChoices::Init()
{
	m_Polygons.resize(ePauseMenuMax);

	XMFLOAT2 size = XMFLOAT2(640, 80.0f);

	// �ʒu�@�T�C�Y
	for (int i = 0; i < ePauseMenuMax; i++)
	{
		m_Polygons[i].SetSize(size);
		m_Polygons[i].SetPosition(0.0f, 100.0f - (i * 100.0f));
	}

	// �e�N�X�`���ǂݍ���
	m_Polygons[ePause_Continue].LoadTexture(PauseContinue);
	m_Polygons[ePause_Retry].LoadTexture(PauseRetry);
	m_Polygons[ePause_StageSelect].LoadTexture(PauseSelect);
	m_Polygons[ePause_Title].LoadTexture(PauseTitle);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CPauseMenuChoices::Uninit()
{
	m_Polygons.clear();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CPauseMenuChoices::Update()
{
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CPauseMenuChoices::Draw()
{
	for (int i = 0; i < ePauseMenuMax; i++)
		m_Polygons[i].Draw();
}

//=============================================================================
// 
// �F�ύX
// 
//=============================================================================
void CPauseMenuChoices::ColorChange(int index)
{
	// �I���e�L�X�g�F�ύX
	float color = m_TextureColor->ColorChange();

	for (int i = 0; i < ePauseMenuMax; i++)
	{
		if (i == index)
			m_Polygons[i].SetColor(1.0f, 1.0f, color);
		else
			m_Polygons[i].SetColor(1.0f, 1.0f, 1.0f);
	}
}