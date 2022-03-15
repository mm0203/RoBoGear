//=============================================================================
// CRenderer.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Renderer.h"
#include <Renderer/Texture/Texture.h>
#include <Renderer/Graphics/Graphics.h>
#include <System/Input/input.h>
#include <Manager/GameManager.h>
#include <time.h>

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
double CRenderer::m_dAnimeTime;
std::map<const std::string, CAssimpModel*, std::less<>> CRenderer::m_ModelPool;
std::map<const CAssimpModel*, TAssimpMaterial*, std::less<>> CRenderer::m_MaterialPool;

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CRenderer::CRenderer()
{
	m_pModel = nullptr;
	m_nAnimeNo = 0;
	m_filename = "\0";
	m_pTexture = nullptr;
	m_dAnimeTime = 0.0f;
}

//=============================================================================
// 
// テクスチャセット
// 
//=============================================================================
void CRenderer::SetTexture(const char* filename)
{
	m_pTexture = CTexture::GetTexture(GetDevice(), filename);
}

//=============================================================================
// 
// テクスチャセット
// 
//=============================================================================
void CRenderer::SetTexture(const wchar_t* filename)
{
	m_pTexture = CTexture::GetTexture(GetDevice(), filename);
}

//=============================================================================
// 
// マテリアル取得
// 
//=============================================================================
TAssimpMaterial* CRenderer::GetMaterial()
{
	// モデルがなかったら
	if (!m_pModel) return nullptr;

	if (m_pModel->GetMaterial()) return m_pModel->GetMaterial();

	// マテリアル検索
	const auto& itr = m_MaterialPool.find(m_pModel);

	// マテリアルがプールにあったら
	if (m_MaterialPool.end() != itr)
		return itr->second;

	// 新規作成
	auto pMat = new TAssimpMaterial();

	// モデルに格納
	m_pModel->SetMaterial(pMat);

	// プールに格納
	m_MaterialPool.emplace(m_pModel, pMat);

	return pMat;
}

//=============================================================================
// 
// モデル読み込み
// 
//=============================================================================
bool CRenderer::LoadModel(const char* FileName)
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// プールから検索
	const auto& itr = m_ModelPool.find(FileName);

	// 既にプールにあったら
	if (m_ModelPool.end() != itr)
	{
		m_pModel = itr->second;
		m_filename = FileName;
		//m_pTexture = GetMaterial()->pTexture;
		return true;
	}

	// プールになければ生成
	const auto& am = new CAssimpModel();

	// モデルのロード
	bool b = am->Load(pDevice, pDC, FileName);

	// プールに登録
	m_ModelPool.emplace(FileName, am);

	// 格納
	m_pModel = am;
	m_filename = FileName;
	//m_pTexture = GetMaterial()->pTexture;

	// カメラとライトをセット
	m_pModel->SetLight(&CSingleton<CLight>::GetInstance());
	m_pModel->SetCamera(&CSingleton<CCamera>::GetInstance());

	return b;
}

//=============================================================================
// 
// モデル解放
// 
//=============================================================================
void CRenderer::ReleaseModel()
{
	const auto& itr = m_ModelPool.find(m_filename);

	// プールにあったら
	if (m_ModelPool.end() != itr)
	{
		//itr->second->Release();
		m_pModel->Release();	 // モデルをリリース
		m_ModelPool.erase(itr);	 // 要素を削除
		delete m_pModel;
	}

	// モデル情報を空に
	if (m_pModel)
	{
		m_pModel = nullptr;
		m_filename = "\0";
	}
}

//=============================================================================
// 
// モデル全開放
// 
//=============================================================================
void CRenderer::ReleaseModelAll()
{
	// インスタンスの数を取得
	int ModelCount = (int)m_ModelPool.size();

	// リスト内のインスタンスを削除
	for (int i = 0; i < ModelCount; i++)
	{
		const auto& it = m_ModelPool.begin();
		//it->first = "\0";
		it->second->Release();	// モデルをリリース
		delete it->second;		// 要素の中身を削除
		it->second = nullptr;
		m_ModelPool.erase(it);  // 要素を削除
	}
	// モデル情報を空に
	if (m_pModel)
	{
		m_pModel = nullptr;
		m_filename = "\0";
	}
}

//=============================================================================
// 
// モデル描画
// 
//=============================================================================
void CRenderer::Draw(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	static XMFLOAT4X4	g_mtxWorld;
	XMMATRIX mtxWorld, mtxRot, mtxTranslate, mtxScale;

	mtxWorld = XMMatrixIdentity();

	// サイズ
	mtxScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScale);
	// 回転
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(rot.x), XMConvertToRadians(rot.y), XMConvertToRadians(rot.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
	// 移動
	mtxTranslate = XMMatrixTranslation(pos.x, pos.y, pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
	XMStoreFloat4x4(&g_mtxWorld, mtxWorld);

	// 不透明度切り替え
	//m_pModel->DrawShadow(pDC, g_mtxWorld, eOpacityOnly, true);

	// モデル表示
	m_pModel->Draw(pDC, g_mtxWorld, false, eNoAffect);

	// デバッグモードでX押したらアウトライン非表示
	bool outline = false;
	if (CGameManager::GetDebug() && GetKeyPress(VK_X)) outline ^= 1;

	// アウトライン表示
	if(!outline)
	m_pModel->Draw(pDC, g_mtxWorld, true, eNoAffect);

	// アニメーション
	DrawAnime();
}


//=============================================================================
// 
// アニメ再生時間
// 
//=============================================================================
void CRenderer::AnimePlayTime()
{
	// 時間を取得
	static double LastAnimTime = clock() / double(CLOCKS_PER_SEC);
	double m_dCurrent = clock() / double(CLOCKS_PER_SEC);

	// 最終の更新された時間と現在の時間の差分を取得
	double dSlice = m_dCurrent - LastAnimTime;
	LastAnimTime = m_dCurrent;

	// 差分を加算して時間を増やしていく
	m_dAnimeTime += dSlice;
}

//=============================================================================
// 
// アニメ切り替え
// 
//=============================================================================
void CRenderer::AnimeChange(int AnimeNo, double AnimeSpeed)
{
	// アニメの終了時間
	double AnimeEndTime = m_pModel->GetAnimDuration(m_nAnimeNo);

	// 時間に応じてアニメ切り替え
	if (m_dAnimeTime >= AnimeEndTime / AnimeSpeed)
		m_nAnimeNo = AnimeNo;
}

//=============================================================================
// 
// アニメ描画
// 
//=============================================================================
void CRenderer::DrawAnime()
{
	// 指定したアニメーションNo
	m_pModel->SetAnimIndex(m_nAnimeNo);
	// アニメーション再生時間
	m_pModel->SetAnimTime(m_dAnimeTime);	
}