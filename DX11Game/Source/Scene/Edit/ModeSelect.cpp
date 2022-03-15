//=============================================================================
// CModeSelect.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "ModeSelect.h"
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Message/Message.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const XMFLOAT3 CursorColor = XMFLOAT3(0.0f, 0.8f, 0.9f);	// カーソル色
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CModeSelect::CModeSelect()
{
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CModeSelect::Init()
{
	// ポリゴン初期設定
	m_Polygon.LoadTexture(L"data/texture/Edit/Cursor01.png");
	m_Polygon.SetPosition(400, 300);
	m_Polygon.SetSize(40, 40);
	m_Polygon.SetColor(CursorColor);

	// テキスト描画
	CMessageManager::CreateMessage("CREATE",   XMFLOAT2(440.0f, 300.0f));
	CMessageManager::CreateMessage("DELETE",   XMFLOAT2(440.0f, 250.0f));
	CMessageManager::CreateMessage("SET STEP", XMFLOAT2(440.0f, 200.0f));
	CMessageManager::CreateMessage("SAVE",     XMFLOAT2(440.0f, 150.0f));
	CMessageManager::CreateMessage("LOAD",     XMFLOAT2(440.0f, 100.0f));
	CMessageManager::CreateMessage("TITLE",    XMFLOAT2(440.0f, 50.0f));
	CMessageManager::CreateMessage("GAME",     XMFLOAT2(440.0f, 0.0f));
	CMessageManager::CreateMessage("STEP",     XMFLOAT2(485.0f, -75.0f));
	CMessageManager::CreateMessage("STAGE NO", XMFLOAT2(435.0f, -225.0f));
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CModeSelect::Uninit()
{
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CModeSelect::Update(int& index,int ModeNum)
{
	// 下
	if (GetKeyTrigger(VK_UP))
	{
		// カーソルSE
		CSound::Play(SE_CURSORMOVE);

		index--;
		// 最小を超えたら最大に
		if (index < 0) index += ModeNum;

		// 矢印の位置を変更
		XMFLOAT2 pos = m_Polygon.GetPos();
		pos.y = index * -50.0f + 300.0f;
		m_Polygon.SetPosition(pos);
		//CSound::Play(SE_Cursor);
	}
	// 上
	if (GetKeyTrigger(VK_DOWN))
	{
		// カーソルSE
		CSound::Play(SE_CURSORMOVE);

		index++;
		// 最大を超えたら最小に
		if (index > ModeNum - 1) index -= ModeNum;

		// 矢印の位置を変更
		XMFLOAT2 pos = m_Polygon.GetPos();
		pos.y = index * -50.0f + 300.0f;
		m_Polygon.SetPosition(pos);
	}

	PrintDebugProc("[CurrentCursor] = %d\n", index);

	// 選択しているメッセージの色を変更	
	int num = 0;
	std::vector<CMessage*> List = CMessageManager::GetActiveList();
	for (auto it : List)
	{
		// 引数から現在の選択肢を取得
		if (num == index)
			it->SetColor(CursorColor);
		else 
			it->SetColor({ 1.0f,1.0f,1.0f });
		num++;
		if (num == ModeNum) break;
	}
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CModeSelect::Draw()
{
	m_Polygon.Draw();
}