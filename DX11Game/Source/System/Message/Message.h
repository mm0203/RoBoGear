//=============================================================================
// Message.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <main.h>
#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
//　マクロ定義
// 
//=============================================================================
namespace
{
	const int MessageMax = 20;		// 表示できる最大文字数
	const int MessageNum = 15;		// 生成できる文字数
	const int DefaultMag = 5;		// デフォルトの文字サイズ
	const float FontSizeX = 4.0f;   // 横フレーム数
	const float FontSizeY = 7.0f;   // 縦フレーム数

	const int FontFrameX = 7;		// フォントフレームX
	const int FontFrameY = 4;		// フォントフレームX

	// UVを分割
	constexpr float FontFrameSizeX = 1.0f / FontFrameX;
	constexpr float FontFrameSizeY = 1.0f / FontFrameY;
}

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
// 前方宣言
class MessageManager;

class CMessage : public CPolygon
{
	friend class CMessageManager; // フレンドクラス
public:
	CMessage();
	~CMessage() = default;

	// メンバ関数
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	// メンバ変数
	XMFLOAT2 m_MessagePos;
	char m_Message[MessageMax];
	int m_Mag;	//文字倍率
};

// メッセージマネージャー
class CMessageManager
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// メッセージ生成
	static void CreateMessage(const char* message, XMFLOAT2 pos, int Mag = DefaultMag, XMFLOAT3 Color = { 1.0f,1.0f,1.0f });
	// オブジェクト削除
	static void DeleteObject(CMessage*);
	// メッセージリスト取得
	static std::vector<CMessage*> GetActiveList() { return m_ActiveList; }

private:
	// メッセージ追加
	static void AddObject(CMessage);
	// メッセージ生成
	static void CreateObject(int num = MessageNum);
	// メッセージ更新
	static void UpdateObject();

private:
	static std::vector<CMessage*> m_UnusedList;	// 未使用リスト
	static std::vector<CMessage*> m_ActiveList;	// 使用リスト
	static std::vector<CMessage*> m_DeleteList; // 削除リスト
	static ID3D11ShaderResourceView* m_pFont;	// 使うフォント
};

