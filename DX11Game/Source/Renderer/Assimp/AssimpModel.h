//=============================================================================
// AssimpModel.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once
#define NOMINMAX
//#define D3DCOMPILER
#include <map>
#include <vector>
#include <windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#ifdef D3DCOMPILER
#include <d3dcompiler.h>
#endif

// アシンプ
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// システム
#include <System/Camera/Camera.h>
#include<System/Light/Light.h>

// レンダー
#include <Renderer/Mesh/mesh.h>
#include <Renderer/Graphics/DXBuffer.h>
#include <Renderer/Shader/Script/Shader.h>
#include <Renderer/Texture/Texture.h>
#include <Renderer/Texture/TextureFactory.h>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{if(p){(p)->Release();(p)=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{if(p){delete p;(p)=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[]p;(p)=nullptr;}}
#endif

enum EByOpacity
{
	eNoAffect = 0,		// 全て
	eOpacityOnly,		// 不透明のみ
	eTransparentOnly,	// 透明のみ
};

// マテリアル
struct TAssimpMaterial 
{
	DirectX::XMFLOAT4	Ka;		// アンビエント+テクスチャ有無
	DirectX::XMFLOAT4	Kd;		// ディフューズ
	DirectX::XMFLOAT4	Ks;		// スペキュラ+スペキュラ強度
	DirectX::XMFLOAT4	Ke;		// エミッシブ
	ID3D11ShaderResourceView*	pTexture;		// 拡散テクスチャ
	ID3D11ShaderResourceView*	pTexSpecular;	// 鏡面反射テクスチャ
	ID3D11ShaderResourceView*	pTexEmmisive;	// 発光テクスチャ
	ID3D11ShaderResourceView*	pTexTransparent;// 透過テクスチャ

	// マテリアル
	TAssimpMaterial()
	{
		Ka = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 0.5f);
		Kd = DirectX::XMFLOAT4(1, 1, 1, 1);
		Ks = DirectX::XMFLOAT4(0, 0, 0, 0);
		Ke = DirectX::XMFLOAT4(0, 0, 0, 0);
		pTexture = nullptr;
		pTexEmmisive = nullptr;
		pTexSpecular = nullptr;
		pTexTransparent = nullptr;
	}

	// 解放
	void Release()
	{
		SAFE_RELEASE(pTexTransparent);
		SAFE_RELEASE(pTexSpecular);
		SAFE_RELEASE(pTexEmmisive);
		SAFE_RELEASE(pTexture);
	}
};

// 頂点情報
struct TAssimpVertex 
{
	DirectX::XMFLOAT3	vPos;	// 頂点位置
	DirectX::XMFLOAT3	vNorm;	// 頂点法線
	DirectX::XMFLOAT2	vTex;	// UV座標
	UINT		uBoneIndex[4];	// ボーン番号
	float		fBoneWeight[4];	// ボーン重み
	TAssimpVertex()
	{
		vPos = DirectX::XMFLOAT3(0, 0, 0);
		vNorm = DirectX::XMFLOAT3(0, 0, -1);
		vTex = DirectX::XMFLOAT2(0, 0);
		uBoneIndex[0] = uBoneIndex[1] = uBoneIndex[2] = uBoneIndex[3] = 0;
		fBoneWeight[0] = fBoneWeight[1] = fBoneWeight[2] = fBoneWeight[3] = 0.0f;
	}
};

//=============================================================================
// 
// アニメ判定クラス
// 
//=============================================================================
class AnimEvaluator 
{
public:
	AnimEvaluator(const aiAnimation* pAnim);
	~AnimEvaluator();

	void Evaluate(double pTime);
	const std::vector<aiMatrix4x4>& GetTransformations() const { return mTransforms; }

protected:
	const aiAnimation* mAnim;
	double mLastTime;
	std::vector<std::tuple<unsigned int, unsigned int, unsigned int> > mLastPositions;
	std::vector<aiMatrix4x4> mTransforms;
};

// シーン ノード情報(追加データ有のツリー構造)
struct SceneAnimNode
{
	std::string mName;
	SceneAnimNode* mParent;
	std::vector<SceneAnimNode*> mChildren;

	// 直近のローカル変換マトリックス
	aiMatrix4x4 mLocalTransform;

	// 直近のワールド変換マトリックス
	aiMatrix4x4 mGlobalTransform;

	// 現在のチャネル配列インデックス。アニメーション無しの場合は-1。
	int mChannelIndex;

	// デフォルト コンストラクタ
	SceneAnimNode() : mName()
		, mParent(nullptr)
		, mChildren()
		, mLocalTransform()
		, mGlobalTransform()
		, mChannelIndex(-1)
	{
	}

	// 名前を伴うコンストラクタ
	SceneAnimNode(const std::string& pName) : mName(pName)
		, mParent(nullptr)
		, mChildren()
		, mLocalTransform()
		, mGlobalTransform()
		, mChannelIndex(-1)
	{
	}

	// デストラクタ
	~SceneAnimNode()
	{
		for (std::vector<SceneAnimNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it) 
		{
			delete *it;
		}
	}
};
//=============================================================================
// 
// アニメーション ノード マトリックス生成クラス
// 
//=============================================================================
class SceneAnimator
{
public:
	SceneAnimator(const aiScene* pScene, size_t pAnimIndex = 0);
	~SceneAnimator();

	void SetAnimIndex(size_t pAnimIndex);
	void Calculate(double pTime);
	const aiMatrix4x4& GetLocalTransform(const aiNode* node) const;
	const aiMatrix4x4& GetGlobalTransform(const aiNode* node) const;
	const std::vector<aiMatrix4x4>& GetBoneMatrices(const aiNode* pNode, size_t pMeshIndex = 0);

	size_t CurrentAnimIndex() const { return mCurrentAnimIndex; }

	aiAnimation* CurrentAnim() const 
	{
		return static_cast<unsigned int>(mCurrentAnimIndex) < mScene->mNumAnimations ? mScene->mAnimations[mCurrentAnimIndex] : nullptr;
	}

	// アニメの時間情報
	double m_dCurrent;
	double m_dLastPlaying;
	double m_dAnimSpeed;
	double m_dAnimTime;
	double m_dLastAnimTime;

	bool m_bStopAnim;

protected:
	SceneAnimNode* CreateNodeTree(aiNode* pNode, SceneAnimNode* pParent);
	void UpdateTransforms(SceneAnimNode* pNode, const std::vector<aiMatrix4x4>& pTransforms);
	void CalculateGlobalTransform(SceneAnimNode* pInternalNode);

protected:
	const aiScene* mScene;
	int mCurrentAnimIndex;
	AnimEvaluator* mAnimEvaluator;
	SceneAnimNode* mRootNode;
	typedef std::map<const aiNode*, SceneAnimNode*> NodeMap;
	NodeMap mNodesByName;
	typedef std::map<const char*, const aiNode*> BoneMap;
	BoneMap mBoneNodesByName;
	std::vector<aiMatrix4x4> mTransforms;
};

//=============================================================================
// 
// メッシュクラス
// 
//=============================================================================
class CAssimpModel;
class CAssimpMesh 
{
private:
	CAssimpModel* m_pModel;	// モデル
	std::vector<TAssimpVertex> m_aVertex;	// 頂点
	std::vector<UINT> m_aIndex;	// インデックス

	TAssimpMaterial m_material;	// マテリアル

	ID3D11Buffer* m_pConstantBufferOutLine;
	ID3D11Buffer* m_pConstantBufferBone;
	CDXBuffer* m_pAssimp;
	ID3D11ShaderResourceView* m_pRampTex;	// トゥーンテクスチャ用

	ConstantBuffer* m_pConstantBufferGlobal;	// グローバル用
	ConstantBuffer* m_pConstantBufferMaterial;	// マテリアル用


public:
	CAssimpMesh(ID3D11Device* pDevice, CAssimpModel* pModel, std::vector<TAssimpVertex> aVertex, std::vector<UINT> aIndex, TAssimpMaterial& material);
	virtual ~CAssimpMesh();

	void Draw(ID3D11DeviceContext* pDC, DirectX::XMFLOAT4X4& mtxWorld, EByOpacity byOpacity = eNoAffect);
	void DrawOutLine(ID3D11DeviceContext* pDC, DirectX::XMFLOAT4X4& mtxWorld, EByOpacity byOpacity = eNoAffect);
	void Release();
	void SetBoneMatrix(ID3D11DeviceContext* pDC, XMFLOAT4X4 mtxBone[]);

private:
	bool SetupMesh(ID3D11Device* pDevice);
};

//=============================================================================
// 
// モデルクラス
// 
//=============================================================================
class CAssimpModel
{
private:
	std::vector<CAssimpMesh> m_aMesh;
	std::string m_directory;
	std::string m_fname;
	std::string m_ext;
	std::string m_textype;
	DirectX::XMFLOAT4X4 m_mtxTexture;
	DirectX::XMFLOAT4X4 m_mtxWorld;
	TAssimpMaterial* m_pMaterial;
	CLight* m_pLight;
	CCamera* m_pCamera;

	DirectX::XMFLOAT3 m_vBBox;
	DirectX::XMFLOAT3 m_vCenter;

	//ID3D11Buffer* m_pInstancingBuffer;

	const aiScene* m_pScene;
	SceneAnimator* m_pAnimator;
	double m_dCurrent;
	double m_dLastPlaying;

public:
	CAssimpModel();
	virtual ~CAssimpModel();

	static bool InitShader(ID3D11Device* pDevice);
	static void UninitShader();

	DirectX::XMFLOAT4X4& GetTextureMatrix();
	void SetTextureMatrix(DirectX::XMFLOAT4X4& mtxTexture);
	bool Load(ID3D11Device* pDevice, ID3D11DeviceContext* pDC, std::string filename);
	void Draw(ID3D11DeviceContext* pDC, DirectX::XMFLOAT4X4& mtxWorld,bool shadow, EByOpacity byOpacity = eNoAffect);
	void DrawNode(ID3D11DeviceContext* pDC, aiNode* piNode, const aiMatrix4x4& piMatrix, EByOpacity byOpacity, bool shadow);
	void SetLight(CLight* pLight) { m_pLight = pLight; }
	CLight* GetLight() { return m_pLight; }
	void SetCamera(CCamera* pCamera) { m_pCamera = pCamera; }
	CCamera* GetCamera() { return m_pCamera; }
	DirectX::XMFLOAT4X4& GetWorldMatrix() { return m_mtxWorld; }
	void SetMaterial(TAssimpMaterial* pMaterial = nullptr) { m_pMaterial = pMaterial; }
	TAssimpMaterial* GetMaterial() { return m_pMaterial; }

	// アニメーション関連
	void SetAnimIndex(int nAnimIndex);
	int GetCurrentAnimIndex();
	UINT GetAnimCount();
	double GetAnimDuration(int nAnimIndex = -1/* -1:現在のアニメ */);
	void SetStartAnimTime(double dTime);
	void SetAnimSpeed(double dSpeed);
	void SetStopAnim(bool bStop);
	void SetAnimTime(double dTime);

	void Release();
	void ModelRelease(CAssimpModel* model);

	DirectX::XMFLOAT3& GetBBox() { return m_vBBox; }
	DirectX::XMFLOAT3& GetCenter() { return m_vCenter; }

private:
	void ScaleAsset();
	void CalculateBounds(aiNode* piNode, aiVector3D* p_avOut, const aiMatrix4x4& piMatrix);
	void processNode(ID3D11Device* pDevice, aiNode* node);
	CAssimpMesh processMesh(ID3D11Device* pDevice, aiMesh* mesh);
	TAssimpMaterial loadMaterial(ID3D11Device* pDevice, aiMaterial* mat, aiMesh* mesh);
	std::string determineTextureType(aiMaterial* mat);
	int getTextureIndex(aiString* str);
	ID3D11ShaderResourceView* getTextureFromModel(ID3D11Device* pDevice, int textureindex);
	void LoadTexture(ID3D11Device* pDevice, aiString& szPath, ID3D11ShaderResourceView** ppTexture);
	bool HasAlphaPixels(ID3D11ShaderResourceView* pTexture);
};
