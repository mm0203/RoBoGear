//=============================================================================
// Startup.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Main.h"
#include <windows.h>
#include <stdio.h>
#include <crtdbg.h>
#include <Manager/SceneManager.h>
#include <Resource/resource.h>

// timeGetTime周りの使用
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

#define CLASS_NAME		_T("AppClass")	// ウインドウのクラス名
#define WINDOW_NAME		_T("RoBoGear")	// ウインドウのキャプション名

HWND		g_hWnd;		// メイン ウィンドウ ハンドル
HINSTANCE	g_hInst;	// インスタンス ハンドル

//=============================================================================
// 
// プロトタイプ宣言
// 
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);

//=============================================================================
// 
// スタートアップ
// 
//=============================================================================
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク呼び出し
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 未使用宣言
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

	// COM初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		MessageBox(NULL, _T("COMの初期化に失敗しました。"), _T("error"), MB_OK);
		return -1;
	}

	// インスタンス ハンドル保存
	g_hInst = hInstance;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域サイズからウィンドウ サイズ算出
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// ウィンドウの作成
	g_hWnd = CreateWindowEx(dwExStyle,
		CLASS_NAME,
		WINDOW_NAME,
		dwStyle,
		CW_USEDEFAULT,		// ウィンドウの左座標
		CW_USEDEFAULT,		// ウィンドウの上座標
		rc.right - rc.left,	// ウィンドウ横幅
		rc.bottom - rc.top,	// ウィンドウ縦幅
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if (FAILED(Init(g_hWnd, true)))
		return -1;

	// FPS制御
	timeBeginPeriod(1);
	DWORD countStartTime = timeGetTime();
	DWORD preExecTime = countStartTime;

	// ウィンドウの管理
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
			// 変更先のシーンが設定されていなければスキップ
			CSceneManager::GetInstance().ChangeNextScene();
		}
	}

	// 終了処理
	timeEndPeriod(1);
	Uninit();
	UnregisterClass(CLASS_NAME, g_hInst);

	// COM終了処理
	CoUninitialize();

	return (int)msg.wParam;
}

//=============================================================================
// 
// プロシージャ
// 
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// ウィンドウが生成されたら
	case WM_CREATE:
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);

		// ウィンドウ破棄指示がきたら
	case WM_DESTROY:
		PostQuitMessage(0);	// システムにスレッドの終了を要求
		break;
		// キーボードが押されたら
	case WM_KEYDOWN:
		switch (wParam)
		{
			// [ESC]キーが押されたら
		case VK_ESCAPE:
			PostMessage(hWnd, WM_CLOSE, 0, 0);	// [x]が押されたように振舞う
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;	// [Alt]+[Enter]時のBEEPを抑止
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 
// WM_CREATEメッセージハンドラ
// 
//=============================================================================
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// クライアント領域サイズをSCREEN_WIDTH×SCREEN_HEIGHTに再設定.
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

	// IME無効化
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1を返すとCreateWindow[Ex]が失敗する.
}

// メインウィンドウハンドル取得
HWND GetMainWnd() { return g_hWnd; }
// インスタンスハンドル取得
HINSTANCE GetInstance() { return g_hInst; }
