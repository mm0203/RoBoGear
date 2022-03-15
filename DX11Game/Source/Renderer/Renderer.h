//=============================================================================
// CRenderer.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Renderer/Assimp/AssimpModel.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CRenderer
{
public:
	CRenderer();
	~CRenderer() = default;

	// getter
	int GetAnimeNo() { return m_nAnimeNo; }
	static double GetAnimeTime() { return m_dAnimeTime; }

	// setter
	void SetAnimeNo(int AnimeNo) { m_nAnimeNo = AnimeNo; }
	static void SetAnimeTime(double AnimTime) { m_dAnimeTime = AnimTime; }

	// テクスチャセット
	void SetTexture(const char* filename);
	void SetTexture(const wchar_t* filename);
	// マテリアル取得
	TAssimpMaterial* GetMaterial();
	 // アニメ再生時間取得
	static void AnimePlayTime();
	// アニメ描画
	void DrawAnime();
	// アニメ変更(アニメNo, 再生速度)
	void AnimeChange(int AnimeNo, double AnimeSpeed = 1.0f); 
	// モデル読み込み
	bool LoadModel(const char* FileName);
	// モデル開放
	void ReleaseModel();
	// モデル一括開放
	void ReleaseModelAll();
	// 描画
	void Draw(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot);

private:
	// モデル
	CAssimpModel* m_pModel;
	// アニメNo
	int m_nAnimeNo;	
	// モデルファイル名
	std::string m_filename;
	// テクスチャ
	ID3D11ShaderResourceView* m_pTexture;
	// アニメ再生時間
	static double m_dAnimeTime;

	// モデルプール
	static std::map<const std::string, CAssimpModel*, std::less<>> m_ModelPool;
	// マテリアルプール
	static std::map<const CAssimpModel*, TAssimpMaterial*, std::less<>> m_MaterialPool;
};
