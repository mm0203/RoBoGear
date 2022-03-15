//=============================================================================
// Startup.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "Main.h"
#include <windows.h>
#include <stdio.h>
#include <crtdbg.h>
#include <Manager/SceneManager.h>
#include <Resource/resource.h>

// timeGetTime����̎g�p
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

#define CLASS_NAME		_T("AppClass")	// �E�C���h�E�̃N���X��
#define WINDOW_NAME		_T("RoBoGear")	// �E�C���h�E�̃L���v�V������

HWND		g_hWnd;		// ���C�� �E�B���h�E �n���h��
HINSTANCE	g_hInst;	// �C���X�^���X �n���h��

//=============================================================================
// 
// �v���g�^�C�v�錾
// 
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);

//=============================================================================
// 
// �X�^�[�g�A�b�v
// 
//=============================================================================
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// ���������[�N�Ăяo��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ���g�p�錾
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		nullptr,
		CLASS_NAME,
		nullptr
	};
	MSG msg;

	// COM������
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		MessageBox(NULL, _T("COM�̏������Ɏ��s���܂����B"), _T("error"), MB_OK);
		return -1;
	}

	// �C���X�^���X �n���h���ۑ�
	g_hInst = hInstance;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈�T�C�Y����E�B���h�E �T�C�Y�Z�o
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// �E�B���h�E�̍쐬
	g_hWnd = CreateWindowEx(dwExStyle,
		CLASS_NAME,
		WINDOW_NAME,
		dwStyle,
		CW_USEDEFAULT,		// �E�B���h�E�̍����W
		CW_USEDEFAULT,		// �E�B���h�E�̏���W
		rc.right - rc.left,	// �E�B���h�E����
		rc.bottom - rc.top,	// �E�B���h�E�c��
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(g_hWnd, true)))
		return -1;

	// FPS����
	timeBeginPeriod(1);
	DWORD countStartTime = timeGetTime();
	DWORD preExecTime = countStartTime;

	// �E�B���h�E�̊Ǘ�
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			DWORD nowTime = timeGetTime();
			if (nowTime - preExecTime >= 1000 / 60)
			{
				Update();
				Draw();
				preExecTime = nowTime;
			}
			// �ύX��̃V�[�����ݒ肳��Ă��Ȃ���΃X�L�b�v
			CSceneManager::GetInstance().ChangeNextScene();
		}
	}

	// �I������
	timeEndPeriod(1);
	Uninit();
	UnregisterClass(CLASS_NAME, g_hInst);

	// COM�I������
	CoUninitialize();

	return (int)msg.wParam;
}

//=============================================================================
// 
// �v���V�[�W��
// 
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// �E�B���h�E���������ꂽ��
	case WM_CREATE:
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);

		// �E�B���h�E�j���w����������
	case WM_DESTROY:
		PostQuitMessage(0);	// �V�X�e���ɃX���b�h�̏I����v��
		break;
		// �L�[�{�[�h�������ꂽ��
	case WM_KEYDOWN:
		switch (wParam)
		{
			// [ESC]�L�[�������ꂽ��
		case VK_ESCAPE:
			PostMessage(hWnd, WM_CLOSE, 0, 0);	// [x]�������ꂽ�悤�ɐU����
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;	// [Alt]+[Enter]����BEEP��}�~
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 
// WM_CREATE���b�Z�[�W�n���h��
// 
//=============================================================================
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// �N���C�A���g�̈�T�C�Y��SCREEN_WIDTH�~SCREEN_HEIGHT�ɍĐݒ�.
	RECT rcClnt;
	GetClientRect(hWnd, &rcClnt);
	rcClnt.right -= rcClnt.left;
	rcClnt.bottom -= rcClnt.top;
	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT)
	{
		RECT rcWnd;
		GetWindowRect(hWnd, &rcWnd);
		SIZE sizeWnd;
		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	// IME������
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1��Ԃ���CreateWindow[Ex]�����s����.
}

// ���C���E�B���h�E�n���h���擾
HWND GetMainWnd() { return g_hWnd; }
// �C���X�^���X�n���h���擾
HINSTANCE GetInstance() { return g_hInst; }
