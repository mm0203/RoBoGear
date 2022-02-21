//=============================================================================
// MeSsageManager.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Message.h"
#include <System/Debug/debugproc.h>
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
std::vector<Message*> MessageManager::m_ActiveList;
std::vector<Message*> MessageManager::m_UnusedList;
std::vector<Message*> MessageManager::m_DeleteList;
ID3D11ShaderResourceView* MessageManager::m_pFont = nullptr;

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void MessageManager::Init()
{
	// フォント読み込み
	CreateTextureFromFile(GetDevice(), L"data/texture/EngFont.png", &m_pFont);

	// オブジェクト作成
	MessageManager::CreateObject();
}
//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void MessageManager::Uninit()
{
	// 各リストのオブジェクト破棄
	int num = (int)m_ActiveList.size();
	for (int i = 0; i < num; i++)
	{
		Message* p;
		p = *(m_ActiveList.begin());
		p->Uninit();
		m_ActiveList.erase(m_ActiveList.begin());
		delete p;
	}
	num = (int)m_UnusedList.size();
	for (int i = 0; i < num; i++)
	{
		Message* p;
		p = *(m_UnusedList.begin());
		p->Uninit();
		m_UnusedList.erase(m_UnusedList.begin());
		delete p;
	}

	SAFE_RELEASE(m_pFont);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void MessageManager::Update()
{
	// オブジェクト更新
	for (auto it : m_ActiveList)
		it->Update();
	// リスト更新
	MessageManager::UpdateObject();
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void MessageManager::Draw()
{
	// オブジェクト描画
	for (auto it : m_ActiveList)
		it->Draw();
}

//=============================================================================
// 
// メッセージ生成処理
// 
//=============================================================================
void MessageManager::CreateMessage(const char* message, XMFLOAT2 pos, int Mag, XMFLOAT3 Color)
{
	Message obj;
	strcpy(obj.m_Message, message);
	obj.m_MessagePos = pos;
	obj.SetFrameSize(FontFrameSizeX, FontFrameSizeY);
	obj.SetSize(FontSizeX * Mag, FontSizeY * Mag);
	obj.SetColor(Color);
	obj.m_Mag = Mag;
	obj.SetTex(m_pFont);
	MessageManager::AddObject(obj);
}

//=============================================================================
// 
// 削除処理
// 
//=============================================================================
void MessageManager::DeleteObject(Message* pObj)
{
	// DeleteListに登録
	m_DeleteList.push_back(pObj);
}

//=============================================================================
// 
// オブジェクト追加
// 
//=============================================================================
void MessageManager::AddObject(Message obj)
{
	// 登録用オブジェクト
	Message* pObj;
	// 未使用オブジェクトが無ければエラー
	if (m_UnusedList.empty())
	{
		MessageBoxA(GetMainWnd(), "メッセージオブジェクトが足りない", "ObjectNothing", MB_OK);
		return;
	}
	// 未使用リストからオブジェクトを取り出す
	pObj = *m_UnusedList.begin();

	// 未使用リスト更新
	m_UnusedList.erase(m_UnusedList.begin());

	// オブジェクトの中身をコピー
	*pObj = obj;

	// アクティブリストに登録
	m_ActiveList.push_back(pObj);
}

//=============================================================================
// 
// オブジェクト更新
// 
//=============================================================================
void MessageManager::UpdateObject()
{
	// 空の場合スキップ
	if (m_DeleteList.empty()) return;

	for (auto it : m_DeleteList)
	{
		int num = 0;
		// アクティブリストから検索
		for (auto ite : m_ActiveList)
		{
			if (it == ite)
			{
				// ポインタをゲット
				Message* pObj = ite;

				// アクティブリストから削除
				m_ActiveList.erase(m_ActiveList.begin() + num);

				// 未使用リストに追加
				m_UnusedList.push_back(pObj);

				break;
			}
			num++;
		}
	}
	// 削除リストクリア
	m_DeleteList.clear();
}

//=============================================================================
// 
// オブジェクト生成
// 
//=============================================================================
void MessageManager::CreateObject(int num)
{
	// オブジェクト作成
	for (int i = 0; i < num; i++)
	{
		Message* pObj = new Message;
		// 未使用リストに登録
		m_UnusedList.push_back(pObj);
	}
}
