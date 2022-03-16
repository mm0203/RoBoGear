//=============================================================================
// CEffectManager.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Effect.h"
#include <Manager/Object.h>
#include <System/Debug/debugproc.h>

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
std::vector<CEffect*> CEffectManager::m_ActiveList;
std::vector<CEffect*> CEffectManager::m_UnusedList;
std::vector<CEffect*> CEffectManager::m_DeleteList;

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CEffectManager::Init()
{
	// オブジェクト作成
	CEffectManager::CreateObject(99);

}
//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CEffectManager::Uninit()
{
	// 各リストのオブジェクト削除
	int num = (int)m_ActiveList.size();

	for (int i = 0; i < num; i++)
	{
		CEffect* p;						//削除用ポインタ
		p = *(m_ActiveList.begin());	//要素のポインタ
		p->Uninit();					//終了処理を呼ぶ
		m_ActiveList.erase(m_ActiveList.begin());	//リストから削除
		delete p;						//インスタンス削除
	}

	// 未使用リストのオブジェクト削除
	num = (int)m_UnusedList.size();

	for (int i = 0; i < num; i++)
	{
		CEffect* p;						//削除用ポインタ
		p = *(m_UnusedList.begin());	//要素のポインタ
		p->Uninit();					//終了処理を呼ぶ
		m_UnusedList.erase(m_UnusedList.begin());	//リストから削除
		delete p;						//インスタンス削除
	}
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CEffectManager::Update(GameState state)
{
	// オブジェクト更新
	for (auto it : m_ActiveList)
		it->Update();

	// リスト更新
	CEffectManager::UpdateObject();
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CEffectManager::Draw(GameState state)
{
	// オブジェクト描画
	for (auto it : m_ActiveList)
		it->Draw();
}

//=============================================================================
// 
// エフェクト生成
// 
//=============================================================================
void CEffectManager::CreateEffect(EffectID ID, XMFLOAT3 pos)
{
	CEffect obj;

	// 座標をちょっと上げて見えやすいように
	pos.y += 50.0f;

	// 各IDでエフェクトを登録
	switch (ID)
	{
	case Effect_GimicBreak:
		obj.Init();
		obj.m_FrameNum = { 5,3 };
		obj.m_MaxAnimNum = 15;
		obj.m_Speed = 5;
		obj.SetPosition(pos);
		obj.SetSize(75.0f, 75.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/GimicBreak.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case Effect_KeyBreak:
		obj.Init();
		obj.m_FrameNum = { 6,1 };
		obj.m_MaxAnimNum = 6;
		obj.m_Speed = 3;
		obj.SetPosition(pos);
		obj.SetSize(100.0f, 100.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/KeyBreak.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case Effect_PlayerMove:
		obj.Init();
		obj.m_FrameNum = { 4,1 };
		obj.m_MaxAnimNum = 4;
		obj.m_Speed = 3;
		obj.SetPosition(pos);
		obj.SetSize(50.0f, 50.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/PlayerMove.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case Effect_CubeMove:
		obj.Init();
		obj.m_FrameNum = { 8,1 };
		obj.m_MaxAnimNum = 8;
		obj.m_Speed = 2;
		obj.SetPosition(pos);
		obj.SetSize(100.0f, 100.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/CubeMove.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case Effect_Trap:
		obj.Init();
		obj.m_FrameNum = { 8,1 };
		obj.m_MaxAnimNum = 8;
		obj.m_Speed = 3;
		obj.SetPosition(pos);
		obj.SetSize(100.0f, 100.0f);
		obj.SetBillFrameNum(obj.m_FrameNum);
		obj.LoadBillTexture("data/texture/effect/Trap.png");
		obj.SetBillDiffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		break;


	default:
		break;
	}

	// 初期化
	obj.m_CurrentAnimNum = 0;
	obj.m_SpeedCount = 0;

	CEffectManager::AddObject(obj);
}

//=============================================================================
// 
// エフェクト削除
// 
//=============================================================================
void CEffectManager::DeleteObject(CEffect* pObj)
{
	// DeleteListに登録
	m_DeleteList.push_back(pObj);
}

//=============================================================================
// 
// エフェクトのオブジェクト追加
// 
//=============================================================================
void CEffectManager::AddObject(CEffect obj)
{
	// 登録用オブジェクト
	CEffect* pObj;
	// 未使用オブジェクトが無ければエラー
	if (m_UnusedList.empty())
	{
		MessageBoxA(GetMainWnd(), "エフェクトオブジェクトが足りない", "ObjectNothing", MB_OK);
		return;
	}

	// 未使用リストからオブジェクトを取り出す
	pObj = *m_UnusedList.begin();

	// 未使用リスト更新
	m_UnusedList.erase(m_UnusedList.begin());

	// オブジェクトの中身をコピー
	*pObj = obj;
	//*pObj->m_BillMesh.m_pTexture = *obj.m_BillMesh.m_pTexture;

	// 生成したエフェクトを渡す
	ID3D11ShaderResourceView* pTexture = &pObj->m_BillMesh.GetTexture();
	ID3D11ShaderResourceView* pAddTexture = &obj.m_BillMesh.GetTexture();
	pTexture = pAddTexture;

	// アクティブリストに登録
	m_ActiveList.push_back(pObj);
}

//=============================================================================
// 
// エフェクトのオブジェクト更新
// 
//=============================================================================
void CEffectManager::UpdateObject()
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
				CEffect* pObj = ite;
				pObj->Uninit();
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
// エフェクトのオブジェクト作成
// 
//=============================================================================
void CEffectManager::CreateObject(int num)
{
	// オブジェクト作成
	for (int i = 0; i < num; i++)
	{
		CEffect* pObj = new CEffect;
		// 未使用リストに登録
		m_UnusedList.push_back(pObj);
	}
}


