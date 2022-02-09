//=============================================================================
// debugproc.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include <stdarg.h>
#include <string.h>
#include "debugproc.h"
#include <Renderer/Polygon/Polygon.h>
#include <Renderer/Texture/Texture.h>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================
#define	TEXTURE_FILENAME	L"data/TEXTURE/PressStart2Ph_e.tga"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define FONT_WIDTH			16
#define FONT_HEIGHT			16

//=============================================================================
// 
// �O���[�o���ϐ�
// 
//=============================================================================
static ID3D11ShaderResourceView*	g_pTexture;					// �e�N�X�`���ւ̃|�C���^
static char							g_szDebug[8192] = { '\0' };	// �f�o�b�O���
static bool							g_bHiragana = false;		// �������t���O

//=============================================================================
// 
// ����������
// 
//=============================================================================
HRESULT InitDebugProc(void)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = S_OK;

	// �e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice, TEXTURE_FILENAME, &g_pTexture);

	return hr;
}

//=============================================================================
// 
// �f�o�b�O�\�������̏I������
// 
//=============================================================================
void UninitDebugProc(void)
{
	// �e�N�X�`����@
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// 
// �f�o�b�O�\�������̍X�V����
// 
//=============================================================================
void UpdateDebugProc(void)
{
}

//=============================================================================
// 
// �f�o�b�O�\�������̕`�揈��
// 
//=============================================================================
void DrawDebugProc(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMFLOAT2 vPos(SCREEN_WIDTH * -0.5f + FONT_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - FONT_HEIGHT * 0.5f);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(8.0f / 128.0f, 8.0f / 128.0f);
	SetPolygonSize(FONT_WIDTH, FONT_HEIGHT);
	for (char* pChr = &g_szDebug[0]; *pChr; ++pChr) 
	{
		if (*pChr == '\n') 
		{
			vPos.x = SCREEN_WIDTH * -0.5f + FONT_WIDTH * 0.5f;
			vPos.y -= FONT_HEIGHT;
			continue;
		}
		SetPolygonPos(vPos.x, vPos.y);
		int nChr = (BYTE)*pChr;
		if (g_bHiragana &&
			(nChr >= 0xa6 && nChr <= 0xaf || nChr >= 0xb1 && nChr <= 0xdd))
			nChr ^= 0x20;
		SetPolygonUV((nChr & 15) / 16.0f, (nChr >> 4) / 16.0f);
		UpdatePolygon();
		DrawPolygon(pDeviceContext);
		vPos.x += FONT_WIDTH;
	}
	// �e�N�X�`���ݒ�����ɖ߂�
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	SetPolygonAlpha(1.0f);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
}

//=============================================================================
// 
// �f�o�b�O�\���̓o�^�J�n
// 
//=============================================================================
void StartDebugProc(bool hiragana)
{
	SetHiragana(hiragana);
	g_szDebug[0] = '\0';
}

//=============================================================================
// 
// �f�o�b�O�\���̓o�^
// 
//=============================================================================
void PrintDebugProc(const char *fmt, ...)
{
	va_list list;
	char aBuf[256];

	va_start(list, fmt);
	_vsprintf_p(aBuf, sizeof(aBuf), fmt, list);
	va_end(list);

	// �A��
	if ((strlen(g_szDebug) + strlen(aBuf)) < sizeof(g_szDebug) - 1)
	{
		strcat_s(g_szDebug, sizeof(g_szDebug), aBuf);
	}
}

//=============================================================================
// 
// �Ђ炪��(���g�p)
// 
//=============================================================================
bool SetHiragana(bool hiragana)
{
	bool prev = g_bHiragana;
	g_bHiragana = hiragana;
	return prev;
}
