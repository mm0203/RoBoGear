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
class MessageManager;
class Message : public CPolygon
{
	// フレンドクラス　マネージャー
	friend class MessageManager;
public:
	Message();
	~Message() = default;

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
class MessageManager
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void CreateMessage
	(const char* message, XMFLOAT2 pos, int Mag = DefaultMag, XMFLOAT3 Color = { 1.0f,1.0f,1.0f });
	static void DeleteObject(Message*);
	static std::vector<Message*> GetActiveList() { return m_ActiveList; }

private:
	static void AddObject(Message);
	static void CreateObject(int num = MessageNum);
	static void UpdateObject();

private:
	static std::vector<Message*> m_UnusedList;
	static std::vector<Message*> m_ActiveList;
	static std::vector<Message*> m_DeleteList;
	static ID3D11ShaderResourceView* m_pFont;
};

